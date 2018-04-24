#include <string>
#include <sstream>
#include "ioMod.h"
#include "gamedata.h"
#include "hud.h"
#include "clock.h"
#include "renderContext.h"

Hud::Hud(const Player& p) :
  px ( Gamedata::getInstance().getXmlInt("hud/player/x") ),
  py ( Gamedata::getInstance().getXmlInt("hud/player/y") ),
  pw ( Gamedata::getInstance().getXmlInt("hud/player/width") ),
  ph ( Gamedata::getInstance().getXmlInt("hud/player/height") ),
  hx ( Gamedata::getInstance().getXmlInt("hud/help/x") ),
  hy ( Gamedata::getInstance().getXmlInt("hud/help/y") ),
  hw ( Gamedata::getInstance().getXmlInt("hud/help/width") ),
  hh ( Gamedata::getInstance().getXmlInt("hud/help/height") ),
  renderer ( RenderContext::getInstance()->getRenderer() ),
  helpHud({hx,hy,hw,hh}),
  helpOn(true),
  playerHud({px,py,pw,ph}),
  player( new Player(p) ),
  lifeIcon( ImageFactory::getInstance().getImage("lifeIcon") ),
  bulletIcon( ImageFactory::getInstance().getImage("bulletIcon") ),
  hudclr({44,14,73,150}),
  hudoutline({24,4,43,150}),
  textclr({255,255,255,255})
{  }

Hud::Hud(const Hud& hd):
  px(hd.px),
  py(hd.py),
  pw(hd.pw),
  ph(hd.ph),
  hx(hd.hx),
  hy(hd.hy),
  hw(hd.hw),
  hh(hd.hh),
  renderer(hd.renderer),
  helpHud(hd.helpHud),
  helpOn(hd.helpOn),
  playerHud(hd.playerHud),
  player( hd.player ),
  lifeIcon( hd.lifeIcon ),
  bulletIcon( hd.bulletIcon ),
  hudclr(hd.hudclr),
  hudoutline(hd.hudoutline),
  textclr(hd.textclr)
{ }

Hud& Hud::operator=(const Hud& hd){
  px = hd.px;
  py = hd.py;
  pw = hd.pw;
  ph = hd.ph;
  hx = hd.hx;
  hy = hd.hy;
  hw = hd.hw;
  hh = hd.hh;
  renderer = hd.renderer;
  helpHud = hd.helpHud;
  helpOn = hd.helpOn;
  playerHud = hd.playerHud;
  player =  hd.player;
  hudclr = hd.hudclr;
  hudoutline = hd.hudoutline;
  textclr = hd.textclr;
  return *this;
}

void Hud::draw() const {
  if( helpOn ){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, hudclr.r, hudclr.g, hudclr.b, hudclr.a);
    SDL_RenderFillRect(renderer, &helpHud);
    SDL_SetRenderDrawColor(renderer, hudoutline.r, hudoutline.g, hudoutline.b, hudoutline.a);
    SDL_RenderDrawRect(renderer, &helpHud);
    IoMod::getInstance().writeText("A - move left", 75, 75,textclr);
    IoMod::getInstance().writeText("D - move right", 75, 125,textclr);
    IoMod::getInstance().writeText("SPACE - Attack", 75, 175, textclr);
    IoMod::getInstance().writeText("F1 - Toggle Help", 75, 225, textclr);
    SDL_RenderPresent(renderer);
  }

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, hudclr.r, hudclr.g, hudclr.b, hudclr.a);
  SDL_RenderFillRect(renderer, &playerHud);
  SDL_SetRenderDrawColor(renderer, hudoutline.r, hudoutline.g, hudoutline.b, hudoutline.a);
  SDL_RenderDrawRect(renderer, &playerHud);
  // std::cout << player->getScore() << std::endl;
  // draw this bullets
  for(int n = 0; n < player->getLifeCount(); n++){
    lifeIcon->draw( px + 10*(n+1) + lifeIcon->getWidth(), py  );
  }
  // draw the lives
  // write the score
  std::stringstream strm;
  strm << player->getScore();
  IoMod::getInstance().writeText(strm.str(), px+pw/2, py+hh/2, textclr);
  SDL_RenderPresent(renderer);
}
