#include "elf.h"
#include <math.h>
#include <string>
#include <cstdlib>
#include <sstream>
#include "player.h"
using namespace std;

Elf::Elf(int x, int y, Floor *fl): Enemy(30,10,140,"elf",true,true,x,y,fl) {}

Elf::~Elf() {}

void Elf::attack(Player *p) {
  if(isHostile() && isMovable()) {
    int i = rand() % 2;
    double damage1 = ceil((100/(100 + p->getDef())) * getAtk());
    if (i == 0) {
     p->getAttack(this);
     ostringstream ss;
     ss << "first attack: Elf deals " << damage1 << " damage to PC ";
     string s = ss.str();
     p->updateAction(s);
    } else {
  // cout << "Enemy Attack Miss" << end;
     p->updateAction(" first attack: Elf Attack Miss ");
    }
    if (p->getType() != "drow") {
     int j = rand() % 2;
     if (j == 0) {
      p->getAttack(this);
      ostringstream ss;
      ss << "second attack: elf deals " << damage1 << " damage to PC ";
      string s = ss.str();
      p->updateAction(s);
     } else {
      p->updateAction("second attack: elf Attack Miss ");
     }
   }
 }
}
    
