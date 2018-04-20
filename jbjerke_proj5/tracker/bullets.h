#ifndef BULLETS__H
#define BULLETS__H

#include <list>
#include "bullet.h"

class CollisionStrategy;

class Bullets {
public:
  Bullets(const std::string&);
  Bullets(const Bullets&);
  Bullets& operator=(const Bullets&) = delete;
  ~Bullets();

  void draw() const;
  void update(Uint32 ticks);
  void shoot(const Vector2f&, const Vector2f&);

  unsigned int bulletCount() const { return bulletList.size(); }
  unsigned int freeCount() const { return freeList.size(); }

  bool shooting() const { return !bulletList.empty(); }
  bool collided(const Drawable*) const;

private:
  std::string bulletName;
  Vector2f bulletVelocity;
  Image* bulletImage;
  std::list<Bullet*> bulletList;
  std::list<Bullet*> freeList;
  CollisionStrategy* strategy;
  unsigned int maxNumOFBullets;
};
#endif
