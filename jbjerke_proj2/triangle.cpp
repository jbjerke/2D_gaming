#include<SDL2/SDL.h>
#include "triangle.h"

Triangle::Triangle(SDL_Renderer* rend, SDL_Point* pts, SDL_Color cr) :
rr(rend),
corners(pts),
color(cr) {}

void Triangle::drawFilledTriangle(){
  SDL_SetRenderDrawColor(rr, color.r, color.g, color.b, color.a);
//go to mid-valued x => fill in half by half
}

void Triangle::drawTriangle(){
  SDL_SetRenderDrawColor(rr, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(rr, corners[0].x, corners[0].y, corners[1].x, corners[1].y);
  SDL_RenderDrawLine(rr, corners[1].x, corners[1].y, corners[2].x, corners[2].y);
  SDL_RenderDrawLine(rr, corners[2].x, corners[2].y, corners[0].x, corners[0].y);
}
