#ifndef DROW_H
#define DROW_H
#include "player.h"
class RH;
class BA;
class BD;
class PH;
class WA;
class WD;

class Drow : public Player {
  public:
  Drow(int x, int y,int bc, Floor *fl);
  ~Drow();
  void reset_Atk() override;
  void reset_Def() override;
  void usePotion(RH *rh) override;
  void usePotion(BA *ba) override;
  void usePotion(BD *bd) override;
  void usePotion(PH *ph) override;
  void usePotion(WA *wa) override;
  void usePotion(WD *wd) override;
};
#endif
