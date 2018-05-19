#include "player.h"
#include <string>
#include <math.h>
#include <cstdlib>
#include "enemy.h"
#include "treasure.h"
#include "potion.h"
#include "floor.h"
#include "rh.h"
#include "ba.h"
#include "bd.h"
#include "ph.h"
#include "wa.h"
#include "wd.h"
using namespace std;

Player::Player(double atk,double def, double hp,string type, int x, int y, int bc, Floor *fl, int gold, int curfl, char pre_tile,double maxhp): Character(atk, def, hp,type, x, y,fl), reachtop{false},atk_mer{false},Action{""}, use_RH{false},use_BA{false}, use_BD{false},use_PH{false},use_WA{false},use_WD{false},born_chamber{bc},Gold{gold}, cur_floor{curfl}, pre_tile{pre_tile}, Max_HP{maxhp} {}


Player::~Player() {}

int Player::getFloor() {
  return cur_floor;
}

bool Player::getreach_top() {
  return reachtop;
}

void Player::reach_top() {
  reachtop = true;
}

int Player::getGold() {
  return Gold;
}

bool Player::getRH() {
  return use_RH;
}

bool Player::getBA() {
  return use_BA;
}

bool Player::getBD() {
  return use_BD;
}

bool Player::getPH() {
  return use_PH;
}

bool Player::getWA() {
   return use_WA;
}

bool Player::getWD() {
  return use_WD;
}


int Player::getborn_chamber() {
  return born_chamber;
}

double Player::getMaxHP() {
  return Max_HP;
}

bool Player::getAtk_Mer() {
  return atk_mer;
}

void Player::Atk_Mer() {
  atk_mer = true;
}

string Player::getAction() {
  return Action;
}

void Player::updateAction(string s) {
  Action = Action + "   " + s;
}

void Player::resetAction() {
  Action = "";
}
   
void Player::attack(Enemy *e) {
 // cout <<"PC Attack Enemy!"<< endl;
  if (e->getType() == "halfling") {
    int i;
    i = rand() % 2;
    if ( i == 0) {
      e->getAttack(this);
    } else {
      ostringstream ss;
      ss << "Oops~ PC Attack Miss!";
      string l = ss.str();
      updateAction(l);
      return;
    }
  }else {
    e->getAttack(this);
  }
  string s = e->getType();
  if (e->isDead() && s != "dragon" && s != "human" && s != "merchant") {
     int g = rand() % 2 + 1;
     Gold += g;
  }
  double damage = ceil((100/(100 + e->getDef())) * getAtk());
  ostringstream ss;
  ss << "PC deals " << damage << " damage to " << e->getType() << " " << e->getType() << " HP: " << e->getHP();
  string ac = ss.str();
  updateAction(ac);
  if (e->isDead()) {
     updateAction( e->getType() + " was killed");
  } 
}

void Player::getAttack(Enemy *e) {
   double damage = ceil((100/(100 + this->getDef())) * e->getAtk());
   if (HP <= damage) {
      HP = 0;
   } else {
   //   cout << "Caution! Enemy deals " << damage << "to PC!" << endl;
      HP -= damage;
   }
}

void Player::pick_gold(Treasure *tr) {
  ostringstream ss;
  if (tr->isAvaliable()) {
    Gold += tr->getValue();
    ss << "PC picks up " << tr->getValue() << " Gold!  ";
  } else {
    ss <<"Oops~ Treasure Not Avaliable  ";
  }
  string s = ss.str();
  updateAction(s);
}

int Player::move(string dir, string file){
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
    fl->modifyFloor(new_x,new_y,'@');
  } else if (c == 'G') {
    Treasure *tr = fl->getTreasure(new_x,new_y);
    pick_gold(tr);
    fl->modifyFloor(new_x,new_y,'@');
    pre_tile = c;
    X = new_x;
    Y = new_y;
  } else if (c == '\\') {
    fl->goupstair(file);
    return 0;
  } else if ( c == 'P') {
    Potion *po = fl->getPotion(new_x,new_y);
    updateAction(" Invalid Direction");
    ostringstream ss;
    if (po->isAvaliable()) {
         ss << " However, PC sees Potion: " << po->getType();
    } else {
         ss << " However, PC sees an unknown Potion ";
    }
    string l = ss.str();
    updateAction(l);
    fl->modifyFloor(old_x,old_y,'@');
  } else {
    ostringstream ss;
    ss << " Invalid direction";
    string s = ss.str();
    updateAction(s);
    fl->modifyFloor(old_x,old_y,'@');
  }
  return 1;
}
    
 
void Player::go_up(int num,int x, int y) {       
  pre_tile = '.';
  cur_floor += 1;
  born_chamber = num;
  X = x;
  Y = y;
  Action = "";
  reset_Atk();
  reset_Def(); 
}

void Player::potion_move(int x1, int y1, int x2, int y2) {
     if (pre_tile == '.' || pre_tile == '+' || pre_tile == '#') {
        fl->modifyFloor(x1,y1,pre_tile);
     } else {
        if (fl->getTreasure(x1,y1)->isAvaliable()) { //  pick up successfully
            fl->modifyFloor(x1,y1,'.');
        } else {
           fl->modifyFloor(x1,y1,'G');
        }
     }
     pre_tile = '.';
     X = x2;
     Y = y2;
     fl->modifyFloor(x2,y2,'@');
 }

void Player::usePotion(RH *rh) {                           
  if (getHP() + 10 > getMaxHP() && getMaxHP()) {
    HP = getMaxHP();
  } else {
   HP = getHP() + 10;
  }
  Action = "PC uses RH";
  use_RH = true;
  potion_move(getX(),getY(), rh->getX(), rh->getY());
}

void Player::usePotion(BA *ba) {
  Atk += 5;
  use_BA = true;
  Action = "PC uses BA";
  potion_move(getX(), getY(), ba->getX(), ba->getY());
}

void Player::usePotion(BD *bd) {
  Def += 5;
  use_BD = true;
  Action = "PC uses BD";
  potion_move(getX(), getY(), bd->getX(), bd->getY());
}

void Player::usePotion(PH *ph) {
  if (getHP() >= 10) {
    HP -= 10;
  } else {
    HP = 0;
  }
  use_PH = true;
  Action = "PC uses PH";
  potion_move(getX(), getY(), ph->getX(), ph->getY()); 
}

void Player::usePotion(WA *wa) {
   if (getAtk() >= 5) {
     Atk -= 5;
   } else {
    Atk = 0;
   }
   use_WA = true;
   Action = "PC uses WA";
   potion_move(getX(), getY(),wa->getX(),wa->getY());
}

void Player::usePotion(WD *wd) {
  if (getDef() >= 5) {
    Def -= 5;
  } else {
    Def = 0;
  }
  use_WD = true;
  Action = "PC uses WD";
  potion_move(getX(), getY(), wd->getX(), wd->getY());
} 
 
