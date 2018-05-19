#include "human.h"
#include <string>
using namespace std;

Human::Human(int x, int y, Floor *fl): Enemy(20,20,140,"human",true,true,x,y,fl) {}

Human::~Human() {}
