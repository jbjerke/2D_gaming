#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include "drawable.h"

class SmartSprite;

class Player : public Drawable {
public:
  Player(const std::string&);
  Player(const Player&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const {
    return images[currentFrame];
  }
  int getScaledWidth()  const {
    return getScale()*images[currentFrame]->getWidth();
  }
  int getScaledHeight()  const {
    return getScale()*images[currentFrame]->getHeight();
  }
  virtual const SDL_Surface* getSurface() const {
    return images[currentFrame]->getSurface();
  }

  void right();
  void left();
  // void jump(); To come when I have the time to draw this
  void stop();

  void attach( SmartSprite* ss ) { observers.push_back(ss); }
  void detach( SmartSprite* ss );
  void notify( ); //Can probably just include in the update

private:
  std::vector<Image *> rightimages;
  std::vector<Image *> leftimages;
  std::vector<Image *> idleimages;
  // Eventually - both directions of idle
  // Eventaully - jump
  std::vector<Image *> images;

  std::list<SmartSprite*> observers;

  std::string playerName;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  Vector2f initialVelocity;

  void advanceFrame(Uint32 ticks);
  Player& operator=(const Player&);
};
#endif
