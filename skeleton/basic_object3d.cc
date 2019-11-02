/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _basic_object3D::draw_point()
{
  glBegin(GL_POINTS);
  for (unsigned int i=0;i<Vertices.size();i++){
    glVertex3fv((GLfloat *) &Vertices[i]);
  }
  glEnd();
}

int _basic_object3D::rightVert(int i, int layer, int rev){
    if (i+1 > (layer)*rev)
        return i+1-rev;
    return i+1;
}

int _basic_object3D::downVert(int i, int rev){
    return i+rev;
}

int _basic_object3D::downRight(int i, int layer, int rev){
    return rightVert(i+rev, layer+1, rev);
}


