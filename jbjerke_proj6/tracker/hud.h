#include <iostream>
#include <SDL.h>

class Hud {
public:
  Hud();
  Hud(const Hud&);
  void toggleHelperOn();

private:
  int playerw;
  int playerh;
  int helperw;
  int helperh;
  SDL_Renderer* renderer;
  SDL_Rect helpHud;
  SDL_Rect playerHud;
  SDL_Color hudclr;
  SDL_Color hudoutline;
  SDL_Color textclr;
};
