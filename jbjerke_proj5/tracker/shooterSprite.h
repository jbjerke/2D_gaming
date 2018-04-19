#ifndef ShooterSprite__H
#define ShooterSprite__H
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include "drawable.h"

class ExplodingSprite;

class ShooterSprite : public Drawable {
public:
  ShooterSprite(const std::string&);
  ShooterSprite(const ShooterSprite&);
  ~ShooterSprite();

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual void explode();
  virtual bool isExploding() const { return explosion; }
  virtual bool isDoneExploding() const { return isExploded; }

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
  void stop();

private:
  std::vector<Image *> rightimages;
  std::vector<Image *> leftimages;
  std::vector<Image *> idleimages;
  std::vector<Image *> leftidleimages;
  std::vector<Image *> attackimages;
  std::vector<Image *> leftattackimages;
  std::vector<Image *> images;

  std::string ShooterSpriteName;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  enum DIRECTION {LEFT, RIGHT};
  DIRECTION facing;

  Vector2f initialVelocity;

  ExplodingSprite* explosion;
  bool isExploded;

  void advanceFrame(Uint32 ticks);
  ShooterSprite& operator=(const ShooterSprite&);
};
#endif
