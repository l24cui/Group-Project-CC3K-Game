#ifndef FLOOR_H
#define FLOOR_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
class Enemy;
class Treasure;
class Potion;
class Chamber;
class Player;

class Floor {
  std::vector<std::string> display;
  std::vector<Enemy *> enemies;
  std::vector<Potion *> potions;
  std::vector<Treasure *> treasures;
  std::vector<Chamber *> chambers;
  Player *p;
  std::string file;
  public:
  Floor(std::string file);
  ~Floor();
  std::string getFile();
  void print();
  char getChar(int x, int y);
  void createPC();
  void modifyFloor(int x, int y, char c); // change the display
  void createEnemy();
  void createPotion();
  void createGold();
  void createStair();
  void goupstair(std::string file);
  void restart(std::string file);  
  void EnemyUpdate();
  void Score();
  bool PCdead();
  int PCUpdate_move(std::string c, std::string file);
  void PCUpdate(std::string c, std::string dir);
  void putPlayer();
  bool Win();
  void setHostile(); // set merchant hostile
  void setKnown(std::string type); // set Potion known
  void changeEnemyStat(); // command f. movable or not
  Treasure *getTreasure(int x, int y);
  Potion *getPotion(int x, int y);
};

#endif
