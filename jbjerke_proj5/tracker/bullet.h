#ifndef BULLET__H
#define BULLET__H

#include <iostream>
#include "twoWaySprite.h"
#include "gamedata.h"

class Bullet : public TwoWaySprite {
public:
  Bullet(const string&, const Vector2f&, const Vector2f&);
  Bullet(const Bullet&);
  Bullet& operator=(const Bullet&) = delete;

  void fireDirection(const Vector2f&);
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset();
  
private:
  float distance;
  float maxDistance;
  bool tooFar;
};

#endif
