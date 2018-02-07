#include <SDL2/SDL.h>
#include "circle.h"

Circle::Circle(SDL_Renderer* rend, SDL_Point c, int rad, SDL_Color cr) :
rr(rend),
center(c),
radius(rad),
color(cr) {}

//Circle::Circle& operator=(const Circle&);

void Circle::drawFilledCircle(){
  SDL_SetRenderDrawColor(rr, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
      for (int h = 0; h < radius * 2; h++) {
        int dx = radius - w; // horizontal offset
        int dy = radius - h; // vertical offset
        if ((dx*dx + dy*dy) <= (radius * radius)) {
          SDL_RenderDrawPoint(rr, center.x + dx, center.y + dy);
        }
      }
    }
}

void Circle::drawCircle(int pts){
  SDL_SetRenderDrawColor(rr, color.r, color.g, color.b, color.a);
  int step = 360/pts;
  for (int theta = 0; theta < 360; theta += step){
    SDL_RenderDrawPoint(rr,
      center.x+radius*cos(DegtoRad(theta)),
      center.y+radius*cos(DegtoRad(theta)));
  }
}

//void Circle::changeColor(SDL_Color cr){ color = cr; }

//void Circle::changeCenter(SDL_Point c){ center = c; }
