#ifndef DWARF_H
#define DWARF_H
#include "enemy.h"
#include <string>

class Dwarf : public Enemy {
  public:
  Dwarf(int x, int y, Floor *fl);
  ~Dwarf();
};  


#endif







