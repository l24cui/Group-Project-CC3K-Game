#include "halfling.h"
using namespace std;

Halfling::Halfling(int x, int y, Floor *fl):Enemy(15,20,100,"halfling",true,true,x,y,fl) {}

Halfling::~Halfling() {}

