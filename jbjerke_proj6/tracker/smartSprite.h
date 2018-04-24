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

  virtual void explode();

  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  void setPlayerIsExploding(const bool expd ) { playerIsExploding = expd; }

  int getType() const;
  int getTimesHit() const { return timesHit; }

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
  bool playerIsExploding;
  int timesHit;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
