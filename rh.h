#ifndef RH_H
#define RH_H
#include "potion.h"

class Player;
class RH : public Potion {
  public:
  RH(int x, int y,bool a);
  ~RH();
  void apply(Player *p) override;
};


#endif 
