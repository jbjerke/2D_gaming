#include<SDL2/SDL.h>

class Rectangle{
public:
  Rectangle(SDL_Renderer*, SDL_Rect, SDL_Color);
  void drawFilledRectangle();
  void drawRectangle();
private:
  SDL_Renderer* const rr;
  SDL_Rect rec;
  SDL_Color color;
};
