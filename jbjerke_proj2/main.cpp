#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

const std::string NAME = "jbjerke";
const int WIDTH = 640;
const int HEIGHT = 500;

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );

// Lake ========================================================================
SDL_Rect lake0 = {0,300, WIDTH, 200};
SDL_Color lkcr0 = {19, 19, 38, 255};

Rectangle lakelayer0(renderer, lake0, lkcr0);
lakelayer0.drawFilledRectangle();

SDL_Point c1 = {320,-925};
SDL_Color ccr1= {34, 34, 66, 255};

Circle cir1(renderer, c1, 1400, ccr1);
cir1.drawFilledCircle();

SDL_Point c2 = {320,-310};
SDL_Color ccr2= {49, 49, 89, 255};

Circle cir2(renderer, c2, 700, ccr2);
cir2.drawFilledCircle();

SDL_Rect lake2 = {0,180, WIDTH, 75};
SDL_Color lkcr2 = {77, 77, 135, 255};

Rectangle lakelayer2(renderer, lake2, lkcr2);
lakelayer2.drawFilledRectangle();

// Sky =========================================================================
SDL_Rect sky0 = {0, 0, WIDTH, 8};
SDL_Color s0 = {79, 63, 135, 255};

Rectangle skylayer0(renderer, sky0, s0);
skylayer0.drawFilledRectangle();

SDL_Rect skyhf = {0, 8, WIDTH, 147};
SDL_Color shf = {71, 80, 137, 255};

Rectangle skylayerhf(renderer, skyhf, shf);
skylayerhf.drawFilledRectangle();

SDL_Rect sky1 = {0, 20, WIDTH, 135};
SDL_Color s1 = {124, 150, 165, 255};

Rectangle skylayer1(renderer, sky1, s1);
skylayer1.drawFilledRectangle();

SDL_Rect sky2 = {0, 50, WIDTH, 105};
SDL_Color s2 = {216, 137, 84, 255};

Rectangle skylayer2(renderer, sky2, s2);
skylayer2.drawFilledRectangle();

SDL_Rect sky2hf = {0, 60, WIDTH, 95};
SDL_Color s2hf = {117, 52, 24,255};

Rectangle skylayer2hf(renderer, sky2hf, s2hf);
skylayer2hf.drawFilledRectangle();

SDL_Rect sky3 = {0, 75, WIDTH, 80};
SDL_Color s3 = {86, 38, 28, 255};

Rectangle skylayer3(renderer, sky3, s3);
skylayer3.drawFilledRectangle();

SDL_Rect sky4 = {0, 90, WIDTH, 65};
SDL_Color s4 = {44, 35, 45, 255};

Rectangle skylayer4(renderer, sky4, s4);
skylayer4.drawFilledRectangle();

SDL_Rect sky5 = {0, 115, WIDTH, 40};
SDL_Color s5 = {44, 30, 45, 255};

Rectangle skylayer5(renderer, sky5, s5);
skylayer5.drawFilledRectangle();

// Land ========================================================================
SDL_Point leftvcs1 = {0,167};
SDL_Point leftvcs2 = {600,167};
SDL_Point leftvcs3 = {0,135};
SDL_Point leftvcs[3]= {leftvcs1, leftvcs2, leftvcs3};
SDL_Color blk = {0,0,0,0};

Triangle leftLand (renderer, leftvcs, blk);
leftLand.drawFilledTriangle();

SDL_Point rightvcs1 = {WIDTH,167};
SDL_Point rightvcs2 = {270,167};
SDL_Point rightvcs3 = {WIDTH,135};
SDL_Point rightvcs[3]= {rightvcs1, rightvcs2, rightvcs3};

Triangle rightLand (renderer, rightvcs, blk);
rightLand.drawFilledTriangle();

SDL_Point v0 = {75, 150};
SDL_Point v1 = {95,150};
SDL_Point v2 = {90,130};
SDL_Point v[3] = {v0, v1, v2};
Triangle trmt1(renderer, v, blk);
trmt1.drawFilledTriangle();

SDL_Point b0 = {155,160};
SDL_Point b1 = {165,160};
SDL_Point b2 = {158, 135};
SDL_Point b[3] = {b0, b1, b2};
Triangle trmt2(renderer, b, blk);
trmt2.drawFilledTriangle();

SDL_Point t0 = {165,160};
SDL_Point t1 = {200,160};
SDL_Point t2 = {170, 140};
SDL_Point t[3] = {t0, t1, t2};
Triangle trmt3(renderer, t, blk);
trmt3.drawFilledTriangle();
// Balloons and dock ===========================================================
// Dock
SDL_Rect p1 = {360,340,5,130};
Rectangle pole1(renderer, p1, blk);
pole1.drawFilledRectangle();

SDL_Rect p2 = {580,290,5,180};
Rectangle pole2(renderer, p2, blk);
pole2.drawFilledRectangle();

SDL_Rect p3 = {460,300,5,130};
Rectangle pole3(renderer, p3, blk);
pole3.drawFilledRectangle();

SDL_Rect p4 = {600,100,5,330};
Rectangle pole4(renderer, p4, blk);
pole4.drawFilledRectangle();

SDL_Rect p5 = {365, 360, 100, 5};
Rectangle pole5(renderer, p5, blk);
pole5.drawFilledRectangle();

SDL_Rect p6 = {585, 360, 20, 5};
Rectangle pole6(renderer, p6, blk);
pole6.drawFilledRectangle();

// Balloons
SDL_Point bal1 = {520, 465};
SDL_Color nbal1 = {0, 55, 255, 255};
Circle baln1(renderer, bal1, 20, nbal1);
baln1.drawFilledCircle();

SDL_Point bal2 = {475, 480};
SDL_Color nbal2 = {0, 255, 246, 255};
Circle baln2(renderer, bal2, 25, nbal2);
baln2.drawFilledCircle();

SDL_Point bal3 = {230, 430};
SDL_Color nbal3 = {33, 255, 0, 255};
Circle baln3(renderer, bal3, 20, nbal3);
baln3.drawFilledCircle();

SDL_Point bal4 = {150, 330};
SDL_Color nbal4 = {186, 0, 117, 255};
Circle baln4(renderer, bal4, 10, nbal4);
baln4.drawFilledCircle();
//==============================================================================
  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
  frameGen.makeFrame();

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
