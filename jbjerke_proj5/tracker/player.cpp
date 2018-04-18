#include "player.h"
#include "gamedata.h"
#include "smartSprite.h"

Player::Player( const std::string& name) :
  player(name),
  observers( ),
  initialVelocity(player.getVelocity()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

Player::Player(const Player& p) :
  player(p.player),
  observers(p.observers),
  initialVelocity(p.initialVelocity),
  worldWidth(p.worldWidth),
  worldHeight(p.worldHeight)
{ }

void Player::stop() {
  player.stop();
}

void Player::right() {
  player.right();
}
void Player::left()  {
  player.left();
}

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
		++o;
	}
}

void Player::notify(){
	for ( auto* o : observers ){
		o->setPlayerPos( player.getPosition() );
	}
}
