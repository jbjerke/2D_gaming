#include<SDL2/SDL.h>
#include "triangle.h"

int maxx (const SDL_Point* pt, int ind){
  if (ind == 1){
    if (pt[0].x >= pt[1].x && pt[0].x >= pt[2].x){ return 1; }
    else if (pt[1].x >= pt[0].x && pt[1].x >= pt[2].x){ return 2; }
    else { return 3; }
  }
  else{
    if (pt[0].y >= pt[1].y && pt[0].y >= pt[2].y){ return 1; }
    else if (pt[1].y >= pt[0].y && pt[1].y >= pt[2].y){ return 2; }
    else { return 3; }
  }
}

int minx (const SDL_Point* pt, int ind){
  if (ind == 1){
    if (pt[0].x <= pt[1].x && pt[0].x <= pt[2].x){ return 1; }
    else if (pt[1].x <= pt[0].x && pt[1].x <= pt[2].x){ return 2; }
    else { return 3; }
  }
  else{
    if (pt[0].y <= pt[1].y && pt[0].y <= pt[2].y){ return 1; }
    else if (pt[1].y <= pt[0].y && pt[1].y <= pt[2].y){ return 2; }
    else { return 3; }
  }
}

Triangle::Triangle(SDL_Renderer* rend, SDL_Point* pts, SDL_Color cr) :
rr(rend),
corners(pts),
color(cr) {}

void Triangle::drawFilledTriangle(){
  SDL_SetRenderDrawColor(rr, color.r, color.g, color.b, color.a);
//go to mid-valued x => fill in half by half
  // Sorry this is inefficient but:
  // Determine the vertex with the smallest x
  int lvi = minx(corners, 1);
  SDL_Point lv = corners[lvi-1];

  // Determine the vertex with the largest x
  int rvi = maxx(corners, 1);
  SDL_Point rv = corners[rvi-1];

  // Determine the vertex with the mid x
  int mvi;

  if (lvi == 1 || rvi == 1){
    if (lvi == 2 || rvi == 2){ mvi = 3; }
    else if (lvi == 3 || rvi == 3){ mvi = 2; }
    else { mvi = 1; }
  }
  else if(lvi == 2 || rvi == 2){
    if (lvi == 1 || rvi == 1){ mvi = 3; }
    else if (lvi == 3 || rvi == 3){ mvi = 1; }
    else { mvi = 2; }
  }
  else{
    mvi = 3;
  }
  SDL_Point mv = corners[mvi-1];

  // Pick two arbitrary vertices of the triangle and determine the y=mx+b
  float m = (rv.y - lv.y)/(rv.x - lv.x);
  float b = -1*m*rv.x + rv.y;

  // Draw lines from third vertex to points on this lines
  for(int n = lv.x+1; n <= rv.x-1; n++){
    SDL_RenderDrawLine(rr, n, m*n + b, mv.x, mv.y);
  }
  SDL_RenderDrawLine(rr, lv.x, lv.y, rv.x, rv.y);
  SDL_RenderDrawLine(rr, lv.x, lv.y, mv.x, mv.y);
  SDL_RenderDrawLine(rr, mv.x, mv.y, rv.x, rv.y);
}

void Triangle::drawTriangle(){
  SDL_SetRenderDrawColor(rr, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(rr, corners[0].x, corners[0].y, corners[1].x, corners[1].y);
  SDL_RenderDrawLine(rr, corners[1].x, corners[1].y, corners[2].x, corners[2].y);
  SDL_RenderDrawLine(rr, corners[2].x, corners[2].y, corners[0].x, corners[0].y);
}
