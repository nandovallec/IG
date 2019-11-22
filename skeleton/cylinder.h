#ifndef CYLINDER_H
#define CYLINDER_H
#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _cylinder:public _object3D
{
public:
  _cylinder(float Size=1.0, float Layer = 20, float rev = 20);
};


#endif // CYLINDER_H
