#ifndef PH_H
#define PH_H
#include "potion.h"
class Player;

class PH : public Potion {
  public:
  PH(int x, int y,bool a);
  ~PH();
  void apply(Player *p) override;
};


#endif 
