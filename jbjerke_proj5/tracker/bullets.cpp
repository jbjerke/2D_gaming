#include <iostream>
#include <cmath>
#include "ioMod.h"
#include "bullets.h"
#include "imageFactory.h"
#include "collisionStrategy.h"

Bullets::~Bullets() {
  for( Bullet* bl : bulletList ){
    delete bl;
  }

  for( Bullet* fl : freeList ){
    delete fl;
  }

  bulletList.clear();
  freeList.clear();

  delete strategy;
}

Bullets::Bullets(const std::string& name) :
  bulletName(name),
  bulletVelocity(
    Gamedata::getInstance().getXmlInt(name+"/speedX"),
    Gamedata::getInstance().getXmlInt(name+"/speedY")
  ),
  bulletImage( ImageFactory::getInstance().getImage(name) ),
  bulletList(),
  freeList(),
  strategy(nullptr),
  maxNumOFBullets( Gamedata::getInstance().getXmlInt(name+"/maxCount") )
{
    //if statements for which collision
    const std::string thisStrat = Gamedata::getInstance().getXmlStr("collisionStrategy");
    if( thisStrat == "Rectangular" ){
      strategy = new RectangularCollisionStrategy;
    }
    else if ( thisStrat == "MidPoint" ){
      strategy = new MidPointCollisionStrategy;
    }
    else if ( thisStrat == "PerPixel" ){
      strategy = new PerPixelCollisionStrategy;
    }
}

Bullets::Bullets(const Bullets& b):
  bulletName(b.bulletName),
  bulletVelocity(b.bulletVelocity),
  bulletImage(b.bulletImage),
  bulletList(b.bulletList),
  freeList(b.freeList),
  strategy(b.strategy),
  maxNumOFBullets(b.maxNumOFBullets)
{  }

void  Bullets::shoot(const Vector2f& pos, const Vector2f& objVel){
  if( freeList.empty() && bulletList.size() <= maxNumOFBullets ){
    Bullet* b = new Bullet( bulletName, pos, objVel );
    bulletList.push_back(b);
  }
  else if( !freeList.empty() ){
    Bullet* b = freeList.front();
    freeList.pop_front();
    b->reset();
    b->fireDirection(objVel);
    b->setPosition(pos);
    bulletList.push_back( b );
  }
}

bool Bullets::collided(const Drawable* obj) const {
  for( const auto& bt : bulletList ){
    if( strategy->execute(*bt, *obj) ){
      // move to freeList somehow
      return true;
    }
  }
  return false;
}

void Bullets::draw() const {
  for( const auto& bt : bulletList){
    bt->draw();
  }
}

void Bullets::update(Uint32 ticks) {
  auto bllt = bulletList.begin();
  while( bllt != bulletList.end() ){
    (*bllt)->update(ticks);
    if( (*bllt)->goneTooFar() ){
      freeList.push_back(*bllt);
      bllt = bulletList.erase(bllt);
    }
    else ++bllt;
  }
}
