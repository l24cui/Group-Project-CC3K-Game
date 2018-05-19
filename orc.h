#ifndef ORC_H
#define ORC_H
#include "enemy.h"
#include <string>

class Orc : public Enemy {
  public:
  Orc(int x, int y, Floor *fl);
  ~Orc();
};
#endif
