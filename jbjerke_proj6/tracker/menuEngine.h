#include <vector>
#include <SDL.h>
#include "menu.h"

class MenuEngine {
public:
  MenuEngine ();
  ~MenuEngine ();
  void play(bool, bool);

  int getOptionNo() const { return optionNo; }

private:
  Clock& clock;
  SDL_Renderer * const renderer;
  Menu menu;

  int optionNo;

  // bool gameWon;
  // bool gameLost;

  void draw(bool, bool) const;
  void update(Uint32);

  MenuEngine(const MenuEngine&);
  MenuEngine& operator=(const MenuEngine&);
};
