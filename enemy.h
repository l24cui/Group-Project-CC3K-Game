#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include <string>

class Player;

class Enemy : public Character {
  protected:
  bool Hostile;
  bool Movable;
  public:
  Enemy(double atk, double def, double hp, std::string type, bool hostile, bool movable, int x, int y, Floor *fl);
  virtual void attack(Player *p);
  virtual void getAttack(Player *p);
  bool isHostile();
  virtual ~Enemy();
  void setHostile();
  void move();
  bool isMovable();
  virtual void setMovable();
};
#endif
