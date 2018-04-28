#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "twoWayMultiSprite.h"
#include "shooterSprite.h"
#include "player.h"
#include "smartSprite.h"
#include "gamedata.h"
#include "hud.h"
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

  delete strat;

  delete wizard;

  delete player;

  // delete hd;

  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  // sound( ),
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
  strat(),
  collision( false ),
  godmode( false ),
  hud(new Hud() ),
  makeVideo( false )
{
  clock.startClock();

  unsigned int numOfDogats= Gamedata::getInstance().getXmlInt("Dogat/count");
  unsigned int numOfPinkupines= Gamedata::getInstance().getXmlInt("Pinkupine/count");
  dogats.reserve(numOfDogats);
  pinkupines.reserve(numOfPinkupines);

  Vector2f pos = player->getPlayer()->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();

  for( unsigned int n = 0; n < numOfDogats; n++ ){
    dogats.push_back( new TwoWayMultiSprite("Dogat") );
  }

  for( unsigned int m = 0; m < numOfPinkupines/2; m++){
    pinkupines.push_back( new SmartSprite("Pinkupine", "aggressive", pos, w, h) );
    player->attach( pinkupines[m] );
  }

  for( unsigned int m = 0; m < numOfPinkupines/2; m++){
    SmartSprite* sm = new SmartSprite("Pinkupine", "passive", pos, w, h);
    pinkupines.push_back( sm );
    player->attach( sm );
  }

  const std::string s = Gamedata::getInstance().getXmlStr("collisionStrategy");
  if( s == "Rectangular" ){
    strat = new RectangularCollisionStrategy;
  }
  else if ( s == "MidPoint" ){
    strat = new MidPointCollisionStrategy;
  }
  else if ( s == "PerPixel" ){
    strat = new PerPixelCollisionStrategy;
  }

  Viewport::getInstance().setObjectToTrack(player->getPlayer());
  std::cout << "Loading complete" << std::endl;
}


void Engine::draw() const {
  sky.draw();
  mntns.draw();
  trees.draw();
  path.draw();

  // Put in the HUD:
  SDL_Color color = {255, 255, 255, 0};
  io.writeText("Jordan Bjerken", 30, 800, color);

  wizard->draw();

  for(auto* dg : dogats){
    dg->draw();
  }

  for(auto* pk : pinkupines){
    pk->draw();
  }

  if ( !godmode ) {
    if ( player->playerDed() ){
      SDL_Color color = {255, 255, 255, 0};
      io.writeText("Press 'R' to restart", 625, 150, color);
      clock.pause();
    }
  }

  player->draw();

  viewport.draw();

  hud->draw(*player);

  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();

  // if ( !godmode ) {
  //   if ( player->playerDed() ){
  //     SDL_Color color = {255, 255, 255, 0};
  //     io.writeText("Press 'R' to restart", 400, 700, color);
  //     clock.pause();
  //   }
  // }

  wizard->update(ticks);

  auto dt = dogats.begin();
  while( dt != dogats.end() ){
    (*dt)->update(ticks);
    if ( (*dt)->isDoneExploding() ){
      delete *dt;
      dt = dogats.erase(dt);
    }
    else ++dt;
  }

  auto pp = pinkupines.begin();
  while( pp != pinkupines.end() ){
    (*pp)->update(ticks);
    if ( (*pp)->isDoneExploding() ){
      delete *pp;
      pp = pinkupines.erase(pp);
    }
    else ++pp;
  }

  player->update(ticks);
  sky.update();
  mntns.update();
  trees.update();
  path.update();
  viewport.update(); // always update viewport last
}

void Engine::checkForCollisions(){
  std::vector<Drawable*>::iterator dit = dogats.begin();
  while( dit != dogats.end() ){
    if( !((*dit)->isExploding()) ){
      if ( strat->execute(*(player->getPlayer()), **dit) && !( player->isExploding() ) ){
        // (*dit)->explode();
        player->explode();
        return;
      }
      if( player->heHitSomething(*dit) ){
        (*dit)->explode();
      }
    }
    ++dit;
  }

  std::vector<SmartSprite*>::iterator pit = pinkupines.begin();
  while( pit != pinkupines.end() ){
    if( !(*pit)->isExploding() ){
      if ( strat->execute(*(player->getPlayer()), **pit) && !( player->isExploding() ) ){
        (*pit)->explode();
        player->detach(*pit);
        player->explode();
        return;
      }
      if( player->heHitSomething(*pit) ){
        (*pit)->explode();
        player->detach(*pit);
      }
    }
    ++pit;
  }

  // if ( strat->execute(*player, *wizard) ){
  //   static_cast<Player*>(player)->stop();
  // }
}

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;
  SDLSound sound;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if( keystate[SDL_SCANCODE_R] ){
          clock.unpause();
          return true;
        }
        if( keystate[SDL_SCANCODE_G] ){
          godmode = !godmode;
        }
        if ( keystate[SDL_SCANCODE_F1] ){
          hud->toggleHelp();
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
        player->left();
      }
      if (keystate[SDL_SCANCODE_D]){
        player->right();
      }
      if( keystate[SDL_SCANCODE_SPACE] ){
        player->heAttak();
        sound[0];
      }
      if( keystate[SDL_SCANCODE_E ]){
        player->explode();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
  return false;
}
