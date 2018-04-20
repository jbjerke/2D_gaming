#include <iostream>
#include <cmath>
#include "bullet.h"
#include "imageFactory.h"

Bullet::Bullet(const string& name, const Vector2f& pos, const Vector2f& vel) :
  Sprite(name, pos, vel, ImageFactory::getInstance().getImage(name)),
  distance(0),
  maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")),
  tooFar(false)
{ }

Bullet::Bullet(const Bullet& b) :
  Sprite(b),
  distance(b.distance),
  maxDistance(b.maxDistance),
  tooFar(b.tooFar)
{ }

void Bullet::update(Uint32 ticks) {
  Vector2f pos = getPosition();
  Sprite::update(ticks);

  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
}

void Bullet::reset() {
  tooFar = false;
  distance = 0;
}
