#ifndef TORSO_H
#define TORSO_H
#include "human.h"
#include "arm.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _torso:public _human
{
private:
    _arm brazoDer;
    _arm brazoIzq;

public:
  _torso(float Size=6.0, float Layer = 60, float rev = 40);
  void drawGeneric(int option);
  //void draw_point();

};



#endif // TORSO_H
