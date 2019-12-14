/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _basic_object3D
{
  public:
  vector<_vertex3ui> Triangles;
  vector<_vertex3f> normalVertices;
  vector<_vertex3f> normalTriangles;
  int revoluciones = 0;
  int layers = 0;
  GLenum shadeKind = GL_SMOOTH;

  float radiusLight	  = 5;
  float stepCircle	  = 0;


  void draw_line();
  void draw_fill();
  void draw_chess();
  void calculateNormals();
  void turnFlatShading(bool first, bool second);
  void turnSmoothShading(bool first, bool second);

  GLfloat mat_ambient[4]  = { 0.23125,  0.23125,  0.23125,  1.0 };
  GLfloat mat_diffuse[4]  = { 0.2775,   0.2775,   0.2775,   1.0 };
  GLfloat mat_specular[4] = { 0.773911, 0.773911, 0.773911, 1.0 };
  GLfloat shine[1]        = { 89.6 };

  GLfloat posicion_luz_0[4]  = { 0.0, 5.0, 0.0, 0.0 };							// DIRECCIONAL - inf therefore difussion and specular doesnt use position
  GLfloat posicion_luz_1[4]  = { radiusLight, -4, radiusLight, 1.0 };	// POSICIONAL
  GLfloat luz_difusa_1[4]	 = { 1.0, 0.0, 1.0, 0.0 };
  GLfloat luz_especular_1[4] = { 1.0, 0.0, 1.0, 0.0 };

  void nextStep(int step);
  void prevStep(int step);

  void drawTexture(string name);

  vector<_vertex3ui> getTriangles();

};

#endif // OBJECT3D_H
