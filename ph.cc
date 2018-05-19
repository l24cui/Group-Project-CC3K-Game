#include "ph.h"
#include "player.h"
using namespace std;

PH::PH(int x, int y, bool a): Potion(x,y,"PH",a) {}

PH::~PH() {}

void PH::apply(Player *p) {
  p->usePotion(this);
}

