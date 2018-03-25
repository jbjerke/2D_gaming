#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twoWayMultiSprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() {
  spiter = sprites.begin();
  while( spiter != sprites.end() ){
    delete *spiter;
    spiter++;
  }

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
  sprites(),
  spiter(),
  makeVideo( false )
{
  unsigned int numOfSprite = Gamedata::getInstance().getXmlInt("PrideFlag/count");

  for( unsigned int n = 0; n < numOfSprite; n++ ){
    sprites.push_back( new Sprite("PrideFlag") );
  }
  sprites.push_back( new TwoWayMultiSprite("Pinkupine"));
  spiter = sprites.begin();

  switchSprite();
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  sky.draw();
  mntns.draw();
  trees.draw();
  path.draw();

  std::stringstream strm;
  strm << "fps: " << clock.getFps();
  io.writeText(strm.str(), 30, 60);
  SDL_Color color = {0, 0, 255, 0};
  io.writeText("Jordan Bjerken", 30, 470, color);

  for(auto* sp : sprites){
    sp->draw();
  }

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* sp : sprites){
    sp->update(ticks);
  }
  // star->update(ticks);
  // spinningStar->update(ticks);
  sky.update();
  mntns.update();
  trees.update();
  path.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  // ++currentSprite;
  // currentSprite = currentSprite % 2;
  // if ( currentSprite ) {
  //   Viewport::getInstance().setObjectToTrack(*spiter);
  // }
  // else {
  //   if( spiter != sprites.end()){
  //     spiter++;
  //   }
  //   else {
  //     spiter = sprites.begin();
  //   }
  //   Viewport::getInstance().setObjectToTrack(*spiter);
  // }
  ++spiter;
  if( spiter != sprites.end() ){
    Viewport::getInstance().setObjectToTrack(*spiter);
  }
  else {
    spiter = sprites.begin();
    Viewport::getInstance().setObjectToTrack(*spiter);;
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
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
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
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
