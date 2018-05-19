#include "object.h"
#include <string>
using namespace std;

Object::Object(int x, int y,string type): X{x}, Y{y}, Type{type} {}

int Object::getX() {
  return X;
}

int Object::getY() {
  return Y;
}

string Object::getType() {
  return Type;
}

