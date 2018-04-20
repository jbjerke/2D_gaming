#include "player.h"
#include "gamedata.h"
#include "smartSprite.h"

Player::Player( const std::string& name) :
  player(name),
  observers( ),
  initialVelocity(player.getVelocity()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  lives(Gamedata::getInstance().getXmlInt(name+"/lifeCount"))
{ }

Player::Player(const Player& p) :
  player(p.player),
  observers(p.observers),
  initialVelocity(p.initialVelocity),
  worldWidth(p.worldWidth),
  worldHeight(p.worldHeight),
  lives(p.lives)
{ }

void Player::update(Uint32 ticks) {
  player.update(ticks);

  stop();

  notify();
}

void Player::detach( SmartSprite* ss ){
	std::list<SmartSprite*>::iterator o = observers.begin();
	while( o != observers.end() ){
		if ( *o == ss){
			o = observers.erase(o);
			return;
		}
		else ++o;
	}
}

void Player::notify(){
	for ( auto* o : observers ){
		o->setPlayerPos( player.getPosition() );
	}
}
