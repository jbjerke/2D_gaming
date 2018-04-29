#include "multisprite.h"
#include "gamedata.h"
#include "imageFactory.h"
#include "explodingSprite.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
	regularimages( ImageFactory::getInstance().getImages(name) ),
	altimages(),
	images( regularimages ),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	useAlt(false),
	explosion(nullptr),
	isExploded(false)
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s),
	regularimages(s.regularimages),
	altimages(s.altimages),
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
	useAlt(s.useAlt),
	explosion(s.explosion),
	isExploded(s.isExploded)
  { }

	MultiSprite::~MultiSprite(){ if( explosion ) delete explosion;}

MultiSprite& MultiSprite::operator=(const MultiSprite& s) {
  Drawable::operator=(s);
	regularimages = s.regularimages;
	altimages = s.altimages;
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
	useAlt = s.useAlt;
	explosion = s.explosion;
	isExploded = s.isExploded;
  return *this;
}

void MultiSprite::draw() const {
	if(explosion) explosion->draw();
  else images[currentFrame]->draw(getX(), getY(), getScale());
}

void MultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

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
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }
}

void MultiSprite::explode() {
	if( !explosion ){
		Sprite
		sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
		explosion = new ExplodingSprite(sprite);
	}
}

void MultiSprite::createAltImages(const std::string& name){
	altimages = ImageFactory::getInstance().getImages(name);
}

void MultiSprite::toggleAlt(){
	std::cout << "1" << std::endl;
	useAlt = !useAlt;

	if( useAlt ) images = altimages;
	else images = regularimages;
}
