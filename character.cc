#include "character.h"
#include <string>
#include "floor.h"
using namespace std;

Character::Character(double atk, double def, double hp, string type, int x, int y,Floor *fl): Object(x,y,type),fl{fl}, Atk{atk}, Def{def}, HP{hp} {}

double Character::getAtk() {
  return Atk;
}

double Character::getDef() {
  return Def;
}

double Character::getHP() {
  return HP;
}


bool Character::isDead() {
  if (HP <= 0) {
    return true;
  } else {
    return false;
  }
}

