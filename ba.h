#ifndef BA_H
#define BA_H
#include "potion.h"
class Player;

class BA : public Potion {
  public:
  BA(int x, int y,bool a);
  ~BA();
  void apply(Player *p) override;
};


#endif 
