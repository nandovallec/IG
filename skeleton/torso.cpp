#include "torso.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_torso::_torso(float Size, float Layers, float rev)
{
  /*revoluciones = rev;
    layers = Layers;

    _vertex3f beginning = _vertex3f(Size/3.0,Size/2.0, 0);
    _vertex3f ending = _vertex3f(Size/1.75, -Size/2.0, 0);
    //Vertices.push_back(beginning);

    float num = 1/Layers;
    float prog = 0;
    float prog_height = prog;
    for(int i = 0; i < Layers; i++){
      //if(i >= (Layers/2)){
        //Vertices.push_back(_vertex3f(0+prog*.4, (Size/2.0)-prog_height, 0));
        Vertices.push_back(getPointsBetw(beginning, ending, prog));
          //prog_height += (Size)/((float)Layers/(3./2.));

      //}
      prog +=num;

   //   prog += (Size)/Layers;
    }
    Vertices.push_back(_vertex3f(0,Vertices[Vertices.size()-1].y,0));
    Vertices[0].y = Vertices[1].y;
  //cerr<<-(Size/2.0)<<endl;
    this->revolucionar();
    this->connect();*/


    //ESTO ES BRAZO


    revoluciones = rev;
    layers = Layers;

    _vertex3f beginning = _vertex3f(Size/10,Size/1.5, 0);
    _vertex3f ending = _vertex3f(Size/4, -Size/1.5, 0);
    //Vertices.push_back(beginning);

    float num = 1/Layers;
    float prog = 0;
    float prog_height = prog;
    for(int i = 0; i < Layers; i++){
      //if(i >= (Layers/2)){
        //Vertices.push_back(_vertex3f(0+prog*.4, (Size/2.0)-prog_height, 0));
        Vertices.push_back(getPointsBetw(beginning, ending, prog));
          //prog_height += (Size)/((float)Layers/(3./2.));

    //  }
    prog +=num;

   //   prog += (Size)/Layers;
    }
    Vertices.push_back(_vertex3f(0,Vertices[Vertices.size()-1].y,0));
    Vertices[0].y = Vertices[1].y;
  //cerr<<-(Size/2.0)<<endl;
    this->revolucionar();
    this->connect();


}



