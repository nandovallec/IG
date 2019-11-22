#include "semisphere.h"
#define PI 3.14159265

_semiSphere::_semiSphere(float Size, float Layers, float rev)
{

    revoluciones = rev;
    layers = Layers;
    //Vertices.resize(Layers+2);


    //Vertices.push_back(_vertex3f(0,Size/2.0, 0));

    float prog = 0;//(Size)/Layers;
    for(int i = 0; i <= Layers; i++){
      Vertices.push_back(_vertex3f(Size/2*cos((90-prog)*PI / 180), Size/2*sin((90-prog)*PI / 180), 0));
      prog += (90)/Layers;
    }
      Vertices.push_back(_vertex3f(0, Vertices[Vertices.size()-1].y, 0));
      this->revolucionar();
      this->connect();
    //cerr<<"s"<<Size<<"   "<< Size*sin((90-prog)*PI / 180)<<endl;
    //Vertices[Layers+1]=_vertex3f(0,-(Size/2.0),0);
  //cerr<<-(Size/2.0)<<endl;
    //cerr<<"tam es "<< Vertices.size()<<endl;
}
