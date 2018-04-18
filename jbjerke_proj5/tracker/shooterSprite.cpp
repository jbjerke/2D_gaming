#include "shooterSprite.h"
#include "gamedata.h"
#include "imageFactory.h"

void ShooterSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

ShooterSprite::ShooterSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  rightimages( ImageFactory::getInstance().getImages(name) ),
  leftimages( ImageFactory::getInstance().getImages("Left"+name) ),
  idleimages( ImageFactory::getInstance().getImages("Idle"+name) ),
	leftidleimages( ImageFactory::getInstance().getImages("LeftIdle"+name) ),
	attackimages( ImageFactory::getInstance().getImages(name+"Attack") ),
	leftattackimages( ImageFactory::getInstance().getImages("Left"+name+"Attack") ),
  images( idleimages ),
	ShooterSpriteName(name),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt("Idle"+name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	facing(RIGHT),
  initialVelocity(getVelocity())
{ }

ShooterSprite::ShooterSprite(const ShooterSprite& s) :
  Drawable(s),
  rightimages(s.rightimages),
  leftimages(s.leftimages),
  idleimages(s.idleimages),
	leftidleimages(s.leftidleimages),
	attackimages(s.attackimages),
	leftattackimages(s.leftattackimages),
  images(s.images),
	ShooterSpriteName(s.ShooterSpriteName),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
	facing(s.facing),
  initialVelocity( s.initialVelocity )
  { }

ShooterSprite& ShooterSprite::operator=(const ShooterSprite& s) {
  Drawable::operator=(s);
  rightimages = s.rightimages;
  leftimages = s.leftimages;
  idleimages = s.idleimages;
	leftidleimages = s.leftidleimages;
	attackimages = s.attackimages;
	leftattackimages = s.leftattackimages;
  images = (s.images);
	ShooterSpriteName = (s.ShooterSpriteName);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  initialVelocity = ( s.initialVelocity );
  return *this;
}

void ShooterSprite::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void ShooterSprite::stop() {
  //setVelocity( Vector2f(0, 0) );
  setVelocityX( 0.50*getVelocityX() );
  setVelocityY(0);

	if( facing == LEFT ) images = leftidleimages;
	else images = idleimages;

	numberOfFrames = Gamedata::getInstance().getXmlInt("Idle"+ShooterSpriteName+"/frames");
}

void ShooterSprite::right() {
	images = rightimages;
	facing = RIGHT;
	numberOfFrames = Gamedata::getInstance().getXmlInt(ShooterSpriteName+"/frames");
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
  }
}
void ShooterSprite::left()  {
	images = leftimages;
	facing = LEFT;
	numberOfFrames = Gamedata::getInstance().getXmlInt("Left"+ShooterSpriteName+"/frames");
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }
}

void ShooterSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
		images = rightimages;
		numberOfFrames = Gamedata::getInstance().getXmlInt(ShooterSpriteName+"/frames");
		facing = RIGHT;
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
		images = leftimages;
		numberOfFrames = Gamedata::getInstance().getXmlInt("Left"+ShooterSpriteName+"/frames");
		facing = LEFT;
  }
	if ( getX() == 0 ) {
		if( facing == LEFT ) images = leftidleimages;
		else images = idleimages;

		numberOfFrames = Gamedata::getInstance().getXmlInt("Idle"+ShooterSpriteName+"/frames");
	}
}
