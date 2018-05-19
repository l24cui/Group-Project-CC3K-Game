#ifndef CHAMBER_H
#define CHAMBER_H
#include <vector>
class Floor;

class Chamber {
  int num;
  int top;
  int bottom;
  int left;
  int right;
  Floor *fl;
  public:
  Chamber(int num, Floor *fl);
  ~Chamber();
  std::vector<int> spawn();
};


#endif
    
