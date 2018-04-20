#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class TwoWayMultiSprite : public Drawable {
public:
  TwoWayMultiSprite(const std::string&);
  TwoWayMultiSprite(const TwoWayMultiSprite&);
  ~TwoWayMultiSprite();

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

  void goLeft();
  void goRight();

  void createAltImages(const std::string&);
  void toggleAlt(){ useAlt = !useAlt; }

private:
  std::vector<Image *> rightimages;
  std::vector<Image *> leftimages;
  std::vector<Image *> altrightimages;
  std::vector<Image *> altleftimages;
  std::vector<Image *> images;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  bool useAlt;

  Vector2f makeVelocity(int, int) const;
  Vector2f makeStart(int, int) const;

  ExplodingSprite* explosion;
  bool isExploded;

  void advanceFrame(Uint32 ticks);
  TwoWayMultiSprite& operator=(const TwoWayMultiSprite&);
};
#endif
