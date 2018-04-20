#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
#include "twoWayMultiSprite.h"

//class ExplodingSprite;

class SmartSprite : public TwoWayMultiSprite {
public:
  SmartSprite(const std::string&, const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite() { }

  virtual void explode() { TwoWayMultiSprite::explode(); }

  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }

private:
  enum TYPE {AGGRESSIVE, PASSIVE};
  enum MODE {NORMAL, EVADE, ATTACK};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  TYPE smartSpriteType;
  MODE currentMode;
  float safeDistance;
  float attackDistance;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
