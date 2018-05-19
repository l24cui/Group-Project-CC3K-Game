#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"

class Merchant : public Enemy {
  public:
  Merchant(int x, int y, Floor *fl,bool hostile);
  ~Merchant();
  void getAttack(Player *p) override;
};
#endif
