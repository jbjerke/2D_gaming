#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gamedata.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void SmartSprite::goLeft()  {
  setVelocityX( -abs(getVelocityX()) );
  TwoWayMultiSprite::goLeft();
}
void SmartSprite::goRight() {
  setVelocityX( fabs(getVelocityX()) );
  TwoWayMultiSprite::goRight();
}


SmartSprite::SmartSprite(const std::string& name, const Vector2f& pos,
  int w, int h) :
  TwoWayMultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance"))
{
  TwoWayMultiSprite::createAltImages("Evade"+name);
}


SmartSprite::SmartSprite(const SmartSprite& s) :
  TwoWayMultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance)
{}

void SmartSprite::update(Uint32 ticks) {
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < safeDistance) {
      currentMode = EVADE;
      toggleAlt();
      //setVelocityX( (1.5)*getVelocityX() );
    }
  }
  else if  ( currentMode == EVADE ) {
    if(distanceToEnemy > safeDistance) {
      currentMode = NORMAL;
      toggleAlt();
      if( getVelocityX() > 0 ) goRight();
      if( getVelocityX() < 0 ) goLeft();
    }
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
    }
  }
  TwoWayMultiSprite::update(ticks);
}
