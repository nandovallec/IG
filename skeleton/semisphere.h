#ifndef SEMISPHERE_H
#define SEMISPHERE_H
#include "object3d.h"
#include "revolutionobject.h"

class _semiSphere :public _object3D, public _revolutionObject
{
public:
  _semiSphere(float Size=2.0, float Layer = 40, float rev = 40);

};

#endif // SEMISPHERE_H
