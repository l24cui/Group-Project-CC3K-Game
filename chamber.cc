#include "chamber.h"
#include <vector>
#include <string>
#include <cstdlib>
#include "floor.h"

using namespace std;

Chamber::Chamber(int num, Floor *fl): num{num}, fl{fl} {
  if (num == 0) {
    top = 3;
    bottom = 6;
    left = 3;
    right = 28;
  } else if (num == 1) {
    top = 3;
    bottom = 12;
    left = 39;
    right = 75;
  } else if (num == 2) {
    top = 10;
    bottom = 12;
    left = 38;
    right = 49;
  } else if (num == 3) {
    top = 15;
    bottom = 21;
    left = 4;
    right = 24;
  } else {
    top = 16;
    bottom = 21;
    left = 37;
    right = 75;
  }
}
   
Chamber::~Chamber() {}

vector <int>Chamber::spawn() {
    vector <int> v;
    int width = right - left + 1;
    int height = bottom - top + 1;
    if (num != 1) {
     while (true) {
      int x = rand() % width + left;
      int y = rand() % height + top;
      if (fl->getChar(x,y) == '.') {
         v.push_back(x);
         v.push_back(y);
         return v;
      }
     }
    } else {
      while(true) {
       int x = rand() % width + left;
       int y = rand() % height + top;
       if (!(x > 38 && x < 50 && y > 9 && y < 13)) {
           if (fl->getChar(x,y) == '.') {
               v.push_back(x);
               v.push_back(y);
               return v;
           }
       }
      }
    }
}
         
           
