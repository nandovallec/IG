#ifndef TORSO_H
#define TORSO_H
#include "human.h"
#include "arm.h"
#include "leg.h"
#include "head.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _torso:public _human
{
private:
    _arm rightArm;
    _arm leftArm;
    _leg leftLeg;
    _leg rightLeg;
    _head head;

public:
  _torso(float Size=6.0, float Layer = 60, float rev = 40);
  void drawGeneric(int option);
  //void draw_point();

};



#endif // TORSO_H
