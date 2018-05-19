#ifndef SHADE_H
#define SHADE_H
#include "player.h"

class Shade : public Player {
  public:
  Shade(int x, int y, int bc, Floor *fl);
  ~Shade();
  void reset_Atk() override;
  void reset_Def() override; 
};
#endif
