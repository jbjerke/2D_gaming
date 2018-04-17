#include <iostream>
#include <SDL.h>

class Hud {
public:
  Hud();
  Hud(const Hud&);
  void toggleOn();
  // void toggleOff();

private:
  int w;
  int h;
  SDL_Renderer* renderer;
  SDL_Rect rect;
  SDL_Color hudclr;
  SDL_Color hudoutline;
  SDL_Color textclr;
};
