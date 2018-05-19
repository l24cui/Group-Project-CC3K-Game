#include "wd.h"
#include "player.h"
using namespace std;

WD::WD(int x, int y, bool a): Potion(x,y,"WD",a) {}

WD::~WD() {}

void WD::apply(Player *p) {
  p->usePotion(this);
}

