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
    //cout << "Primer :     "; Vertices[0].show_values();
  float prog_height = (Size)/Layers;
  float prog_rad = (Size/2.0)/Layers;
  for(int i = 0; i < Layers; i++){
    Vertices.push_back(_vertex3f(0+prog_rad, (Size/2.0)-prog_height, 0));
    //cout << "MID :     "; Vertices[i+1].show_values();
    prog_height += (Size)/Layers;
    prog_rad += (Size/2.0)/Layers;
  }
  Vertices.push_back(_vertex3f(0,-(Size/2.0),0));
  //cout << "FIN :     "; Vertices[Vertices.size()-1].show_values();
//cerr<<-(Size/2.0)<<endl;
  this->revolucionar(Vertices, revoluciones);
  this->connect(Vertices, Triangles, revoluciones);
}



