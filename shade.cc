#include "shade.h"
#include <string>
using namespace std;

Shade::Shade(int x, int y, int bc, Floor *fl): Player(25, 25, 125,"shade", x, y, bc, fl, 0, 1, '.', 125) {}

Shade::~Shade() {}

void Shade::reset_Atk() {
   Atk = 25;
}

void Shade::reset_Def() {
  Def = 25;
}

