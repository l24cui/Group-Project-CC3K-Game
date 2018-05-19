#include "treasure.h"
#include <string>
using namespace std;


Treasure::Treasure(int x, int y, string type, int v, bool a): Item(x,y,type,a), value{v}{}

Treasure::~Treasure() {}

int Treasure::getValue() {
  return value;
}


