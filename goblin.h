#ifndef GOBLIN_H
#define GOBLIN_H
#include "player.h"

class Goblin : public Player {
  public:
  Goblin(int x, int y, int bc,Floor *fl);
  ~Goblin();
  void reset_Atk() override;
  void reset_Def() override;
  void attack(Enemy *e) override;
  void getAttack(Enemy *e) override;
};
#endif
