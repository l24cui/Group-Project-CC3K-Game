#include "vampire.h"
#include <cstdlib>
#include <string>
#include "enemy.h"
#include <math.h>
#include <sstream>
using namespace std;

Vampire::Vampire(int x, int y,int bc,Floor *fl): Player(25,25,50,"vampire",x,y,bc,fl,0,1,'.',0) {}

void Vampire::reset_Atk() {
  Atk = 25;
}

Vampire::~Vampire() {}


void Vampire::reset_Def() {
  Def = 25;
}

void Vampire::attack(Enemy *e) {
//  cout << "PC Attacks Enemy!" << endl;
  if (e->getType() == "dwarf") {
    e->getAttack(this);
    if (HP >= 5) {
        HP -= 5;
    } else {
        HP = 0;
    }
  } else if (e->getType() == "halfling") {
    int i = rand() % 2;
    if ( i == 0) {
      e->getAttack(this);
      HP += 5;
    } else {
     // cout << "Oops~ Miss!" << endl;
      updateAction("PC Attack Miss! ");
      return;
    }
  } else {
    e->getAttack(this);
    HP += 5;
  }
  if (e->isDead() && e->getType() != "dragon" && e->getType() != "human" && e->getType() != "merchant") {
   int g = rand() % 2 + 1;
   Gold += g;
  }
  double d1 = ceil((100/(100 + e->getDef())) * getAtk());
  ostringstream ss;
  ss << "PC deals " << d1 <<" damage to " << e->getType() << "(HP: " << e->getHP() << ")";
  if (e->isDead()) {
      ss << e->getType() << " was killed";
      string l = ss.str();
      updateAction(l);
  } else {
      string l = ss.str();
      updateAction(l);
  }
}
