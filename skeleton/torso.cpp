#include "torso.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_torso::_torso(float Size, float Layers, float rev)
{
  revoluciones = rev;
  layers = Layers;


  Vertices.push_back(_vertex3f(0,Size/2.0, 0));

  float prog = (Size)/Layers;
  float prog_height = prog;
  for(int i = 0; i < Layers; i++){
    if(i >= (Layers/3)){
        Vertices.push_back(_vertex3f(0+prog*.4, (Size/2.0)-prog_height, 0));
        prog_height += (Size)/((float)Layers/(3./2.));

    }
    prog += (Size)/Layers;
  }
  Vertices.push_back(_vertex3f(0,Vertices[Vertices.size()-1].y,0));
  Vertices[0].y = Vertices[1].y;
//cerr<<-(Size/2.0)<<endl;
  this->revolucionar();
  this->connect();
}



