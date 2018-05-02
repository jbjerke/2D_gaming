#include <vector>
#include <SDL.h>
#include "menu.h"

class MenuEngine {
public:
  MenuEngine ();
  ~MenuEngine ();
  void play();

  int getGameMode() const { return gameMode; }

private:
  Clock& clock;
  SDL_Renderer * const renderer;
  Menu menu;

  int gameMode;

  // bool gameWon;
  // bool gameLost;

  void draw() const;
  void update(Uint32);

  MenuEngine(const MenuEngine&);
  MenuEngine& operator=(const MenuEngine&);
};
