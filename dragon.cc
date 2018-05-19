#include "dragon.h"
#include "player.h"
#include <string>

using namespace std;

Dragon::Dragon(int x, int y, Floor *fl, Treasure *tr): Enemy(20,20,150,"dragon",true,false,x,y,fl), canatk{true},hoard{tr} {}

Dragon::~Dragon() {}

void Dragon::setMovable() {
  Movable = false;
}

void Dragon::setAtk() {
  if (canatk) {
     canatk = false;
  } else {
     canatk = true;
  }
}

Treasure *Dragon::getHoard() {
  return hoard;
}

void Dragon::attack(Player *p) {
  if (isHostile()&& canatk) {
      int i = rand() % 2;
      if ( i == 0) {
         p->getAttack(this);
         double damage = ceil((100/(100 + p->getDef())) * getAtk());
         ostringstream ss;
         ss << "Dragon deals " << damage << " to PC";
         string s = ss.str();
         p->updateAction(s);
      } else {
        p->updateAction(" Dragon Attack Miss");
      }
  }
}

void Dragon::setHoard(Treasure *tr) {
   hoard = tr;
}

