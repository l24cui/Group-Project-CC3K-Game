#include "drow.h"
#include <string>
#include "rh.h"
#include "ba.h"
#include "bd.h"
#include "ph.h"
#include "wa.h"
#include "wd.h"
using namespace std;

Drow::Drow(int x, int y,int bc, Floor *fl): Player(25, 15, 150,"drow", x, y,bc,fl, 0, 1, '.',150) {}

Drow::~Drow() {}

void Drow::reset_Atk() {
  Atk = 25;
}

void Drow::reset_Def() {
  Def = 15;
}

void Drow::usePotion(RH *rh) {
  if (HP + 10 * 1.5 >= Max_HP) {
      HP = Max_HP;
  } else {
      HP += 10 * 1.5;
  }
  use_RH = true;
  Action = "PC uses RH";
  potion_move(getX(),getY(),rh->getX(),rh->getY());
}

void Drow::usePotion(BA *ba) {
  Atk += 1.5 * 5;
  Action = "PC uses BA";
  use_BA = true;
  potion_move(getX(),getY(),ba->getX(),ba->getY());
}

void Drow::usePotion(BD *bd) {
  Def += 1.5 * 5;
  use_BD = true;
  Action = "PC uses BD";
  potion_move(getX(),getY(),bd->getX(),bd->getY());
}

void Drow::usePotion(PH *ph) {
  if (HP - 10 * 1.5 >= 0) {
     HP -= 10 * 1.5;
  } else {
    HP = 0;
  }
  use_PH = true;
  Action = "PC uses PH";
  potion_move(getX(),getY(),ph->getX(),ph->getY());
}

void Drow::usePotion(WA *wa) {
  if (Atk - 5 * 1.5 >= 0) {
    Atk -= 5 * 1.5;
  } else {
    Atk = 0;
  }
  use_WA = true;
  Action = "PC uses WA";
  potion_move(getX(),getY(),wa->getX(),wa->getY());
}

void Drow::usePotion(WD *wd) {
  if (Def - 1.5 * 5 >= 0) {
      Def -= 5 * 1.5;
  } else {
      Def = 0;
  }
  use_WD = true;
  Action = "PC uses WD";
  potion_move(getX(),getY(),wd->getX(),wd->getY());
}

