#include "troll.h"
#include <string>
#include <math.h>
#include <cstdlib>
#include "enemy.h"
#include "treasure.h"
#include "potion.h"
#include "rh.h"
#include "ba.h"
#include "bd.h"
#include "ph.h"
#include "wa.h"
#include "wd.h"
#include "floor.h"

using namespace std;

Troll::Troll(int x,int y,int bc, Floor *fl): Player(25,15,120,"troll",x,y,bc,fl,0,1,'.',120) {}

Troll::~Troll() {}

void Troll::reset_Atk() {
  Atk = 25;
}

void Troll::reset_Def() {
  Def = 15;
}

void Troll::attack(Enemy *e) {
//  cout <<"Attack Enemy!"<< endl;
  if (HP + 5 <= Max_HP) {
    HP += 5;
  } else {
    HP = Max_HP;
  }
  if (e->getType() == "halfling") {
    int i;
    i = rand() % 2;
    if (i == 0) {
      e->getAttack(this);
    } else {
   // cout << "Oops~ Miss!" << endl;
    ostringstream ss;
    ss << "Oops~ PC Attack Miss!";
    string s = ss.str();
    updateAction(s);
    return;
    }
  }else {
    e->getAttack(this);
  }
  if (e->isDead() && e->getType() != "dragon" && e->getType() != "human" && e->getType() != "merchant") {
   int g = rand() % 2 + 1;
   Gold += g;
  }
  double damage1 = ceil((100/(100 + e->getDef())) * getAtk());
  ostringstream ss;
  ss << "PC deals " << damage1 << " damage to " << e->getType() << "(HP: " << e->getHP() << ")";
  string p = ss.str();
  updateAction(p);
  if (e->isDead()) {
     updateAction( e->getType() + "  was killed");
  }
}


int Troll::move(string dir, string file) {
  int old_x = getX();
  int old_y = getY();
  int new_x = old_x;
  int new_y = old_y;
  if (dir == "no") {
    new_y -= 1;
    Action = "PC moves North ";
  } else if (dir == "so") { 
    new_y += 1;
    Action = "PC moves South ";
  } else  if (dir == "ea") {
    new_x += 1;
    Action = "PC moves East ";
  } else if (dir == "we") {
    new_x -= 1;
    Action = "PC moves West ";
  } else if (dir == "ne") {
    new_x += 1;
    new_y -= 1;
    Action = "PC moves North East ";
  } else if (dir == "nw") {
    new_x -= 1;
    new_y -= 1;
    Action = "PC moves North West ";
  } else if (dir == "se") {
    new_x += 1;
    new_y += 1;
    Action = "PC moves South East ";
  } else {
    new_x -= 1;
    new_y += 1;
    Action = "PC moves South West ";
  }
  char c = fl->getChar(new_x, new_y);
  if (pre_tile == '.' || pre_tile == '+' || pre_tile == '#') {
       fl->modifyFloor(old_x, old_y, pre_tile);
  } else { 
       if (fl->getTreasure(old_x,old_y)->isAvaliable()) { //  pick up successfully
           fl->modifyFloor(old_x,old_y,'.');
       } else {
           fl->modifyFloor(old_x,old_y,'G');
       }
  }
  if (c == '.' || c == '+' || c == '#') {
    pre_tile = c;
    X = new_x; 
    Y = new_y;
    if (HP + 5 <= Max_HP) {
        HP += 5;
    } else {
        HP = Max_HP;
    }
    fl->modifyFloor(new_x,new_y,'@');
  } else if (c == 'G') {
    Treasure *tr = fl->getTreasure(new_x,new_y);
    pick_gold(tr);
    fl->modifyFloor(new_x,new_y,'@');
    if (HP + 5 <= Max_HP) {
        HP += 5;
    } else {
        HP = Max_HP;
    }
    pre_tile = c;
    X = new_x;
    Y = new_y;
  } else if (c == '\\') {
    fl->goupstair(file);
    return 0;
  } else if (c == 'P') {
    Potion *potion = fl->getPotion(new_x,new_y);
    updateAction("Invalid Direction! ");
    ostringstream ss;
    if (potion->isAvaliable()) {
         ss << " However, PC sees Potion: " << potion->getType();
    } else {
         ss << " However, PC sees un unknown Potion ";
    }
    string l = ss.str();
    updateAction(l);
    fl->modifyFloor(old_x,old_y,'@');
  } else {   
    ostringstream ss;
    ss << "Invalid direction" ;
    string s = ss.str();
    updateAction(s);
    fl->modifyFloor(old_x,old_y,'@');
  }
  return 1;
}
    

void Troll::usePotion(RH *rh) {                              
  if (getHP() + 10 + 5 > getMaxHP() && getMaxHP()) {
    HP = getMaxHP();
  } else {
   HP = getHP() + 10 + 5;
  }
  use_RH = true;
  Action = "PC uses RH";
  potion_move(getX(),getY(), rh->getX(), rh->getY());
}

void Troll::usePotion(BA *ba) {
    if (HP + 5 <= Max_HP) {
        HP += 5;
    } else {
        HP = Max_HP;
    }
  Atk += 5;
  use_BA = true;
  Action =  "PC use BA";
  potion_move(getX(), getY(), ba->getX(), ba->getY());
}

void Troll::usePotion(BD *bd) {
    if (HP + 5 <= Max_HP) {
        HP += 5;
    } else {
        HP = Max_HP;
    }
    use_BD = true;
    Def += 5;
    Action = "PC uses BD";
    potion_move(getX(), getY(), bd->getX(), bd->getY());
}

void Troll::usePotion(PH *ph) {
    if (getHP() >= 5) {
    HP -= 5;
  } else {
    HP = 0;
  }
  use_PH = true;
  Action = "PC uses PH";
  potion_move(getX(), getY(), ph->getX(), ph->getY()); 
}

void Troll::usePotion(WA *wa) {
    if (HP + 5 <= Max_HP) {
        HP += 5;
    } else {
        HP = Max_HP;
    }
    if (getAtk() >= 5) {
     Atk -= 5;
    } else {
     Atk = 0;
    }
   use_WA = true;
   Action = "PC uses WA";
   potion_move(getX(), getY(),wa->getX(),wa->getY());
}

void Troll::usePotion(WD *wd) {
    if (HP + 5 <= Max_HP) {
        HP += 5;
    } else {
        HP = Max_HP;
    }
    if (getDef() >= 5) {
     Def -= 5;
    } else {
    Def = 0;
    }
    use_WD = true;
    Action = "PC uses WD";
    potion_move(getX(), getY(), wd->getX(), wd->getY());
} 
 
