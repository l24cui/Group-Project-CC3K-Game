#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "player.h"

class Vampire : public Player {
  public:
  Vampire(int x, int y, int bc, Floor *fl);
  ~Vampire();
  void reset_Atk() override;
  void reset_Def() override;
  void attack(Enemy *e) override;
};
#endif  
