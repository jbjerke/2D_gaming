#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "sound.h"

class CollisionStrategy;
class Player;
class GoalSprite;
class SmartSprite;
class Hud;

class Engine {
public:
  Engine ();
  ~Engine ();
  bool play();
  //void switchSprite(); maybe if I want more than one player?

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;

  SDLSound sound;

  SDL_Renderer * const renderer;
  World sky;
  World mntns;
  World trees;
  World path;
  Viewport& viewport;

  GoalSprite* wizard;
  std::vector<Drawable*> harmlessdogats;
  std::vector<Drawable*> dogats;
  std::vector<SmartSprite*> pinkupines;
  Player* player;
  // might be useful if tracking players
  //std::vector<Drawable*>::const_iterator spiter;
  // int currentSprite;

  CollisionStrategy* strat;
  bool collision;

  bool godmode;

  Hud* hud;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
  void printScales() const;
  void checkForCollisions();
};
