#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include "floor.h"
#include <fstream>
#include <vector>
#include "shade.h"
#include "drow.h"
#include "troll.h"
#include "goblin.h"
#include "vampire.h"
#include "human.h"
#include "dwarf.h"
#include "orc.h"
#include "elf.h"
#include "merchant.h"
#include "dragon.h"
#include "item.h"
#include "treasure.h"
#include "potion.h"
#include "rh.h"
#include "ba.h"
#include "bd.h"
#include "ph.h"
#include "wa.h"
#include "wd.h"
#include "chamber.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "object.h"

using namespace std;
 
int main(int argc, char *argv[]) {
  srand(time(0));
  string file = "emptyfloor.txt";
  if (argc == 2) {
     file = argv[1];
  } else if (argc == 3) {
     file = argv[1];
     istringstream ss{argv[2]};
     int seed;
     ss >> seed;
     srand(seed);
  }
  cout << "Welcome to CC3K."<< endl;
  Floor *f = new Floor(file);
  f->print();
  string c;
  while (cin >> c) {
    if (c == "no" || c == "so" || c == "ea" || c == "we" || c == "ne" || c == "nw" || c == "se" || c == "sw") {
       int r = f->PCUpdate_move(c,file);
       if (r) {  // upfloor, enemy dont move
          f->EnemyUpdate();
       } else {
          f->print();
       }
    } else if (c == "r") {
       f->restart(file);
    } else if (c == "q") {
       cout << "You quit" << endl;
       break;
    } else if (c == "f") {
       f->changeEnemyStat();
    } else if (c == "u") {
       string dir;
       cin >> dir;
       while (dir != "no" && dir != "so" && dir != "ea" && dir != "we" && dir != "ne" && dir != "nw" && dir != "se" && dir != "sw") {
       cout << "Invalid Direction" << endl;
       cout << "Please enter again" << endl;
       cin.clear();
       cin >> dir;
       }
       f->PCUpdate(c,dir);
       f->EnemyUpdate();
    } else if ( c == "a") {
       string dir;
       cin >> dir;
       while (dir != "no" && dir != "so" && dir != "ea" && dir != "we" && dir != "ne" && dir != "nw" && dir != "se" && dir != "sw") {
       cout << "Invalid Direction" << endl;
       cout << "Please enter again" << endl;
       cin.clear();
       cin >> dir;
       }
       f->PCUpdate(c,dir);
       f->EnemyUpdate();
    } else {
      cout << "Invalid Command" << endl;
      cout << " Please enter again " << endl;
      cin.clear();
    }
    if (f->Win()) {
     cout << " YOU WIN!" << endl;
     f->Score();
     break;
    }
    if (f->PCdead()) {
      cout << "GAME OVER" << endl;
      f->Score();
     break; 
    }
  }
  delete f;  
}
     
  
      
                 
             
       
              
                  
