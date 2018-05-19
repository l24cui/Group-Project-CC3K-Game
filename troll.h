#ifndef TROLL_H
#define TROLL_H
#include "player.h"
#include <string>

class Troll : public Player {
  public:
  Troll(int x, int y, int bc, Floor *fl);
  ~Troll();
  void reset_Atk() override;
  void reset_Def() override;
  void attack(Enemy *e) override;
  int move(std::string dir, std::string file) override;
  void usePotion(RH *rh) override;
  void usePotion(BA *ba) override;
  void usePotion(BD *bd) override;
  void usePotion(PH *ph) override;
  void usePotion(WA *wa) override;
  void usePotion(WD *wd) override;
};

#endif    
