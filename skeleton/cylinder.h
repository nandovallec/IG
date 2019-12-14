#ifndef CYLINDER_H
#define CYLINDER_H
#include "revolutionobject.h"
#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _cylinder:public _object3D,public _revolutionObject
{
public:
  _cylinder(float Size=1.0, float Layer = 20, float rev = 20);
  void draw_texture();
};


#endif // CYLINDER_H
