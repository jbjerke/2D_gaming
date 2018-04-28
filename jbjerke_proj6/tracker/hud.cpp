#include <string>
#include <sstream>
#include "ioMod.h"
#include "gamedata.h"
#include "hud.h"
#include "clock.h"
#include "renderContext.h"

Hud::Hud() :
  px ( Gamedata::getInstance().getXmlInt("hud/player/x") ),
  py ( Gamedata::getInstance().getXmlInt("hud/player/y") ),
  pw ( Gamedata::getInstance().getXmlInt("hud/player/width") ),
  ph ( Gamedata::getInstance().getXmlInt("hud/player/height") ),
  hx ( Gamedata::getInstance().getXmlInt("hud/help/x") ),
  hy ( Gamedata::getInstance().getXmlInt("hud/help/y") ),
  hw ( Gamedata::getInstance().getXmlInt("hud/help/width") ),
  hh ( Gamedata::getInstance().getXmlInt("hud/help/height") ),
  buffer( Gamedata::getInstance().getXmlInt("hud/textBuffer") ),
  renderer ( RenderContext::getInstance()->getRenderer() ),
  helpHud({hx,hy,hw,hh}),
  helpOn(true),
  playerHud({px,py,pw,ph}),
//  player( new Player(p) ),
  // lifeIcon( ImageFactory::getInstance().getImage("lifeIcon") ),
  // bulletIcon( ImageFactory::getInstance().getImage("bulletIcon") ),
  hudclr(
    {(Uint8)Gamedata::getInstance().getXmlInt("hud/color/r"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/color/g"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/color/b"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/color/a")}),
  hudoutline(
    {(Uint8)Gamedata::getInstance().getXmlInt("hud/outlineColor/r"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/outlineColor/g"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/outlineColor/b"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/outlineColor/a")}),
  textclr(
    {(Uint8)Gamedata::getInstance().getXmlInt("hud/textColor/r"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/textColor/g"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/textColor/b"),
       (Uint8)Gamedata::getInstance().getXmlInt("hud/textColor/a")})
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
  buffer(hd.buffer),
  renderer(hd.renderer),
  helpHud(hd.helpHud),
  helpOn(hd.helpOn),
  playerHud(hd.playerHud),
  //player( hd.player ),
  // lifeIcon( hd.lifeIcon ),
  // bulletIcon( hd.bulletIcon ),
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
  buffer = hd.buffer;
  renderer = hd.renderer;
  helpHud = hd.helpHud;
  helpOn = hd.helpOn;
  playerHud = hd.playerHud;
  //player =  hd.player;
  hudclr = hd.hudclr;
  hudoutline = hd.hudoutline;
  textclr = hd.textclr;
  return *this;
}

void Hud::draw(const Player& player) const {
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  if( helpOn ){
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, hudclr.r, hudclr.g, hudclr.b, hudclr.a);
    SDL_RenderFillRect(renderer, &helpHud);
    SDL_SetRenderDrawColor(renderer, hudoutline.r, hudoutline.g, hudoutline.b, hudoutline.a);
    SDL_RenderDrawRect(renderer, &helpHud);
    IoMod::getInstance().writeText("A - move left", hx + buffer, hy + buffer,textclr);
    IoMod::getInstance().writeText("D - move right", hx + buffer, hy + buffer + 50,textclr);
    IoMod::getInstance().writeText("SPACE - Attack", hx + buffer, hy + buffer + 100, textclr);
    IoMod::getInstance().writeText("F1 - Toggle Help", hx + buffer, hy + buffer + 150, textclr);
    //SDL_RenderPresent(renderer);
  }

  SDL_SetRenderDrawColor(renderer, hudclr.r, hudclr.g, hudclr.b, hudclr.a + 50);
  SDL_RenderFillRect(renderer, &playerHud);
  SDL_SetRenderDrawColor(renderer, hudoutline.r, hudoutline.g, hudoutline.b, hudoutline.a);
  SDL_RenderDrawRect(renderer, &playerHud);
  // std::cout << player->getScore() << std::endl;
  // draw this bullets
  // for(int n = 0; n < player->getLifeCount(); n++){
  //   lifeIcon->draw( px + 10*(n+1) + lifeIcon->getWidth(), py  );
  // }
  // draw the lives
  std::stringstream strm1;
  strm1 << "Lives: " << player.getLifeCount();
  IoMod::getInstance().writeText(strm1.str(), px+buffer, py+ph/4, textclr);

  // write the score
  std::stringstream strm2;
  strm2 << "Score: " << player.getScore();
  IoMod::getInstance().writeText(strm2.str(), px+pw/2+buffer, py+ph/4, textclr);

  SDL_RenderPresent(renderer);
}
