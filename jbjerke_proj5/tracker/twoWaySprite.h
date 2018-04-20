#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include "drawable.h"

class ExplodingSprite;

class TwoWaySprite : public Drawable {
public:
  TwoWaySprite(const std::string&);
  TwoWaySprite(const std::string&, const Vector2f& pos, const Vector2f& vel);
  TwoWaySprite(const TwoWaySprite&);
  ~TwoWaySprite();
  TwoWaySprite& operator=(const TwoWaySprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual void explode();
  virtual bool isDoneExploding() const { return isExploded; }
  virtual bool isExploding() const { return explosion; }

  virtual const Image* getImage() const { return image; }
  virtual const SDL_Surface* getSurface() const {
    return image->getSurface();
  }
  int getScaledWidth()  const { return getScale()*image->getWidth();  }
  int getScaledHeight() const { return getScale()*image->getHeight(); }

private:
  Image * rightimage;
  Image * leftimage;
  Image * image;

  ExplodingSprite* explosion;
  bool isExploded;

  int worldWidth;
  int worldHeight;

  int getDistance(const TwoWaySprite*) const;
  Vector2f makeVelocity(int, int) const;
};
#endif
