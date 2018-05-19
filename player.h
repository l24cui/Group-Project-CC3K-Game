#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include <string>

class Enemy;
class Treasure;
class RH;
class BA;
class BD;
class PH;
class WA;
class WD;

class Player: public Character {
  protected:
  int Gold;
  bool atk_mer;
  bool use_RH;
  bool use_BA;
  bool use_BD;
  bool use_PH;
  bool use_WA;
  bool use_WD;
  bool reachtop;
  int cur_floor;
  char pre_tile;
  double Max_HP;
  int born_chamber;
  std::string Action;
  public:
  Player(double atk, double def, double hp, std::string type, int x, int y, int bc, Floor *fl, int gold, int curfl, char pre_tile, double maxhp);
  int getFloor();
  virtual ~Player();
  int getGold();
  int getborn_chamber();
  bool getAtk_Mer();
  void Atk_Mer();
  void reach_top();
  bool getreach_top();
  bool getRH();
  bool getBA();
  bool getBD();
  bool getPH();
  bool getWA();
  bool getWD();
  double getMaxHP();
  std::string getAction();
  virtual void attack(Enemy *e);
  virtual void getAttack(Enemy *e);
  virtual int move(std::string dir, std::string file);
  void pick_gold(Treasure *tr);
  void go_up(int num, int x, int y);
  void updateAction(std::string s);
  void resetAction();
  virtual void reset_Atk() = 0;
  virtual void reset_Def() = 0;
  void potion_move(int x1 , int y1, int x2, int y2);// update the display of floor when using potion
  virtual void usePotion(RH *rh);
  virtual void usePotion(BA *ba);
  virtual void usePotion(BD *bd);
  virtual void usePotion(PH *ph);
  virtual void usePotion(WA *wa);
  virtual void usePotion(WD *wd); 
};
#endif 
