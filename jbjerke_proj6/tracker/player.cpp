#include "player.h"
#include "gamedata.h"
#include "smartSprite.h"

Player::Player( const std::string& name) :
  player( new ShooterSprite(name) ),
  observers( ),
  initialVelocity(player->getVelocity()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  lives(Gamedata::getInstance().getXmlInt(name+"/lifeCount")),
  score( 0 )
{ }

Player::Player(const Player& p) :
  player(p.player),
  observers(p.observers),
  initialVelocity(p.initialVelocity),
  worldWidth(p.worldWidth),
  worldHeight(p.worldHeight),
  lives(p.lives),
  score(p.score)
{ }

Player& Player::operator=(const Player& p){
  player = p.player;
  observers = p.observers;
  initialVelocity = p.initialVelocity;
  worldWidth = p.worldWidth;
  worldHeight = p.worldHeight;
  lives = p.lives;
  score = p.score;
  return *this;
}

Player::~Player(){
  // for( SmartSprite* ss : observers){
  //   delete ss;
  // }
  delete player;

  observers.clear();
}

void Player::update(Uint32 ticks) {
  player->update(ticks);

  stop();

  notify();
}

void Player::explode() {
  player->explode();

  notify();
}

void Player::detach( SmartSprite* ss ){
	std::list<SmartSprite*>::iterator o = observers.begin();
	while( o != observers.end() ){
		if ( *o == ss){
      score += (*o)->getScale()*(*o)->getType();
			o = observers.erase(o);
			return;
		}
		else ++o;
	}
}

void Player::notify(){
	for ( auto* o : observers ){
		o->setPlayerPos( player->getPosition() );
    o->setPlayerIsExploding( isExploding() );
	}
}
