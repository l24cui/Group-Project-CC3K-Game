#ifndef WA_H
#define WA_H
#include "potion.h"

class Player;
class WA : public Potion {
  public:
  WA(int x, int y,bool a);
  ~WA();
  void apply(Player *p) override;
};


#endif 
