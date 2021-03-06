#include <cmath>
#include <random>
#include <functional>
#include "goalSprite.h"
#include "gamedata.h"
#include "ioMod.h"

float dist(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

GoalSprite::GoalSprite(const std::string& name, const Vector2f& pos, int w, int h) :
  goal( new MultiSprite(name) ),
  playerPos(pos),
  currentMode(NORMAL),
  playerWidth(w),
  playerHeight(h),
  viewWidth( Gamedata::getInstance().getXmlInt("view/width") ),
  //worldHeight( Gamedata::getInstance().getXmlInt("world/height") ),
  rewardDistance( Gamedata::getInstance().getXmlFloat(name+"/rewardDistance") ),
  offeringGift(false),
  buffer( Gamedata::getInstance().getXmlInt("font/size") + 15 )
{
  goal->createAltImages("Reward"+name);
}

GoalSprite::GoalSprite(const GoalSprite& g) :
  goal(g.goal),
  playerPos(g.playerPos),
  currentMode(g.currentMode),
  playerWidth(g.playerWidth),
  playerHeight(g.playerHeight),
  viewWidth(g.viewWidth),
  //worldHeight(g.worldHeight),
  rewardDistance(g.rewardDistance),
  offeringGift(g.offeringGift),
  buffer(g.buffer)
{ }

GoalSprite& GoalSprite::operator=(const GoalSprite& g){
  goal=(g.goal);
  playerPos=(g.playerPos);
  currentMode = g.currentMode;
  playerWidth=(g.playerWidth);
  playerHeight=(g.playerHeight);
  viewWidth=(g.viewWidth);
  //worldHeight=(g.worldHeight);
  rewardDistance=(g.rewardDistance);
  offeringGift= g.offeringGift;
  buffer = g.buffer;
  return *this;
}

GoalSprite::~GoalSprite(){
  delete goal;
}

void GoalSprite::update(Uint32 ticks) {
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToPlayer = ::dist( x, y, ex, ey );

  if( currentMode == NORMAL && distanceToPlayer <= rewardDistance ){
    currentMode = GIFT;
    goal->toggleAlt();
    offeringGift = true;
  }
  if( currentMode == GIFT && distanceToPlayer > rewardDistance ){
    currentMode = NORMAL;
    goal->toggleAlt();
    offeringGift = false;
  }

  goal->update(ticks);
}

void GoalSprite::draw() const {
  if( offeringGift ){
    //std::cout <<  << std::endl;
    IoMod::getInstance().writeText("Press 'E' to accept Gift", viewWidth/2 + playerWidth/2,
      getImage()->getHeight() + buffer);
  }

  goal->draw();
}
