#include "cone.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cone::_cone(float Size, float Layers, float rev)
{
  revoluciones = rev;
  layers = Layers;


  Vertices.push_back(_vertex3f(0,Size/2.0, 0));

  float prog = (Size)/Layers;
  for(int i = 0; i < Layers; i++){
    Vertices.push_back(_vertex3f(0+prog, (Size/2.0)-prog, 0));
    prog += (Size)/Layers;
  }
  Vertices.push_back(_vertex3f(0,-(Size/2.0),0));
//cerr<<-(Size/2.0)<<endl;
  this->revolucionar();
  this->connect();
}



