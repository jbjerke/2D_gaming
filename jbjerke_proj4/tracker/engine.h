#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  //void switchSprite(); maybe if I want more than one player?

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World sky;
  World mntns;
  World trees;
  World path;
  Viewport& viewport;

  Drawable* wizard;
  std::vector<Drawable*> dogats;
  std::vector<Drawable*> pinkupines;
  Drawable* player;
  // might be useful if tracking players
  //std::vector<Drawable*>::const_iterator spiter;
  // int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
  void printScales() const;
  void checkForCollisions();
};
