#ifndef ITEM_H
#define ITEM_H
#include "object.h"
#include <string>

class Item : public Object {
  protected:
  bool Avaliable;
  public:
  Item(int x, int y, std::string type, bool a);
  virtual ~Item();
  bool isAvaliable();
  void setAvaliable();
};

#endif  
