#ifndef HAND_H
#define HAND_H
#include "human.h"
#include "sphere.h"
#include "stick.h"

class _hand:public _human
{
private:
    _stick sticks;
    bool left;


public:
  _hand(bool lefty);
  void drawGeneric(int option);
};


#endif // HAND_H
