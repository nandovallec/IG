#include "sphere.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#define PI 3.14159265

_sphere::_sphere(float Size, float Layers, float rev)
{

  revoluciones = rev;
  layers = Layers;
  //Vertices.resize(Layers+2);


  //Vertices.push_back(_vertex3f(0,Size/2.0, 0));

  float prog = 0;//(Size)/Layers;
  for(int i = 0; i <= Layers; i++){
    Vertices.push_back(_vertex3f(Size/2*cos((90-prog)*PI / 180), Size/2*sin((90-prog)*PI / 180), 0));
    prog += (180)/Layers;
  }
  this->revolucionar(Vertices, revoluciones);
  this->connect(Vertices, Triangles, revoluciones);
  //cerr<<"s"<<Size<<"   "<< Size*sin((90-prog)*PI / 180)<<endl;
  //Vertices[Layers+1]=_vertex3f(0,-(Size/2.0),0);
//cerr<<-(Size/2.0)<<endl;
  //cerr<<"tam es "<< Vertices.size()<<endl;
  //if(Layers == 2)
    calculateNormals();
}

void _sphere::calculateNormals(){
    cout << "mehhh"<<endl;
    _vertex3f first, second;

    //std::for_each(v.begin(), v.end(), &foo);
    for(int i = 0; i < Vertices.size(); i++){
        normalVertices.push_back(Vertices[i]);
    }
    for(int i = 0; i < Triangles.size(); i++){
        float sum_x = Vertices[Triangles[i].x].x + Vertices[Triangles[i].y].x + Vertices[Triangles[i].z].x;
        float sum_y = Vertices[Triangles[i].x].y + Vertices[Triangles[i].y].y + Vertices[Triangles[i].z].y;
        float sum_z = Vertices[Triangles[i].x].z + Vertices[Triangles[i].y].z + Vertices[Triangles[i].z].z;

        normalTriangles.push_back(_vertex3f(sum_x/3.0, sum_y/3.0, sum_z/3.0));

    }

    //normalTriangles[revoluciones+1].x = 0;
   /* cout << "AAAA"; Vertices[0].show_values();
    for (auto it: normalVertices){
        it.show_values();
    }*/

    // Let x=a y=b z=c, when I insert the shading it gets the rotation wrong so I have to rotate the Vertices
    /*Triangles[12].x = 13;
    Triangles[12].y = 12;
    Triangles[12].z = 1;

    */
    //normalTriangles.push_back(normalTriangles[normalTriangles.size()-1]);
    //cout<< "t"<<Triangles.size()<<"    tn"<<normalTriangles.size();
    //cout<<Triangles.size()<<endl;
    //Triangles.erase(Triangles.begin()+revoluciones);
    //cout<<Triangles.size()<<endl;
}
