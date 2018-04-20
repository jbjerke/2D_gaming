#include "shooterSprite.h"
#include "explodingSprite.h"
#include "gamedata.h"
#include "imageFactory.h"

void ShooterSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	timeSinceLastBullet += ticks;
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
  rightidleimages( ImageFactory::getInstance().getImages("Idle"+name) ),
	leftidleimages( ImageFactory::getInstance().getImages("LeftIdle"+name) ),
	rightattackimages( ImageFactory::getInstance().getImages(name+"Attack") ),
	leftattackimages( ImageFactory::getInstance().getImages("Left"+name+"Attack") ),
  images( rightidleimages ),
	ShooterSpriteName(name),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt("Idle"+name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	facing(RIGHT),
  initialVelocity(getVelocity()),
	explosion(nullptr),
	isExploded(false),
	bulletName( Gamedata::getInstance().getXmlStr(name+"/bulletName") ),
	bullets(bulletName),
	minBulletSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/minSpeedX") ),
	bulletInterval( Gamedata::getInstance().getXmlInt(bulletName+"/interval") ),
	timeSinceLastBullet(0)
{ }

ShooterSprite::ShooterSprite(const ShooterSprite& s) :
  Drawable(s),
  rightimages(s.rightimages),
  leftimages(s.leftimages),
  rightidleimages(s.rightidleimages),
	leftidleimages(s.leftidleimages),
	rightattackimages(s.rightattackimages),
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
  initialVelocity( s.initialVelocity ),
	explosion(s.explosion),
	isExploded(false),
	bulletName(s.bulletName),
	bullets(s.bullets),
	minBulletSpeed(s.minBulletSpeed),
	bulletInterval(s.bulletInterval),
	timeSinceLastBullet(s.timeSinceLastBullet)
{ }

ShooterSprite& ShooterSprite::operator=(const ShooterSprite& s) {
  Drawable::operator=(s);
  rightimages = s.rightimages;
  leftimages = s.leftimages;
  rightidleimages = s.rightidleimages;
	leftidleimages = s.leftidleimages;
	rightattackimages = s.rightattackimages;
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
	explosion = s.explosion;
	isExploded = s.isExploded;
	bulletName = s.bulletName;
	bulletInterval = s.bulletInterval;
	timeSinceLastBullet = s.timeSinceLastBullet;
	minBulletSpeed = s.minBulletSpeed;
	//bullets = s.bullets;
  return *this;
}

ShooterSprite::~ShooterSprite(){ if(explosion) delete explosion; }

void ShooterSprite::draw() const {
	bullets.draw();
	if(explosion) explosion->draw();
  else images[currentFrame]->draw(getX(), getY(), getScale());
}

void ShooterSprite::stop() {
  //setVelocity( Vector2f(0, 0) );
  setVelocityX( 0.50*getVelocityX() );
  setVelocityY(0);

	if( facing == LEFT ) images = leftidleimages;
	else images = rightidleimages;

	numberOfFrames = Gamedata::getInstance().getXmlInt("Idle"+ShooterSpriteName+"/frames");
}

void ShooterSprite::right() {
	if( !isShooting() ) images = rightimages;
	facing = RIGHT;
	numberOfFrames = Gamedata::getInstance().getXmlInt(ShooterSpriteName+"/frames");
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
  }
}
void ShooterSprite::left()  {
	if( !isShooting() ) images = leftimages;
	facing = LEFT;
	numberOfFrames = Gamedata::getInstance().getXmlInt("Left"+ShooterSpriteName+"/frames");
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }
}

void ShooterSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

	bullets.update(ticks);

	if ( explosion ){
		explosion->update(ticks);

		if ( explosion->chunkCount() == 0 ){
			delete explosion;
			explosion = nullptr;
			isExploded = true;
		}
		return;
	}

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
		if( facing == LEFT && !isShooting() ) images = leftidleimages;
		else if (facing == RIGHT && !isShooting() ) images = rightidleimages;

		numberOfFrames = Gamedata::getInstance().getXmlInt("Idle"+ShooterSpriteName+"/frames");
	}
}

void ShooterSprite::explode() {
	if( !explosion ) {
		Sprite
		sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
		explosion = new ExplodingSprite(sprite);
	}
}

void ShooterSprite::shoot() {
	if ( getVelocityX() > 0 ) { images = rightattackimages; }
	else if( getVelocityX() < 0 ) { images = leftattackimages; }
	else if( facing == RIGHT ) { images = rightattackimages; }
	else if( facing == LEFT ) { images = leftattackimages; }

	numberOfFrames = Gamedata::getInstance().getXmlInt(ShooterSpriteName+"Attack/frames");

	// See if it's okay to shoot now:
	if( timeSinceLastBullet > bulletInterval ){
		Vector2f vel = getVelocity();
		float x;
		float y = getY() + getScaledHeight()/2; //CHANGE

		if( facing == RIGHT ){
			x = getX() + getScaledWidth();
			vel[0] += minBulletSpeed;
		}
		else if( facing == LEFT ){
			x = getX();
			vel[0] -= minBulletSpeed;
		}

		bullets.shoot( Vector2f(x,y), vel );
		timeSinceLastBullet = 0;
	}
}
