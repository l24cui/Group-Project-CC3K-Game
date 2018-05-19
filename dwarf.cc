#include "dwarf.h"
#include <string>
using namespace std;

Dwarf::Dwarf(int x, int y, Floor *fl): Enemy(20,30,100, "dwarf", true, true, x,y,fl) {}

Dwarf::~Dwarf() {}
