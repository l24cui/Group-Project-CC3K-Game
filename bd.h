#ifndef BD_H
#define BD_H
#include "potion.h"

class Player;

class BD : public Potion {
  public:
  BD(int x, int y,bool a);
  ~BD();
  void apply(Player *p) override;
};


#endif 
