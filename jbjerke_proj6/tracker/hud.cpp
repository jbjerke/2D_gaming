#include <string>
#include <sstream>
#include "ioMod.h"
#include "gamedata.h"
#include "hud.h"
#include "clock.h"
#include "renderContext.h"

Hud::Hud() :
  w ( Gamedata::getInstance().getXmlInt("hud/width") ),
  h ( Gamedata::getInstance().getXmlInt("hud/height") ),
  renderer ( RenderContext::getInstance()->getRenderer() ),
  rect({50,50,w,h}),
  hudclr({44,14,73,150}),
  hudoutline({24,4,43,150}),
  textclr({255,255,255,255}){
  }

Hud::Hud(const Hud& hd):
  w(hd.w),
  h(hd.h),
  renderer(hd.renderer),
  rect(hd.rect),
  hudclr(hd.hudclr),
  hudoutline(hd.hudoutline),
  textclr(hd.textclr)
{}

void Hud::toggleOn(){
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, hudclr.r, hudclr.g, hudclr.b, hudclr.a);
  SDL_RenderFillRect(renderer, &rect);
  SDL_SetRenderDrawColor(renderer, hudoutline.r, hudoutline.g, hudoutline.b, hudoutline.a);
  SDL_RenderDrawRect(renderer, &rect);
  IoMod::getInstance().writeText("A - move left", 75, 75,textclr);
  IoMod::getInstance().writeText("D - move right", 75, 125,textclr);
  IoMod::getInstance().writeText("SPACE - Attack", 75, 175, textclr);
  IoMod::getInstance().writeText("F1 - Toggle Help", 75, 225, textclr);
  SDL_RenderPresent(renderer);
}

// void Hud::toggleOff(){
//   SDL_RenderClear( renderer );
// }
