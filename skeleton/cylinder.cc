#include "cylinder.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cylinder::_cylinder(float Size, float Layers, float rev)
{
  layers = Layers;
  revoluciones = rev;


  Vertices.push_back(_vertex3f(0,Size/2.0, 0));

  float prog = 0;
  for(int i = 0; i <= Layers; i++){
    Vertices.push_back(_vertex3f(Size, (Size/2.0)-prog, 0));
    prog += (Size)/Layers;
  }
  Vertices.push_back(_vertex3f(0,-(Size/2.0),0));
//cerr<<-(Size/2.0)<<endl;
  this->revolucionar();
  this->connect();

}

