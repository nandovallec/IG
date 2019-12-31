#ifndef ARM_H
#define ARM_H
#include "human.h"
#include "hand.h"
#include "revolutionobject.h"

class _arm:public _human, public _revolutionObject
{
private:
    bool left;
    _hand *hand;
public:
  _arm(float Size=2, float Layer = 60, float rev = 40, bool lefty = false);
  void drawGeneric(int option);
};



#endif // ARM_H
