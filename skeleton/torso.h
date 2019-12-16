#ifndef TORSO_H
#define TORSO_H
#include "human.h"
#include "arm.h"
#include "leg.h"
#include "head.h"
#include "revolutionobject.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _torso:public _human, public _revolutionObject
{
private:
    _arm rightArm = _arm(2,60,40,false);
    _arm leftArm = _arm(2,60,40,true);
    _leg leftLeg;
    _leg rightLeg;

public:
  _torso(float Size=6.0, float Layer = 60, float rev = 40);
  void drawGeneric(int option);
  //void draw_point();

};



#endif // TORSO_H
