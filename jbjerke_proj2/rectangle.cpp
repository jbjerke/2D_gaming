#include<SDL2/SDL.h>
#include "rectangle.h"

Rectangle::Rectangle(SDL_Renderer* rend, SDL_Rect rectangle, SDL_Color cr) :
rr(rend),
rec(rectangle),
color(cr) { }

void Rectangle::drawFilledRectangle(){
  SDL_SetRenderDrawColor(rr, color.r, color.g, color.b, color.a);
  for(int i = 0; rec.h - i > 0; i++){
    SDL_RenderDrawLine(rr, rec.x, rec.y + i, rec.x + rec.w - 1, rec.y + i);
  }
  //SDL_RenderFillRect(rr, &rec);
}

void Rectangle::drawRectangle(){
  SDL_SetRenderDrawColor(rr, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(rr, &rec);
}
