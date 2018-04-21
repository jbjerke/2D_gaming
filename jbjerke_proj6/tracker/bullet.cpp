#include <iostream>
#include <cmath>
#include "bullet.h"
#include "imageFactory.h"

Bullet::Bullet(const string& name, const Vector2f& pos, const Vector2f& vel) :
  TwoWaySprite(name, pos, vel),
  distance(0),
  maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")),
  tooFar(false)
{ }

Bullet::Bullet(const Bullet& b) :
  TwoWaySprite(b),
  distance(b.distance),
  maxDistance(b.maxDistance),
  tooFar(b.tooFar)
{ }

void Bullet::fireDirection(const Vector2f& vel){
  setVelocity(vel);

  if( vel[0] < 0 ) goLeft();
  else if( vel[0] > 0 ) goRight();
}

void Bullet::update(Uint32 ticks) {
  Vector2f pos = getPosition();
  TwoWaySprite::update(ticks);

  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
}

void Bullet::reset() {
  tooFar = false;
  distance = 0;
}
