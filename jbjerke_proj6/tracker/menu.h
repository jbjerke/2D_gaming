#include <vector>
#include <string>
#include "SDL.h"
#include "gamedata.h"
#include "clock.h"
#include "ioMod.h"
#include "sprite.h"
#include "image.h"

class Menu {
public:
  Menu(SDL_Renderer*);
  void draw(bool, bool) const;
  void update();
  void incrIcon();
  void decrIcon();
  void lightOn()  { currentClick = 1; }
  void lightOff() { currentClick = 0; }
  int getOptionNo() const { return currentOption; }

  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;
private:
  SDL_Renderer* renderer;
  Gamedata& gdata;
  SDL_Rect hudFrame;
  SDL_Color menuColor;
  Clock& clock;
  IoMod& io;
  std::vector<std::string> options;
  std::vector<int> optionLoc;
  std::vector<Sprite *> clicks;
  Image* const backimage;
  int currentClick;
  int currentOption;
  int spaces;
  int startClickX;
  int startClickY;
  int clickX;
  int clickY;
};
