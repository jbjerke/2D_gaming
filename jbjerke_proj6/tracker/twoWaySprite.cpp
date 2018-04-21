#include <cmath>
#include <random>
#include <functional>
#include "twoWaySprite.h"
#include "explodingSprite.h"
#include "gamedata.h"
#include "renderContext.h"

TwoWaySprite::~TwoWaySprite(){ if(explosion) delete explosion; }

Vector2f TwoWaySprite::makeVelocity(int vx, int vy) const {
  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}

TwoWaySprite::TwoWaySprite(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel),
  rightimage( ImageFactory::getInstance().getImage(n) ),
  leftimage( ImageFactory::getInstance().getImage("Left"+n) ),
  image(  ),
  explosion(nullptr),
  isExploded(false),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{
  if( vel[0] < 0 ) image = leftimage;
  if( vel[0] >= 0 ) image = rightimage;
}

TwoWaySprite::TwoWaySprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
          Vector2f(
                    Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  rightimage( ImageFactory::getInstance().getImage(name) ),
  leftimage( ImageFactory::getInstance().getImage("Left"+name) ),
  image( ),
  explosion(nullptr),
  isExploded(false),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{
  float xv = Gamedata::getInstance().getXmlInt(name+"/speedX");

  if( xv < 0 ) image = leftimage;
  if( xv >= 0 ) image = rightimage;
}

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s),
  rightimage(s.rightimage),
  leftimage(s.leftimage),
  image(s.image),
  explosion(s.explosion),
  isExploded(s.isExploded),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

TwoWaySprite& TwoWaySprite::operator=(const TwoWaySprite& rhs) {
  Drawable::operator=( rhs );
  rightimage = rhs.rightimage;
  leftimage = rhs.leftimage;
  image = rhs.image;
  explosion = rhs.explosion;
  isExploded = rhs.isExploded;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void TwoWaySprite::explode() {
  Sprite
  sprite(getName(), getPosition(), getVelocity(), image);
  explosion = new ExplodingSprite(sprite);
}

void TwoWaySprite::draw() const {
  if(getScale() < SCALE_EPSILON) return;
  if( explosion ) explosion->draw();
  else image->draw(getX(), getY(), getScale());
}

void TwoWaySprite::update(Uint32 ticks) {
  if( explosion ){
    explosion->update(ticks);
    if( explosion->chunkCount() == 0 ){
      delete explosion;
      explosion = nullptr;
      isExploded = true;
    }
    return;
  }

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( std::abs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -std::abs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( std::abs( getVelocityX() ) );
    image = rightimage;
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -std::abs( getVelocityX() ) );
    image = leftimage;
  }
}
