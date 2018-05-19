#ifndef POTION_H
#define POTION_H
#include "item.h"
#include <string>

class Player;

class Potion : public Item {
  public:
  Potion(int x, int y, std::string type, bool a);
  virtual ~Potion();
  virtual void apply(Player *) = 0;
};

#endif
