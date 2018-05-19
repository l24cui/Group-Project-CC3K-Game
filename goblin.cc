#include "goblin.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <sstream>
#include "enemy.h"
using namespace std;

Goblin::Goblin(int x, int y, int bc, Floor *fl): Player(15,20,110,"goblin",x,y,bc,fl,0,1,'.',110) {}

void Goblin::reset_Atk() {
  Atk = 15;
}

Goblin::~Goblin() {}

void Goblin::reset_Def() {
  Def = 20;
}

void Goblin::attack(Enemy *e) {
//  cout << "Attack Enemy!" << endl;
  if (e->getType() == "halfling") {
    int i = rand() % 2;
    if (i == 0) {
       e->getAttack(this);
    } else {
   // cout << "Oops~ Miss!" << endl;
      updateAction("PC Attack Miss ");
      return;
    }
  } else {
    e->getAttack(this);
  }
  string s = e->getType();
  if (e->isDead() && s != "dragon" && s != "human" && s != "merchant") {
     int g = rand() % 2 + 1;
     Gold += g;
  }
  double damage2 = ceil((100/(100 + e->getDef())) * getAtk());
  ostringstream ss;
  ss << "PC deals " << damage2 << " damage to " << e->getType() << "(HP: " << e->getHP() << ")";
  if (e->isDead()) {
      Gold += 5;
      ss <<  e->getType() << "  was killed! PC steals 5 Gold!";
      string q = ss.str();
      updateAction(q);
  } else {
    string q = ss.str();
    updateAction(q);
  }
}

void Goblin::getAttack(Enemy *e) {
  double damage = ceil((100/(100+this->getDef())) * e->getAtk());
  if (e->getType() == "orc") {
    if (HP >= 1.5 * damage) {
      HP -= 1.5 * damage;
    } else {
     HP = 0;
   }
  // cout << "Caution! Enemy deals " << 1.5 * damage << " to PC" << endl;
  } else {
    if (HP >= damage) {
        HP -= damage;
    } else {
       HP = 0;
    }
   // cout << "Caution! Enemy deals "<< damage <<" to PC" << endl;
  }
}
