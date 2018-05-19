#include "orc.h"
#include <string>
using namespace std;

Orc::Orc(int x, int y, Floor *fl): Enemy(30,25,180,"orc",true,true,x,y,fl) {}

Orc::~Orc() {}
