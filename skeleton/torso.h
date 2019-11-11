#ifndef TORSO_H
#define TORSO_H
#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _torso:public _object3D
{
public:
  _torso(float Size=1.0, float Layer = 60, float rev = 50);
};



#endif // TORSO_H
