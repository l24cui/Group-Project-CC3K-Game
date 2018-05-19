#include "enemy.h"
#include <string>
#include <cstdlib>
#include <math.h>
#include "player.h"
#include "floor.h"
using namespace std;

Enemy::Enemy(double atk, double def, double hp, string type, bool hostile, bool movable, int x, int y, Floor *fl): Character(atk,def,hp,type,x,y,fl), Hostile{hostile}, Movable{movable} {}

bool Enemy::isHostile() {
  return Hostile;
}

Enemy::~Enemy() {}

bool Enemy::isMovable() {
  return Movable;
}

void Enemy::setHostile() {
  Hostile = true;
}

void Enemy::setMovable() {
  if (isMovable()) {
     Movable = false;
  } else {
     Movable = true;
  }
}

void Enemy::move() {
  if (isMovable()) {
    while (true) {
     int x = rand() % 3 - 1;
     int y = rand() % 3 - 1;
     int new_x = X + x;
     int new_y = Y + y;
     if (fl->getChar(new_x,new_y) == '.') {
       if (getType() == "halfling") {
          fl->modifyFloor(new_x,new_y,'L');
       } else if (getType() == "merchant") {
          fl->modifyFloor(new_x,new_y,'M');
       } else if (getType() == "orc") {
          fl->modifyFloor(new_x,new_y, 'O');
       } else if (getType() == "elf") {
          fl->modifyFloor(new_x,new_y,'E');
       } else if (getType() == "dwarf") {
          fl->modifyFloor(new_x,new_y,'W');
       } else {
          fl->modifyFloor(new_x,new_y,'H');
       }
       fl->modifyFloor(X,Y,'.');
       X = new_x;
       Y = new_y;
       break;
     }
    }
  }
}          

void Enemy::attack(Player *p) {
  if (isHostile() && isMovable()) {
      int i = rand() % 2;
      if ( i == 0) {
         p->getAttack(this);
         double damage = ceil((100/(100 + p->getDef())) * getAtk());
         ostringstream ss;
         ss << getType() << " deals " << damage << " to PC";
         string s = ss.str();
         p->updateAction(s);
      } else {
        p->updateAction(getType() + "  Attack Miss");
      }
  }
}

void Enemy::getAttack(Player *p) {
  double damage = ceil((100/(100+getDef())) * p->getAtk());
  if (HP >= damage) {
     HP -= damage;
  } else {
    HP = 0;
  }
}

                 
