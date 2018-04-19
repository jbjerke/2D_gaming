#include "twoWayMultiSprite.h"
#include "explodingSprite.h"
#include "gamedata.h"
#include "imageFactory.h"

void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

Vector2f TwoWayMultiSprite::makeVelocity(int vx, int vy) const {
  float newvx;
	float newvy;

	if(vx > 0){ newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50); }
	else{ newvx = vx; }

	if(vy > 0){ newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50); }
	else { newvy = vy; }


  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
	rightimages( ImageFactory::getInstance().getImages(name) ),
	leftimages( ImageFactory::getInstance().getImages("Left" + name) ),
  images( leftimages ),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	explosion(nullptr),
	isExploded(false)
{ }

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s) :
  Drawable(s),
  rightimages(s.rightimages),
  leftimages(s.leftimages),
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
	explosion(s.explosion),
	isExploded(s.isExploded)
{ }

TwoWayMultiSprite& TwoWayMultiSprite::operator=(const TwoWayMultiSprite& s) {
  Drawable::operator=(s);
  rightimages = s.rightimages;
  leftimages = s.leftimages;
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
	explosion = s.explosion;
	isExploded = s.isExploded;
  return *this;
}

void TwoWayMultiSprite::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWayMultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()-250) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    goRight();
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
    goLeft();
  }

}

void TwoWayMultiSprite::explode() {}
