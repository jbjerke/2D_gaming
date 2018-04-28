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
  ~Player();

  void draw() const { player->draw(); }
  void update(Uint32 ticks);
  void explode();
  bool isExploding() { return player->isExploding(); }

  const ShooterSprite* getPlayer() const { return player; }

  const std::string& getName() const { return player->getName(); }
  int getX() const { return player->getX(); }
  int getY() const { return player->getY(); }
  const Image* getImage() const {
    return player->getImage();
  }
  int getScaledWidth()  const {
    return player->getScaledWidth();
  }
  int getScaledHeight()  const {
    return player->getScaledHeight();
  }
  const SDL_Surface* getSurface() const {
    return player->getSurface();
  }

  void right() { player->right(); }
  void left() { player->left(); }
  void stop() { player->stop(); }
  void heAttak() { player->shoot(); }
  bool heHitSomething(const Drawable* d) const { return player->shotSomething(d); }
  int getScore() const { return score; }
  int getLifeCount() const { return lives; }
  bool playerWins() const { return score >= winningScore; }
  bool playerDed() const { return !lives; }

  void attach( SmartSprite* ss ) { observers.push_back(ss); }
  void detach( SmartSprite* ss );
  void notify( );

private:
  ShooterSprite* player;
  std::list<SmartSprite *> observers;
  Vector2f initialVelocity;
  int worldWidth;
  int worldHeight;
  int lives;
  int score;
  int winningScore;

  Player& operator=(const Player&);
};
#endif
