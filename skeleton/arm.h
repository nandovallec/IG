#ifndef ARM_H
#define ARM_H
#include "human.h"
#include "hand.h"

class _arm:public _human
{
private:
    _hand hand;
public:
  _arm(float Size=2, float Layer = 60, float rev = 40);

  void drawGeneric(int option);
};



#endif // ARM_H
