#ifndef PLAYER__H
#define PLAYER__H
#include <SDL.h>
#include <string>
#include <vector>
#include <list>
#include <cmath>

#include "shooterSprite.h"

class SmartSprite;

class Player {
public:
  Player(const std::string&);
  Player(const Player&);

  void draw() const { player.draw(); }
  void update(Uint32 ticks);
  const ShooterSprite* getPlayer() const { return &player; }

  const std::string& getName() const { return player.getName(); }
  int getX() const { return player.getX(); }
  int getY() const { return player.getY(); }
  const Image* getImage() const {
    return player.getImage();
  }
  int getScaledWidth()  const {
    return player.getScaledWidth();
  }
  int getScaledHeight()  const {
    return player.getScaledHeight();
  }
  const SDL_Surface* getSurface() const {
    return player.getSurface();
  }

  void right() { player.right(); }
  void left() { player.left(); }
  void stop() { player.stop(); }

  void attach( SmartSprite* ss ) { observers.push_back(ss); }
  void detach( SmartSprite* ss );
  void notify( );

private:
  ShooterSprite player;
  std::list<SmartSprite *> observers;
  Vector2f initialVelocity;
  int worldWidth;
  int worldHeight;
};
#endif
