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
#include <QOpenGLWidget>



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
  vector <vector <GLfloat>> coordTex;
  int revoluciones = 0;
  int layers = 0;
  GLenum shadeKind = GL_SMOOTH;

  float radiusLight	  = 5;
  float stepCircle	  = 0;

  static inline int optionMaterial = 0;


  void draw_line();
  void draw_fill();
  void draw_chess();
  void calculateNormals();
  void turnFlatShading(bool first, bool second);
  void turnSmoothShading(bool first, bool second);

  GLfloat mat_ambient[3][4]  = {{0.24725, 0.1995, 0.0745, 1.0},{0.0215, 0.1745, 0.0215, 1.0},{0.1, 0.18725, 0.1745, 1.0}};
  GLfloat mat_diffuse[3][4]  = {{0.75164, 0.60648, 0.22648, 1.0},{0.07568, 0.61424, 0.07568, 1.0},{0.396, 0.74151, 0.69102, 1.0}};
  GLfloat mat_specular[3][4] = {{0.628281, 0.555802, 0.366065},{0.633, 0.727811, 0.633, 1.0},{0.297254, 0.30829, 0.306678, 1.0}};
  GLfloat shine[3][1]        = { {0.4 * 128},{0.6 * 128.0},{0.1 * 128} };

  GLfloat posicion_luz_0[4]  = { 0.0, 5.0, 0.0, 0.0 };							// DIRECCIONAL - inf therefore difussion and specular doesnt use position
  GLfloat posicion_luz_1[4]  = { radiusLight, -4, radiusLight, 0.0 };	// POSICIONAL
  GLfloat luz_ambient_1[4]   = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat luz_difusa_1[4]	 = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat luz_especular_1[4] = { 1.0, 1.0, 1.0, 0.0 };

  void nextStep(int step);
  void prevStep(int step);

  void draw_texture();

  vector<_vertex3ui> getTriangles();
  void setImage(QImage image);
  QImage Image;
};

#endif // OBJECT3D_H
