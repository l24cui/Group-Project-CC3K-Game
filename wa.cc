#include "wa.h"
#include "player.h"
using namespace std;

WA::WA(int x, int y, bool a): Potion(x,y,"WA",a) {}

WA::~WA() {}

void WA::apply(Player *p) {
  p->usePotion(this);
}

