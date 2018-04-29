#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);
  ~MultiSprite();

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

  void createAltImages( const std::string& );
  void toggleAlt();

protected:
  std::vector<Image *> regularimages;
  std::vector<Image *> altimages;
  std::vector<Image *> images;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  bool useAlt;

  ExplodingSprite* explosion;
  bool isExploded;

  void advanceFrame(Uint32 ticks);
  MultiSprite& operator=(const MultiSprite&);
};
#endif
