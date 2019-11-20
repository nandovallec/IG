#ifndef HAND_H
#define HAND_H
#include "human.h"

class _hand:public _human
{
private:
public:
    _hand(float Size=1.0, float Layer = 40, float rev = 40);

  void drawGeneric(int option);
};


#endif // HAND_H
