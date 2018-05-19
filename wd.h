#ifndef WD_H
#define WD_H
#include "potion.h"

class WD : public Potion {
  public:
  WD(int x, int y,bool a);
  ~WD();
  void apply(Player *p) override;
};


#endif 
