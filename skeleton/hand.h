#ifndef HAND_H
#define HAND_H
#include "human.h"
#include "sphere.h"
#include "stick.h"

class _hand:public _human
{
private:
    _stick stick;
public:
    _hand();

  void drawGeneric(int option);
};


#endif // HAND_H
