#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <math.h>
#include "object.h"

class Floor;

class Character : public Object {
  protected:
  double Atk;
  double Def;
  double HP;
  Floor *fl;
  public:
  Character(double Atk, double Def, double HP,std::string type,  int x, int y, Floor *fl);
  double getAtk();
  double getDef();
  double getHP();
  bool isDead();
};
  
#endif
