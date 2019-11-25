/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>
#include "vertex.h"
#include "colors.h"
#include "torso.h"
#include "axis.h"
#include "cube.h"
#include "cone.h"
#include "cylinder.h"
#include "tetrahedron.h"
#include "sphere.h"
#include "PLYobject.h"
#include "human.h"
#include "body.h"



namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE, OBJECT_CONE, OBJECT_CYLINDER, OBJECT_SPHERE, OBJECT_PLY, OBJECT_BODY} _object;
}

class _window;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();

  void activateAnimation();
  void increaseStep(int option);
  void decreaseStep(int option);


protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

public slots:
    void animation()
    {
        body.incrLegsDegree(STEP_LEGS);
        body.incrStickDegree(STEP_STICK);
        body.nextStepThrow();
        update();
    }

private:
  _window *Window;

  _axis Axis;
  _tetrahedron Tetrahedron;
  _cube Cube;
  _cone Cone = _cone(1, 1, 20);
  _cylinder Cylinder = _cylinder(1, 1, 20);
  _sphere Sphere;
  _PLYobject plyObj;
  _body body;

  _gl_widget_ne::_object Object;

  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;

  QTimer* timer;
  int STEP_LEGS = 2;
  int STEP_STICK = 5;
  bool animationON = false;

};

#endif
