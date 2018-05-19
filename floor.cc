#include "floor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
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
#include "halfling.h"
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

Floor::Floor(string file) {
  ifstream f {file};
  string s;
  file = file;
  for (int i = 0; i < 25; ++i) {
      getline(f,s);
      display.push_back(s);
  }
  for (int j = 0; j < 5; ++j) {
      Chamber *c = new Chamber{j,this};
      chambers.push_back(c);
  }
  if (file == "emptyfloor.txt") {
      createPC();
      createStair();
      createPotion();
      createGold();
      createEnemy();
  } else {
      int pcx;
      int pcy;
      for (int i = 0; i < 25 ; ++i) {
        for ( int j = 0; j < 79; ++j) {
           char obj = display[i][j];
           if (obj == '0') {
             Potion *po = new RH{j,i, false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '1') {
             Potion *po = new BA{j,i, false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '2') {
             Potion *po = new BD{j,i, false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '3') {
             Potion *po = new PH{j,i, false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '4') {
             Potion *po = new WA{j,i,false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '5') {
             Potion *po = new WD{j,i,false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '6') {
             Treasure *t = new Treasure{j,i,"normal",2,true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '7') {
             Treasure *t = new Treasure{j,i, "small", 1, true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '8') {
             Treasure *t = new Treasure{j,i,"merchant", 4, true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '9') {
             Treasure *t = new Treasure{j,i, "dragon hoard",6, false};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == 'D') {
             Enemy *d = new Dragon{j,i,this,nullptr};
             enemies.push_back(d);
           } else if (obj == 'O') {
             Enemy *o = new Orc{j,i,this};
             enemies.push_back(o);
           } else if (obj == 'L') {
             Enemy *l = new Halfling{j,i,this};
             enemies.push_back(l);
           } else if (obj == 'M') {
             Enemy *m = new Merchant{j,i,this,false};
             enemies.push_back(m);
           } else if (obj == 'E') {
             Enemy *e = new Elf{j,i,this};
             enemies.push_back(e);
           } else if (obj == 'W') {
             Enemy *w = new Dwarf{j,i,this};
             enemies.push_back(w);
           } else if (obj == 'H') {
             Enemy *h = new Human{j,i,this};
             enemies.push_back(h);
           } else if (obj == '@') {
             pcx = j;
             pcy = i;
           }
        }
      }
      cout << "Please choose your race!" << endl;
      cout << "s: shade, d: drow, v: vampire, g: goblin, t: troll" << endl;
      string s;
      while (cin >> s) {
      if (s == "s") {
        p = new Shade(pcx,pcy,-1,this);
        break;
      } else if (s == "d") {
        p = new Drow(pcx,pcy,-1,this);
        break;
      } else if (s == "v") {
        p = new Vampire(pcx,pcy,-1,this);
        break;
      } else if (s == "g") {
        p = new Goblin(pcx,pcy,-1,this);
        break;
      } else if (s == "t") {
        p = new Troll(pcx,pcy,-1,this);
        break;
      } else {
        cout << "Invalid race, please try again" << endl;
        cin.clear();
      }
     }
     for (int i = 0; i < enemies.size(); ++i) {
       if (enemies[i]->getType () == "dragon") {
             int m = enemies[i]->getX();
             int n = enemies[i]->getY();
             for (int j = 0; j < treasures.size(); ++ j) {
               if (treasures[j]->getType() == "dragon hoard" && treasures[j]->getX() >= m-1 && treasures[j]->getX() <= m+1 && treasures[j]->getY() >= n-1 && treasures[j]->getY() <= n+1) {
                   Dragon *de = dynamic_cast<Dragon *>(enemies[i]);
                   de->setHoard(treasures[j]);
                   break;
                   }
             }
       }
     }
  }
}



Floor::~Floor() {
    delete p;
    display.clear();
    for (int j = 4; j >= 0; --j) {
      delete chambers[j];
      chambers.pop_back();
    }
    for (int k = enemies.size()-1; k >= 0; --k) {
     delete enemies[k];
     enemies.pop_back();
    }
    for (int q = potions.size()-1; q >= 0; --q) {
     delete potions[q];
     potions.pop_back();
    } 
    for (int w = treasures.size()-1; w >= 0; --w) {
     delete treasures[w];
     treasures.pop_back();
    }
}

string Floor::getFile() {
  return file;
}

void Floor::print() {
  for (int i = 0; i < 25; ++i) {
    cout << display[i] << endl;
  }
  cout << left << "Race: " << p->getType() << "      Gold: " << p->getGold() << "            Floor: " << p->getFloor() << endl;
  cout << "HP: " << p->getHP() << endl;
  cout << "Atk: " << p->getAtk() << endl;
  cout << "Def: " << p->getDef() << endl;
  cout << "Action: " << p->getAction() << endl;
}
 
char Floor::getChar(int x, int y) {
  return display[y][x];
}


void Floor::modifyFloor(int x, int y, char c) {
  display[y][x] = c;  
}
    

void Floor::createPC() {
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

void Floor::createStair() {
  int i = rand() % 5;
  while (i == p->getborn_chamber()) {
    i = rand() % 5;
  }
  vector <int>v1 = chambers[i]->spawn();
  int x = v1[0];
  int y = v1[1];
  modifyFloor(x,y,'\\');
}

void Floor::createPotion() {
  for (int i = 0; i < 10; ++i) {
    int c = rand() % 5;
    int po = rand() % 6;
    vector <int>v1 = chambers[c]->spawn();
    int x = v1[0];
    int y = v1[1];
    Potion *o;
    if (po == 0) {
        o = new RH(x,y,p->getRH());
    } else if (po == 1) {
        o = new BA(x,y, p->getBA());
    } else if (po == 2) {
        o = new BD(x,y, p->getBD());
    } else if (po == 3) {
        o = new PH(x,y, p->getPH());
    } else if (po == 4) {
        o = new WA(x,y,p->getWA());
    } else {
        o = new WD(x,y, p->getWD());
    }
    modifyFloor(x,y,'P');
    potions.push_back(o);
  }
}

void Floor::createGold() {
  for (int i = 0; i < 10; ++i) {
    int c = rand() % 5;
    int g = rand() % 8;
    vector <int>v1 = chambers[c]->spawn();
    int x = v1[0];
    int y = v1[1];
    Treasure *o;
    if (g >= 0 && g <= 4) {// normal gold
      o = new Treasure(x,y,"normal",2,true);              
    } else if (g == 5) { // dragon hoard
      o = new Treasure(x,y,"dragon hoard",6,false);
      while (true) {
          int x1 = rand() % 3 -1;
          int y1 = rand() % 3 - 1;
          if ((x1 != 0 || y1 != 0) && getChar(x+x1,y+y1) == '.') {
             Enemy *o1 = new Dragon(x+x1,y+y1,this,o);
             modifyFloor(x+x1,y+y1,'D');
             enemies.push_back(o1);
             break;
          }
      } 
    } else { // small gold
      o = new Treasure(x,y,"small",1,true);
    }
    modifyFloor(x,y,'G');
    treasures.push_back(o);
  }
}

void Floor::createEnemy() {
  for (int i = 0; i < 20; ++i) {
     int c = rand() % 5;
     int e = rand() % 18;
     vector <int> v1 = chambers[c]->spawn();
     int x = v1[0];
     int y = v1[1]; 
     Enemy *o;
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
     enemies.push_back(o);
  }
}

void Floor::goupstair(string file) {
  if (p->getFloor() <= 4) { 
    display.clear();
    for (int j = 4; j >= 0; --j) {
      delete chambers[j];
      chambers.pop_back();
    }
    for (int k = enemies.size()-1; k >= 0; --k) {
     delete enemies[k];
     enemies.pop_back();
    }
    for (int q = potions.size()-1; q >= 0; --q) {
     delete potions[q];
     potions.pop_back();
    } 
    for (int w = treasures.size()-1; w >= 0; --w) {
     delete treasures[w];
     treasures.pop_back();
    }
    ifstream f {file};
    string s;
    for (int j = 0; j < 5; ++j) {
       Chamber *c = new Chamber(j,this);
       chambers.push_back(c);
    }
    if (file == "emptyfloor.txt") {
        for (int i = 0; i < 25; ++i) {
           getline(f,s);
           display.push_back(s);
        }
        int cha = rand() % 5;
        vector <int>v1 = chambers[cha]->spawn();
        int x = v1[0];
        int y = v1[1];
        p->go_up(cha,x,y);
     //   cout <<" p->goup run" << endl;
        putPlayer();
       // cout << "insert p run " << endl;
        createStair();
       // cout << "create st" << endl;
        createPotion();
       // cout << " create po" << endl;
        createGold();
       // cout << "crt gold" << endl;
        createEnemy();
       // cout << "!!!!!!"<< endl;
   } else {
      int o = p->getFloor();
      f.seekg(o * 25 * 80);
      for (int i = 0; i < 25; ++i) {
           getline(f,s);
           display.push_back(s);
      }
      int pcx;
      int pcy;
      for (int i = 0; i < 25 ; ++i) {
        for ( int j = 0; j < 79; ++j) {
           char obj = display[i][j];
           if (obj == '0') {
             Potion *po = new RH{j,i, p->getRH()};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '1') {
             Potion *po = new BA{j,i,p->getBA()};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '2') {
             Potion *po = new BD{j,i, p->getBD()};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '3') {
             Potion *po = new PH{j,i, p->getPH()};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '4') {
             Potion *po = new WA{j,i,p->getWA()};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '5') {
             Potion *po = new WD{j,i, p->getWD()};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '6') {
             Treasure *t = new Treasure{j,i,"normal",2,true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '7') {
             Treasure *t = new Treasure{j,i, "small", 1, true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '8') {
             Treasure *t = new Treasure{j,i,"merchant", 4, true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '9') {
             Treasure *t = new Treasure{j,i, "dragon hoard",6, false};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == 'D') {
             Enemy *d = new Dragon{j,i,this,nullptr};
             enemies.push_back(d);
           } else if (obj == 'O') {
             Enemy *o = new Orc{j,i,this};
             enemies.push_back(o);
           } else if (obj == 'L') {
             Enemy *l = new Halfling{j,i,this};
             enemies.push_back(l);
           } else if (obj == 'M') {
             Enemy *m;
             if (p->getAtk_Mer()) {
               m = new Merchant{j,i,this,true};
             } else {
               m = new Merchant{j,i,this,false};
             }
             enemies.push_back(m);
           } else if (obj == 'E') {
             Enemy *e = new Elf{j,i,this};
             enemies.push_back(e);
           } else if (obj == 'W') {
             Enemy *w = new Dwarf{j,i,this};
             enemies.push_back(w);
           } else if (obj == 'H') {
             Enemy *h = new Human{j,i,this};
             enemies.push_back(h);
           } else if (obj == '@') {
             pcx = j;
             pcy = i;
           }
        }
      }
     p->go_up(-1,pcx,pcy);
     for (int i = 0; i < enemies.size(); ++i) {
       if (enemies[i]->getType () == "dragon") {
             int m = enemies[i]->getX();
             int n = enemies[i]->getY();
             for (int j = 0; j < treasures.size(); ++ j) {
               if (treasures[j]->getType() == "dragon hoard" && treasures[j]->getX() >= m-1 && treasures[j]->getX() <= m+1 && treasures[j]->getY() >= n-1 && treasures[j]->getY() <= n+1) {
                   Dragon *dr = dynamic_cast<Dragon *>(enemies[i]);
                   dr->setHoard(treasures[j]);
                   break;
                   }
             }
       }
     }
    }
  }else {
   p->reach_top();
  }
}
  

void Floor::putPlayer() {
   modifyFloor(p->getX(), p->getY(), '@');
}
  

void Floor::restart(string file) {
    delete p;
    display.clear();
    for (int j = 4; j >= 0; --j) {
      delete chambers[j];
      chambers.pop_back();
    }
    for (int k = enemies.size()-1; k >= 0; --k) {
     delete enemies[k];
     enemies.pop_back();
    }
    for (int q = potions.size()-1; q >= 0; --q) {
     delete potions[q];
     potions.pop_back();
    } 
    for (int w = treasures.size()-1; w >= 0; --w) {
     delete treasures[w];
     treasures.pop_back();
    }
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
    if (file == "emptyfloor.txt") {
      createPC();
      createStair();
      createPotion();
      createGold();
      createEnemy();
      print();
    } else {
      int pcx;
      int pcy;
      for (int i = 0; i < 25 ; ++i) {
        for ( int j = 0; j < 79; ++j) {
           char obj = display[i][j];
           if (obj == '0') {
             Potion *po = new RH{j,i,false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '1') {
             Potion *po = new BA{j,i, false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '2') {
             Potion *po = new BD{j,i, false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '3') {
             Potion *po = new PH{j,i, false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '4') {
             Potion *po = new WA{j,i,false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '5') {
             Potion *po = new WD{j,i,false};
             potions.push_back(po);
             display[i][j] = 'P';
           } else if (obj == '6') {
             Treasure *t = new Treasure{j,i,"normal",2,true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '7') {
             Treasure *t = new Treasure{j,i, "small", 1, true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '8') {
             Treasure *t = new Treasure{j,i,"merchant", 4, true};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == '9') {
             Treasure *t = new Treasure{j,i, "dragon hoard",6, false};
             treasures.push_back(t);
             display[i][j] = 'G';
           } else if (obj == 'D') {
             Enemy *d = new Dragon{j,i,this,nullptr};
             enemies.push_back(d);
           } else if (obj == 'O') {
             Enemy *o = new Orc{j,i,this};
             enemies.push_back(o);
           } else if (obj == 'L') {
             Enemy *l = new Halfling{j,i,this};
             enemies.push_back(l);
           } else if (obj == 'M') {
             Enemy *m = new Merchant{j,i,this,false};
             enemies.push_back(m);
           } else if (obj == 'E') {
             Enemy *e = new Elf{j,i,this};
             enemies.push_back(e);
           } else if (obj == 'W') {
             Enemy *w = new Dwarf{j,i,this};
             enemies.push_back(w);
           } else if (obj == 'H') {
             Enemy *h = new Human{j,i,this};
             enemies.push_back(h);
           } else if (obj == '@') {
             pcx = j;
             pcy = i;
           }
        }
      }
      cout << "Please choose your race!" << endl;
      cout << "s: shade, d: drow, v: vampire, g: goblin, t: troll" << endl;
      char s;
      while (cin >> s) {
      if (s == 's') {
        p = new Shade(pcx,pcy,-1,this);
        break;
      } else if (s == 'd') {
        p = new Drow(pcx,pcy,-1,this);
        break;
      } else if (s == 'v') {
        p = new Vampire(pcx,pcy,-1,this);
        break;
      } else if (s == 'g') {
        p = new Goblin(pcx,pcy,-1,this);
        break;
      } else if (s == 't') {
        p = new Troll(pcx,pcy,-1,this);
        break;
      } else {
        cout << "Invalid race, please try again" << endl;
        cin.clear();
      }
     }
     for (int i = 0; i < enemies.size(); ++i) {
       if (enemies[i]->getType () == "dragon") {
             int m = enemies[i]->getX();
             int n = enemies[i]->getY();
             for (int j = 0; j < treasures.size(); ++ j) {
               if (treasures[j]->getType() == "dragon hoard" && treasures[j]->getX() >= m-1 && treasures[j]->getX() <= m+1 && treasures[j]->getY() >= n-1 && treasures[j]->getY() <= n+1) {
                   Dragon *dr = dynamic_cast<Dragon *>(enemies[i]);
                   dr->setHoard(treasures[j]);
                   break;
                   }
             }
       }
     }
     print();
  }
}


int Floor::PCUpdate_move(string c, string file) {  // move
   return  p->move(c,file);
}

void Floor::PCUpdate(string c, string dir) { // a or u
  vector <int>v;
  int x = p->getX();
  int y = p->getY();
  if (dir == "no") {
    v.push_back(x);
    v.push_back(y-1);
  } else if (dir == "so") {
    v.push_back(x);
    v.push_back(y+1);
  } else if (dir == "ea") {
    v.push_back(x+1);
    v.push_back(y);
  } else if (dir == "we") {
    v.push_back(x-1);
    v.push_back(y);
  } else if (dir == "ne") {
    v.push_back(x+1);
    v.push_back(y-1);
  } else if (dir == "nw") {
    v.push_back(x-1);
    v.push_back(y-1);
  } else if (dir == "se") {
    v.push_back(x+1);
    v.push_back(y+1);
  } else {
    v.push_back(x-1);
    v.push_back(y+1);
  }
  int x1 = v[0];
  int y1 = v[1];
  char xx = getChar(x1,y1);
  if (c == "u") {
       if (xx == 'P') {
          Potion *po;
          for (int i = 0; i < potions.size(); ++i) {
              if(potions[i]->getX() == x1 && potions[i]->getY() == y1) {
                 po = potions[i];
                 break;
              }
          }
          po->apply(p);
          string type = po->getType();
          setKnown(type);
       } else {
          p->resetAction();
          p->updateAction("  No Potion Avaliable  ");
       }
  } else { // c : a
       if (xx == 'H' || xx == 'W' || xx == 'E' || xx == 'O' || xx =='M' || xx == 'D' || xx == 'L') {
          Enemy *ey;
          for (int i = 0; i < enemies.size(); ++i) {
              if(enemies[i]->getX() == x1 && enemies[i]->getY() == y1) {
                 ey = enemies[i];
                 break;
              }
          }
          p->attack(ey);
          if (ey->getType() == "merchant") {
             p->Atk_Mer();
             setHostile();
          }
          if (ey->isDead() && ey->getType() == "dragon") {
              Dragon *dr = dynamic_cast<Dragon *>(ey);
              dr->getHoard()->setAvaliable();
              modifyFloor(x1,y1,'.');
          } else if (ey->isDead() && (ey->getType() == "merchant" || ey->getType() == "human")) {
             Treasure *tr = new Treasure(x1,y1,"merchant/human hoard",4,true);
             modifyFloor(x1,y1,'G');
             treasures.push_back(tr);
          } else if (ey->isDead()) {
             modifyFloor(x1,y1,'.');
          }
       } else {
          p->resetAction();
          p->updateAction("    Cannot find Enemy   ");
       }
  }
} 

void Floor::EnemyUpdate() {
  for (int i = 0; i < enemies.size(); ++i) { 
           int PX = p->getX();
           int PY = p->getY();
           int ex = enemies[i]->getX();
           int ey = enemies[i]->getY();
           if (enemies[i]->getType() != "dragon") {
            if (PX >= ex-1 && PX <= ex+1 && PY >=ey-1 && PY <= ey+1 && enemies[i]->getHP() > 0) {
              enemies[i]->attack(p);
            } else if (enemies[i]->getHP() > 0) {
              enemies[i]->move();
            }
           } else {
              Dragon *dr = dynamic_cast<Dragon *> (enemies[i]);
              int x2 = dr->getHoard()->getX(); 
              int y2 = dr->getHoard()->getY();
              if ((PX >= ex-1 && PX <= ex+1 && PY >=ey-1 && PY <= ey+1 && enemies[i]->getHP() > 0) ||( PX >= x2-1 && PX <= x2+1 && PY >= y2-1 && PY <=y2+1 && enemies[i]->getHP() > 0)) {
                 enemies[i]->attack(p);
             }
            }
  }
  print();
  p->resetAction();
}             
 
void Floor::Score() {
     if (p->getType() == "shade") {
         cout << "Score: " << 1.5 * p->getGold() << endl;
     } else {
         cout << "Score: " << p->getGold() << endl;
     }
}

bool Floor::PCdead() {
     if (p->getHP() == 0) {
       return true;
     }
     return false;
}

bool Floor::Win() {
     return p->getreach_top();
}

void Floor::setHostile() {
  for (int i = 0; i < enemies.size(); ++i) {
     enemies[i]->setHostile();
  }
}

void Floor::setKnown(string type) {
    for (int i = 0; i < potions.size(); ++i) {
      if (potions[i]->getType() == type) {
           potions[i]->setAvaliable();
      }
    }
}

void Floor::changeEnemyStat() {
    for (int i = 0; i < enemies.size(); ++i) {
       enemies[i]->setMovable();
       if (enemies[i]->getType() == "dragon") {
           Dragon *dr = dynamic_cast <Dragon *> (enemies[i]);
           dr->setAtk();
    }
  }
}

Treasure* Floor::getTreasure(int x, int y) {
  for (int i = 0; i < treasures.size(); ++i) {
    if (treasures[i]->getX() == x && treasures[i]->getY() == y) {
       return treasures[i];
    }
  }
}

Potion *Floor::getPotion(int x, int y) {
   for (int i = 0; i < potions.size(); ++i) {
      if (potions[i]->getX() == x && potions[i]->getY() == y) {
          return potions[i];
      }
   }
}
