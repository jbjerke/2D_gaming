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


SmartSprite::SmartSprite(const std::string& name, const std::string& type,
  const Vector2f& pos, int w, int h) :
  TwoWayMultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  smartSpriteType(PASSIVE),
  currentMode(NORMAL),
  safeDistance( Gamedata::getInstance().getXmlFloat(name+"/safeDistance") ),
  attackDistance( Gamedata::getInstance().getXmlFloat(name+"/attackDistance") ),
  playerIsExploding(false)
{
  if(type == "passive") {
    smartSpriteType = PASSIVE;
    createAltImages("Evade"+name);
  }
  else if(type == "aggressive") {
    smartSpriteType = AGGRESSIVE;
    createAltImages("Attack"+name);
  }
}


SmartSprite::SmartSprite(const SmartSprite& s) :
  TwoWayMultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  smartSpriteType(s.smartSpriteType),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance),
  attackDistance(s.attackDistance),
  playerIsExploding(s.playerIsExploding)
{}

void SmartSprite::update(Uint32 ticks) {
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL && !playerIsExploding ) {
    if( smartSpriteType == PASSIVE && distanceToEnemy < safeDistance ) {
      currentMode = EVADE;
      toggleAlt();
      //setVelocityX( (1.5)*getVelocityX() );
    }
  else if( smartSpriteType == AGGRESSIVE && distanceToEnemy < attackDistance ){
      currentMode = ATTACK;
     toggleAlt();
      setVelocityX( 2*getVelocityX() );
    }
  }
  else if  ( currentMode == EVADE ) {
    if( distanceToEnemy > safeDistance || playerIsExploding ) {
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
  else if ( currentMode == ATTACK ) {
    if( distanceToEnemy > attackDistance ) {
      currentMode = NORMAL;
      toggleAlt();
      if( getVelocityX() > 0 ) goRight();
      if( getVelocityX() < 0 ) goLeft();
    }
    else {
    if( x < ex ) goRight();
    if( x > ex ) goLeft();
    }
  }
  TwoWayMultiSprite::update(ticks);
}

int SmartSprite::getType() const {
  if( smartSpriteType == PASSIVE ) return -1;
  else if( smartSpriteType == AGGRESSIVE) return 1;
  else return 0;
}
