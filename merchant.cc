#include "merchant.h"
#include <string>
#include <math.h>
#include "player.h"
using namespace std;

Merchant::Merchant(int x, int y, Floor *fl, bool hostile): Enemy(70,5,30,"merchant",hostile,true,x,y,fl) {}

Merchant::~Merchant() {}

void Merchant::getAttack(Player *p) {
  double damage = ceil((100 / (100 + getDef())) * p->getAtk());
  if (HP >= damage) {
    HP -= damage;
  } else {
    HP = 0;
  }
  p->Atk_Mer();
}
    
