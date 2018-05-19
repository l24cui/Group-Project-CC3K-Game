#include "floor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
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
#include "halfling"
#include "item.h"
#include "treasure.h"
#include "potion.h"
#include "rh.h"
#include "ba.h"
#include "bd.h"
#include "ph.h"
#include "wa.h"
#include "wd.h"

using namespace std;

floor::floor(string file) {
  ifstream f {file};
  string s;
  for (int i = 0; i < 25; ++i) {
      getline(f,s);
      display.push_back(s);
  }
  for (int j = 0; j < 5; ++j) {
      Chamber *c = new Chamber(j,this);
      chambers.push_back(c);
  }
  for (int k = 0; k < 25; ++k) {
     vector <Object *> v;
     for (int l = 0; l < 78; ++l) {
         v.push_back(nullptr);
     }
     ptrs.push_back(v);
  }
  if (file == "emptyfloor.txt") {
      createPC();
      createStair();
      createPotion();
      createGold();
      createEnemy();
  }
} //else {
     // for (int i = 0; i < 25; ++i) {
       //   for (int j = 0; j < 78; ++j) {
         //    if (display[i][j] == 
  


floor::~floor() {
  for ( int i = 0; i < 25; ++i) {
    for (int j = 0; j < 78; ++j) {
        delete ptrs[i][j];
    }
  }
  for (int i = 0; i < 5; ++i) {
    delete chambers[i];
  }
  delete p;
}

void floor::print() {
  for (int i = 0; i < 25; ++i) {
    cout << display[i];
  }
  cout << left << "Race: " << p->getType() << " Gold: " << p->getGold() << right << "Floor: " << p->getFloor() << endl;
  cout << "HP: " << p->getHP() << endl;
  cout << "Atk: " << p->getAtk() << endl;
  cout << "Def: " << p->getDef() << endl;
  cout << "Action: " << p->getAction() << endl;
}
 
char floor::getChar(int x, int y) {
  return display[y][x];
}

Object *floor::getObject(int x, int y) {
  return ptrs[y][x];
}


void floor::modefyFloor(int x, int y, char c) {
  display[y][x] = c;  
}

void floor::updatePtr(int x, int y) {
    ptrs[y][x] = nullptr;
}

void floor::updatePtr(Object *p) {
   int x = p->getX();
   int y = p->getY();
   ptrs[y][x] = p;
}
     

void floor::createPC() {
   cout << "Please choose your race!" << endl;
   cout << "s: shade, d: drow, v: vampire, g: goblin, t: troll" << endl;
   char s;
   int Cha_num = rand() % 5;
   vector <int>v1 = chambers[Cha_num]->spawn();
   int x = v1[0];
   int y = v1[1];
   while (cin >> s) {
     if (s == 's') {
       p = new Shade(x,y,Cha_num,this);
       break;
     } else if (s == 'd') {
       p = new Drow(x,y,Cha_num,this);
       break;
     } else if (s == 'v') {
       p = new Vampire(x,y,Cha_num,this);
       break;
     } else if (s == 'g') {
       p = new Goblin(x,y,Cha_num,this);
       break;
     } else if (s == 't') {
       p = new Troll(x,y,Cha_num,this);
       break;
     } else {
       cout << "Invalid race, please try again" << endl;
       cin.clear();
     }
   }
   modifyFloor(x,y,'@');
}

void floor::createStair() {
  int i = rand() % 5;
  while (i == p->getborn_chamber()) {
    i = rand() % 5;
  }
  vector <int>v1 = chambers[i]->spawn();
  int x = v1[0];
  int y = v1[1];
  modifyFloor(x,y,'\');
}

void floor::createPotion() {
  for (int i = 0; i < 10; ++i) {
    int c = rand() % 5;
    int po = rand() % 6;
    vector <int>v1 = chambers[c]->spawn();
    int x = v1[0];
    int y = v1[1];
    Object *o;
    if (po == 0) {
        o = new RH(x,y,this,p->get_RH());
    } else if (po == 1) {
        o = new BA(x,y,this, p->getBA());
    } else if (po == 2) {
        o = new BD(x,y,this, p->getBD());
    } else if (po == 3) {
        o = new PH(x,y,this, p->getPH());
    } else if (po == 4) {
        o = new WA(x,y,this,p->getWA());
    } else {
        o = new WD(x,y,this, p->getWD());
    }
    modifyFloor(x,y,'P');
    updatePtr(o);
  }
}

void floor::createGold() {
  for (int i = 0; i < 10; ++i) {
    int c = rand() % 5;
    int g = rand() % 8;
    vector <int>v1 = chambers[c]->spawn();
    int x = v1[0];
    int y = v1[1];
    Object *o;
    if (g >= 0 && g <= 4) {// normal gold
      o = new Treasure(x,y,this,"normal",2,true);              
    } else if (g == 5) { // dragon hoard
      o = new Treasure(x,y,this,"dragon hoard",6,false);
      while (true) {
          int x1 = rand() % 3 -1;
          int y1 = rand() % 3 - 1;
          if ((x1 != 0 || y1 != 0) && getChar(x+x1,y+y1) == '.') {
             Object *o1 = new Dragon(x+x1,y+y1,this,dynamic_cast<Treasure *>(o));
             modifyFloor(x+x1,y+y1,'D');
             updatePtr(o1);
             break;
          }
      } 
    } else { // small gold
      o = new Treasure(x,y,this,"small",1,true);
    }
    modifyFloor(x,y,'G');
    updatePtr(o);
  }
}

void floor::createEnemy() {
  for (int i = 0; i < 20; ++i) {
     int c = rand() % 5;
     int e = rand() % 18;
     vector <int> v1 = chambers[c]->spawn();
     int x = v1[0];
     int y = v1[1]; 
     Object *o;
     if (e >= 0 && e <= 3) { // human
       o = new Human(x,y,this);
       modifyFloor(x,y,'M');
     } else if (e >= 4 && e <= 6) {  // dwarf
       o = new Dwarf(x,y,this);
       modifyFloor(x,y,'W');
     } else if (e >= 7 && e <= 11) { // halfling
       o = new Halfling(x,y,this);
       modifyFloor(x,y,'L');
     } else if (e >= 12 && e <= 13) { // elf
       o = new Elf(x,y,this);
       modifyFloor(x,y,'E');
     } else if (e >= 14 && e <= 15) { // orc
       o = new Orc(x,y,this);
       modifyFloor(x,y,'O');
     } else {
       if (p->getAtk_Mer()) {
         o = new Merchant(x,y,this,true);
       } else {
         o = new Merchant(x,y,this,false);
       }
       modifyFloor(x,y,'M');
     }
     updatePtr(o);
  }
}

void floor::goupstair(string file) {
    display.clear();
    for (int j = 0; j < 5; ++j) {
      delete chambers[j];
    }
    chambers.clear();
    for (int k = 0; k < 25; ++k) {
     for (int l = 0; l < 78; ++l) {
         delete ptrs[k][l];
     }
    }
    ifstream f {file};
    string s;
    for (int i = 0; i < 25; ++i) {
       getline(f,s);
       display.push_back(s);
    }
    for (int j = 0; j < 5; ++j) {
       Chamber *c = new Chamber(j,this);
       chambers.push_back(c);
    }
    for (int k = 0; k < 25; ++k) {
      vector <Object *> v;
      for (int l = 0; l < 78; ++l) {
          v.push_back(nullptr);
      }
      ptrs.push_back(v);
    }
    if (file == "emptyfloor.txt") {
        int cha = rand() % 5;
        vector <int>v1 = chambers[cha]->spawn();
        int x = v1[0];
        int y = v1[1];
        p->go_up
  

void floor::putPlayer() {
   int Cha_num = rand() % 5;
   vector <int>v1 = chambers[Cha_num]->spawn();
   int x = v1[0];
   int y = v1[1];
    
  

void floor::restart(string file) {
    delete p;
    display.clear();
    for (int j = 0; j < 5; ++j) {
      delete chambers[j];
    }
    chambers.clear();
    for (int k = 0; k < 25; ++k) {
     for (int l = 0; l < 78; ++l) {
         delete ptrs[k][l];
     }
    }
    ptrs.clear();
    ifstream f{file};
    string s;
    for (int i = 0; i < 25; ++i) {
       getline(f,s);
       display.push_back(s);
    }
    for (int j = 0; j < 5; ++j) {
      Chamber *c = new Chamber(j,this);
      chambers.push_back(c);
    }
    for (int k = 0; k < 25; ++k) {
      vector <Object *> v;
      for (int l = 0; l < 78; ++l) {
         v.push_back(nullptr);
      }
      ptrs.push_back(v);
    }
}

void Player::goupstair() {
                
