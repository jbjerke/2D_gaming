#include<SDL2/SDL.h>

class Circle{
public:
  Circle(SDL_Renderer*, SDL_Point, int, SDL_Color);
  //Circle& operator=(const Circle&);
  void drawFilledCircle();
  void drawCircle(int);
//  void changeColor(SDL_Color);
  //void changeCenter(SDL_Point);
private:
    SDL_Renderer* const rr;
    SDL_Point center;
    int radius;
    SDL_Color color;
    const double pi = 3.1415926535897;
    const double rtd = 180/pi;
    const double dtr = pi/180;
    double DegtoRad(double x){ return x*dtr; }
    double RedtoDeg(double x){ return x*rtd; }
};
