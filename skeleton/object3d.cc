/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "object3d.h"
#define PI 3.14159265

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glBegin(GL_TRIANGLES);
  for (unsigned int i=0;i<Triangles.size();i++){
      //cerr<<i<<"  connect "<< Triangles[i]._0<<" "<<Triangles[i]._0<< "  "<<Triangles[i]._0<<"  "<<i<<endl;
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
  }
  glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);

    for (unsigned int i=0;i<Triangles.size();i++){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(0.0,1.0,0.0);
    for (unsigned int i=0;i<Triangles.size();i=i+2){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glColor3f(0.0,.5,0.5);
    for (unsigned int i=1;i<Triangles.size();i=i+2){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();

}


void _object3D::revolucionar(){
    vector<_vertex3f> cop = Vertices;
    Vertices.clear();
    //Vertices.resize((Vertices.size()-2)*(revoluciones));
    //cerr << "nuevo"<<Vertices.size()<<endl;
    float prog = 0;
    //cop[1].show_values();
    //cerr<<"first "<<"    "<< float(cop[1].x)*cos((45)*PI / 180)<<endl;
    //cop[0].show_values();
    Vertices.reserve((cop.size()-2)*revoluciones +2);
    Vertices.push_back(cop[0]);
    for(int i = 1; i < cop.size()-1; i++){
        prog = 360/revoluciones;
        float Size = sqrt(cop[i].x * cop[i].x+cop[i].z+cop[i].z);
        //cerr<<"metoooooo ";cop[i].show_values();cerr<<endl;
        for(int j = 0; j < revoluciones; j++){
            //cerr<<"aa"<<cop[i].x<<"     "<<float(cop[i].x)*cos((360-prog)*PI / 180)<<endl;
            Vertices.push_back(_vertex3f(Size*cos((prog)*PI / 180),cop[i].y,Size*sin((prog)*PI / 180)));
            //Vertices[i*revoluciones+j].show_values();
            //cerr<<i*revoluciones+j<<endl;
            prog += (360)/revoluciones;
        }
    }
    Vertices.push_back(cop[cop.size()-1]);
    cerr<<"maamamamam"<<endl<<endl<<endl;
    //cerr<<Vertices.size()<<endl;
    //Vertices[Vertices.size()-1] = cop[cop.size()-1];

}



void _object3D::connect(){
    cerr<<"aaaaaaaaaaaa"<<endl;
    //int index = 0;
    int count = 0;
    int act_lay = 1;
    //Triangles.resize(layers*2*revoluciones);
    //cerr<<"prop"<<layers*2*revoluciones<<endl;
    cerr<<"mis rev   "<<revoluciones<<endl;

    for(int i = 0; i < revoluciones-1; i++)
        Triangles.push_back(_vertex3ui(0, i+1, i+2));
    Triangles.push_back(_vertex3ui(0, 1, revoluciones));

    for(int i = 1; i < Vertices.size()-(revoluciones)-1; i++){
        if(count == revoluciones){
            count = 0;
            act_lay++;
            //cerr<<"meem"<<Vertices.size()<<endl;
        }
        count++;
        //cerr<<revoluciones<<"dddd"<<act_lay<<endl;
        int r = rightVert(i, act_lay, revoluciones), d = downVert(i, revoluciones), dr = downRight(i, act_lay, revoluciones);
        //cerr << "connect "<< i <<"  "<< r<<"  "<<d<<endl;
        //cerr<< "Conecting:    "; Vertices[i].show_values();cerr<<"      ";Vertices[r].show_values();cerr<<"      ";Vertices[d].show_values();cerr<<"      "<<endl;
        //cerr<<"Conecto : "<<i<<"   "<<r<<"    "<<dr<<"                         y"<<i<<"     "<<d<<"      "<<dr<<endl;
        Triangles.push_back(_vertex3ui(i,r,dr));
        Triangles.push_back(_vertex3ui(i,d, dr));
        //index = index+2;

    }
    int last = Vertices.size()-1;
    Triangles.push_back(_vertex3ui(last-revoluciones,last-1,last));
    for(int i = 0; i < revoluciones-1; i++)
        Triangles.push_back(_vertex3ui(last-i-1, last-i-2, last));
}





