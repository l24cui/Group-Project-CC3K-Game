#ifndef TREASURE_H
#define TREASURE_H
#include "item.h"
class floor;

class Treasure : public Item {
  int value;
  public:
  Treasure(int x, int y,std::string type, int v, bool a);
  ~Treasure();
  int getValue();
};


#endif
