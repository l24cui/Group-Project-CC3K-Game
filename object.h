#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <sstream>
#include <cstdlib>

class Object {
  protected:
  int X;
  int Y;
  std::string Type;
  public: 
  Object(int x, int y,std::string type);
  int getX();
  int getY();
  std::string getType();
};
#endif
