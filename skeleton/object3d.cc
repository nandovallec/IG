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
    glPolygonMode(GL_FRONT,GL_FILL);
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
    glPolygonMode(GL_FRONT,GL_FILL);
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

vector<_vertex3ui> _object3D::getTriangles(){
    return Triangles;
}

void _object3D::calculateNormals(){
    _vertex3f first, second;
    for(int i = 0; i < Vertices.size(); i++){
        normalVertices.push_back(_vertex3f(0.0,0.0,0.0));
    }

    for(int i = 0; i < Triangles.size(); i++){
        first = Vertices[Triangles[i].y] - Vertices[Triangles[i].x];
        second = Vertices[Triangles[i].z] - Vertices[Triangles[i].x];

        normalTriangles.push_back(first.cross_product(second));
        //cout << "Product "<<i <<"   "<<(first.cross_product(second)).dot_product(_vertex3f(0.1,0.1,0.1))<<endl;
        normalVertices[Triangles[i].x] = normalVertices[Triangles[i].x] + normalTriangles[i];
        normalVertices[Triangles[i].y] = normalVertices[Triangles[i].y] + normalTriangles[i];
        normalVertices[Triangles[i].z] = normalVertices[Triangles[i].z] + normalTriangles[i];

    }
}


void _object3D::smoothShading(){
    shadeKind = GL_SMOOTH;
}
void _object3D::flatShading(){
    shadeKind = GL_FLAT;
}







