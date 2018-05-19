#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"

class Treasure;
class Player;

class Dragon : public Enemy {
   Treasure *hoard;
   bool canatk;
   public:
   Dragon(int x, int y, Floor *fl, Treasure *tr);
   ~Dragon();
   void setAtk();
   void setMovable() override;
   void attack(Player *p) override;
   Treasure * getHoard();
   void setHoard(Treasure *tr);
};

#endif
