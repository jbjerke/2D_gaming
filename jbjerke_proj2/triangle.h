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
  int min (int a, int b, int c){
    if (a < b && a < c){ return a; }
    else if (b < a && b < c){ return b; }
    else { return c; }
  }
  int max (int a, int b, int c){
    if (a >= b && a >= c){ return a; }
    else if (b >= a && b >= c){ return b; }
    else { return c; }
  }
};
