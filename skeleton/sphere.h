#ifndef SPHERE_H
#define SPHERE_H
#include "revolutionobject.h"
#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _sphere:public _revolutionObject,public _object3D
{

public:
  _sphere(float Size=2.0, float Layer = 40, float rev = 40);
 void calculateNormals();


};


#endif // SPHERE_H
