#ifndef CONE_H
#define CONE_H
#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _cone:public _object3D
{
public:
  _cone(float Size=1.0, float Layer = 2, float rev = 6);
};


#endif // CONE_H
