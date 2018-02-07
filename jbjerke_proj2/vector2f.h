#include <iostream>
#include <SDL2/SDL.h>
#include "vector2f.h"

const int WIDTH = 640;
const int HEIGHT = 480;

Vector2f v0(320, 100);
Vector2f v1(270, 186);
Vector2f v2(370, 186);

float wedge(Vector2f a, Vector2f b) {
 return a[0]*b[1] - a[1]*b[0];
}

float triangle(Vector2f x, float fuzz) {
  Vector2f e0 = v1 - v0;
  Vector2f e1 = v2 - v1;
  Vector2f e2 = v0 - v2;
  float N = wedge(e1, -e0);
  if(N <= -0.00001){
      N  *= -1.0;
      e0 *= -1.0;
      e1 *= -1.0;
      e2 *= -1.0;
  }

  float b0 = wedge(e0, x - v0);
  if(b0 <= -0.00001) { return 0.0; }
  float b1 = wedge(e1, x - v1);
  if(b1 <= -0.00001) { return 0.0; }
  float b2 = wedge(e2, x - v2);
  if(b2 <= -0.00001) { return 0.0; }
  if(fuzz == 0.0) return 1.0;
  return std::min(1.0, (pow(b0*b1*b2, 0.33) * 3.0 / N) / fuzz);
}

int smallest(int a, int b, int c) {
  int temp = std::min(a, b);
  return std::min(temp, c);
}
int largest(int a, int b, int c) {
  int temp = std::max(a, b);
  return std::max(temp, c);
}

int main (int , char*[]) {
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    std::cout << "Failed to initialize SDL2" << std::endl;
    return EXIT_FAILURE;
  }
  SDL_Window* window = SDL_CreateWindow(
      "Drawing a Triangle", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH, HEIGHT, SDL_WINDOW_SHOWN
  );

  SDL_Renderer* renderer = SDL_CreateRenderer(
    window, -1, SDL_RENDERER_ACCELERATED
  );

  // Background will be rendered in this color:
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

  // Clear window
  SDL_RenderClear( renderer );

  SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
  SDL_RenderDrawLine(renderer, 320, 100, 270, 186);
  SDL_RenderDrawLine(renderer, 270, 186, 370, 186);
  SDL_RenderDrawLine(renderer, 370, 186, 320, 100);

  float x = smallest(v0[0],v1[0],v2[0]);
  float y = smallest(v0[1],v1[1],v2[1]);
  Vector2f box0( x, y );
  std::cout << "box0: " << box0 << std::endl;

  x = largest(v0[0],v1[0],v2[0]);
  y = largest(v0[1],v1[1],v2[1]);
  Vector2f box1( x, y );
  std::cout << "box1: " << box1 << std::endl;

  for (int x = box0[0]; x <= box1[0]; ++x) {
    for (int y = box0[1]; y <= box1[1]; ++y) {
      Vector2f p(x, y);
      if ( triangle(p, 0.6) ) {
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }

  for(int y = 0; y < HEIGHT; ++y) {
    float c = static_cast<float>(y)/HEIGHT;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255 * c, 255);
    SDL_RenderDrawLine(renderer, 0, y, 32, y);
  }

  // The next line does the render:
  SDL_RenderPresent(renderer);

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
