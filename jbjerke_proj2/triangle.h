#include<SDL2/SDL.h>

class Triangle{
public:
  Triangle(SDL_Renderer*, SDL_Point*, SDL_Color);
  void drawFilledTriangle();
  void drawTriangle();

private:
  SDL_Renderer* const rr;
  const SDL_Point* corners;
  SDL_Color color;
};
