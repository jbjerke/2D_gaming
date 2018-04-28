#include <iostream>
#include <SDL.h>
#include "player.h"

class Hud {
public:
  Hud();
  Hud(const Hud&);
  Hud& operator=(const Hud&);
  //~Hud() { delete player; }
  void draw(const Player&) const;
  void toggleHelp() { helpOn = !helpOn; }

private:
  int px;
  int py;
  int pw;
  int ph;

  int hx;
  int hy;
  int hw;
  int hh;

  int buffer;

  SDL_Renderer* renderer;

  SDL_Rect helpHud;
  bool helpOn;

  SDL_Rect playerHud;

  // const Image * lifeIcon;
  // const Image * bulletIcon;

  SDL_Color hudclr;
  SDL_Color hudoutline;
  SDL_Color textclr;
};
