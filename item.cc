#include "item.h"
#include <string>

using namespace std;

Item::Item(int x, int y, string type, bool a): Object(x,y,type), Avaliable{a} {}

Item::~Item() {}

bool Item::isAvaliable() {
  return Avaliable;
}

void Item::setAvaliable() {
  Avaliable = true;
}


