#include "twoWayMultiSprite.h"
#include "explodingSprite.h"
#include "gamedata.h"
#include "imageFactory.h"

TwoWayMultiSprite::~TwoWayMultiSprite(){ if(explosion) delete explosion; }

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

Vector2f TwoWayMultiSprite::makeStart(int sx, int sy) const {
	float newsx;

	if(sx > 0){ newsx = Gamedata::getInstance().getRandFloat(sx-1500, sx+1500); }
	else{ newsx = sx; }

	newsx *= [](){ if(rand()%2) return -1; else return 1; }();
	sy *= [](){ return rand()%2?-1:1; }();

	return Vector2f(newsx, sy);
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
  Drawable(name,
           makeStart(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
	rightimages( ImageFactory::getInstance().getImages(name) ),
	leftimages( ImageFactory::getInstance().getImages("Left" + name) ),
	altrightimages(),
	altleftimages(),
  images(),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	useAlt(false),
	explosion(nullptr),
	isExploded(false)
{
	if( getVelocityX() < 0 ) images = leftimages;
	else if( getVelocityX() > 0 ) images = rightimages;
}

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s) :
  Drawable(s),
  rightimages(s.rightimages),
  leftimages(s.leftimages),
	altrightimages(s.altrightimages),
	altleftimages(s.altleftimages),
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

TwoWayMultiSprite& TwoWayMultiSprite::operator=(const TwoWayMultiSprite& s) {
  Drawable::operator=(s);
  rightimages = s.rightimages;
  leftimages = s.leftimages;
	altrightimages = s.altrightimages;
	altleftimages = s.altleftimages;
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

void TwoWayMultiSprite::draw() const {
	if( explosion ){
		explosion->draw();
	}
  else images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWayMultiSprite::update(Uint32 ticks) {
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

void TwoWayMultiSprite::goLeft(){
	if( useAlt ) images = altleftimages;
	else images = leftimages;
}

void TwoWayMultiSprite::goRight(){
	if( useAlt ) images = altrightimages;
	else images = rightimages;
}

void TwoWayMultiSprite::explode() {
	if( !explosion ){
		Sprite
		sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
		explosion = new ExplodingSprite(sprite);
	}
}

void TwoWayMultiSprite::createAltImages(const std::string& name){
	altrightimages = ImageFactory::getInstance().getImages(name);
	altleftimages = ImageFactory::getInstance().getImages("Left"+name);
}
