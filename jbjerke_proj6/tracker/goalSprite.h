#ifndef GOALSPRITE__H
#define GOALSPRITE__H
#include <SDL.h>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include "multisprite.h"

class GoalSprite {
public:
  GoalSprite(const std::string&, const Vector2f&, int, int);
  GoalSprite(const GoalSprite&);
  ~GoalSprite();

  void draw() const { goal->draw(); };
  void update(Uint32 ticks);

  void setPlayerPos(const Vector2f& p) { playerPos = p; }

  bool isOfferingGift() const { return offeringGift; }

  const std::string& getName() const { return goal->getName(); }
  int getX() const { return goal->getX(); }
  int getY() const { return goal->getY(); }
  const Image* getImage() const {
    return goal->getImage();
  }
  int getScaledWidth()  const {
    return goal->getScaledWidth();
  }
  int getScaledHeight()  const {
    return goal->getScaledHeight();
  }
  const SDL_Surface* getSurface() const {
    return goal->getSurface();
  }

private:
  MultiSprite* goal;
  enum MODE {NORMAL, GIFT};
  Vector2f playerPos;
  MODE currentMode;
  int playerWidth;
  int playerHeight;
  int worldWidth;
  int worldHeight;

  float rewardDistance;

  bool offeringGift;

  GoalSprite& operator=(const GoalSprite&);
};

#endif
