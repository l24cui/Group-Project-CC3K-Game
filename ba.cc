#include "ba.h"
#include "player.h"
using namespace std;

BA::BA(int x, int y, bool a): Potion(x,y,"BA",a) {}

BA::~BA() {}

void BA::apply(Player *p) {
  p->usePotion(this);
}

