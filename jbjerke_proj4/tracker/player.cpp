#include "player.h"
#include "gamedata.h"
#include "imageFactory.h"
#include "smartSprite.h"

void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

Player::Player( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  rightimages( ImageFactory::getInstance().getImages(name) ),
  leftimages( ImageFactory::getInstance().getImages("Left"+name) ),
  idleimages( ImageFactory::getInstance().getImages("Idle"+name) ),
  images( idleimages ),
	observers(),
	playerName(name),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt("Idle"+name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  initialVelocity(getVelocity())
{ }

Player::Player(const Player& s) :
  Drawable(s),
  rightimages(s.rightimages),
  leftimages(s.leftimages),
  idleimages(s.idleimages),
  images(s.images),
	observers(s.observers),
	playerName(s.playerName),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  initialVelocity( s.initialVelocity )
  { }

Player& Player::operator=(const Player& s) {
  Drawable::operator=(s);
  rightimages = s.rightimages;
  leftimages = s.leftimages;
  idleimages = s.idleimages;
  images = (s.images);
	observers = (s.observers);
	playerName = (s.playerName);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  initialVelocity = ( s.initialVelocity );
  return *this;
}

void Player::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void Player::stop() {
  //setVelocity( Vector2f(0, 0) );
  setVelocityX( 0.50*getVelocityX() );
  setVelocityY(0);
	images = idleimages;
	numberOfFrames = Gamedata::getInstance().getXmlInt("Idle"+playerName+"/frames");
}

void Player::right() {
	images = rightimages;
	numberOfFrames = Gamedata::getInstance().getXmlInt(playerName+"/frames");
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
  }
}
void Player::left()  {
	images = leftimages;
	numberOfFrames = Gamedata::getInstance().getXmlInt("Left"+playerName+"/frames");
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }
}
// void Player::up()    {
//   if ( getY() > 0) {
//     setVelocityY( -initialVelocity[1] );
//   }
// }

void Player::update(Uint32 ticks) {
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
		numberOfFrames = Gamedata::getInstance().getXmlInt(playerName+"/frames");
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
		images = leftimages;
		numberOfFrames = Gamedata::getInstance().getXmlInt("Left"+playerName+"/frames");
  }
	if ( getX() == 0 ) {
		images = idleimages;
		numberOfFrames = Gamedata::getInstance().getXmlInt("Idle"+playerName+"/frames");
	}

  stop();

	notify();
}

void Player::detach( SmartSprite* ss ){
	std::cout << "omfg" << std::endl;
	std::list<SmartSprite*>::iterator o = observers.begin();
	while( o != observers.end() ){
		if ( *o == ss){
			o = observers.erase(o);
			std::cout << "can we please" << std::endl;
			return;
		}
		++o;
	}
	std::cout << "can we please" << std::endl;
}

void Player::notify(){
	for ( auto* o : observers ){
		o->setPlayerPos( getPosition() );
	}
}
