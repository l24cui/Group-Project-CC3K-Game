#include "bd.h"
#include "player.h"
using namespace std;

BD::BD(int x, int y, bool a): Potion(x,y,"BD",a) {}

BD::~BD() {}

void BD::apply(Player *p) {
  p->usePotion(this);
}

