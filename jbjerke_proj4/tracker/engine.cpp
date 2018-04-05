#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "twoWayMultiSprite.h"
#include "player.h"
#include "smartSprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "collisionStrategy.h"

Engine::~Engine() {
  for(auto* ds : dogats){
    delete ds;
  }
  for(auto* ps : pinkupines){
    delete ps;
  }
  for( CollisionStrategy* s : strats ){
    delete s;
  }
  delete wizard;

  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  sky("sky", Gamedata::getInstance().getXmlInt("sky/factor") ),
  mntns("mntns", Gamedata::getInstance().getXmlInt("mntns/factor") ),
  trees("trees", Gamedata::getInstance().getXmlInt("trees/factor") ),
  path("path", Gamedata::getInstance().getXmlInt("path/factor") ),
  viewport( Viewport::getInstance() ),
  wizard(new Sprite("Wizard")),
  dogats(),
  pinkupines(),
  player(new Player("FireSpirit")),
  strats(),
  currentStrat( 0 ),
  collision( false ),
  makeVideo( false )
{
  unsigned int numOfDogats= Gamedata::getInstance().getXmlInt("Dogat/count");
  unsigned int numOfPinkupines= Gamedata::getInstance().getXmlInt("Pinkupine/count");
  dogats.reserve(numOfDogats);
  pinkupines.reserve(numOfPinkupines);

  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();

  for( unsigned int n = 0; n < numOfDogats; n++ ){
    dogats.push_back( new SmartSprite("Dogat", pos, w, h) );
    static_cast<Player*>(player)->attach( dogats[n] );
  }

  for( unsigned int m = 0; m < numOfPinkupines; m++){
    pinkupines.push_back( new SmartSprite("Pinkupine", pos, w, h) );
    static_cast<Player*>(player)->attach( pinkupines[m] );
  }

  strats.push_back( new RectangularCollisionStrategy );
  strats.push_back( new MidPointCollisionStrategy );
  strats.push_back( new PerPixelCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}


void Engine::draw() const {
  sky.draw();
  mntns.draw();
  trees.draw();
  path.draw();

  // Put in the HUD:
  // std::stringstream strm;
  // strm << "fps: " << clock.getFps();
  // io.writeText(strm.str(), 30, 60);
  // SDL_Color color = {0, 0, 255, 0};
  // io.writeText("Jordan Bjerken", 30, 470, color);

  wizard->draw();

  for(auto* dg : dogats){
    dg->draw();
  }

  for(auto* pk : pinkupines){
    pk->draw();
  }

  player->draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();
  wizard->update(ticks);

  for(auto* dt : dogats){
    dt->update(ticks);
  }

  for(auto* pp : pinkupines){
    pp->update(ticks);
  }

  player->update(ticks);
  // star->update(ticks);
  // spinningStar->update(ticks);
  sky.update();
  mntns.update();
  trees.update();
  path.update();
  viewport.update(); // always update viewport last
}

void Engine::checkForCollisions(){
  std::vector<SmartSprite*>::iterator dit = dogats.begin();
  while( dit != dogats.end() ){
    if ( strats[currentStrat]->execute(*player, **dit) ){
      SmartSprite* doneForD = *dit;
      static_cast<Player*>(player)->detach(doneForD);
      delete doneForD;
      dit = dogats.erase(dit);
    }
    else { ++dit; }
  }

  std::vector<SmartSprite*>::iterator pit = pinkupines.begin();
  while( pit != pinkupines.end() ){
    if ( strats[currentStrat]->execute(*player, **pit) ){
      SmartSprite* doneForP = *pit;
      static_cast<Player*>(player)->detach(doneForP);
      delete doneForP;
      pit = pinkupines.erase(pit);
    }
    else { ++pit; }
  }
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_M] ){
          std::cout<<"changed strat" <<std::endl;
          currentStrat = (currentStrat + 1) % strats.size();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]){
        static_cast<Player*>(player)->left();
      }
      if (keystate[SDL_SCANCODE_D]){
        static_cast<Player*>(player)->right();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
