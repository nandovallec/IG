/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glut.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMouseEvent>
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
#include "texturelight.h"
#include "chess_board.h"
#include "matrixply.h"

//#include <QOpenGLFunctions_4_5_Compatibility>




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
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE, OBJECT_CONE, OBJECT_CYLINDER, OBJECT_SPHERE, OBJECT_PLY, OBJECT_BODY, OBJECT_BOARD, OBJECT_MATRIX} _object;
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
  void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


public slots:
    void animation()
    {
        body.incrLegsDegree(STEP_LEGS);
        body.incrStickDegree(STEP_STICK);
        body.nextStepThrow(STEP_CIRCLE);


            switch (Object){
                case _gl_widget_ne::OBJECT_TETRAHEDRON:Tetrahedron.nextStep(100);break;
                case _gl_widget_ne::OBJECT_CUBE:Cube.nextStep(100);break;
                case _gl_widget_ne::OBJECT_SPHERE:Sphere.nextStep(100);break;
                case _gl_widget_ne::OBJECT_CONE:Cone.nextStep(100);break;
                case _gl_widget_ne::OBJECT_CYLINDER:Cylinder.nextStep(100);break;
                case _gl_widget_ne::OBJECT_PLY:plyObj.nextStep(100);break;
                case _gl_widget_ne::OBJECT_BODY:body.nextStep(100);break;
                case _gl_widget_ne::OBJECT_BOARD:chess_board.nextStep(100);break;
                case _gl_widget_ne::OBJECT_MATRIX:matrixObj.nextStep(100);break;
                default:break;
            }


        update();
    }

private:
  _window *Window;

  _axis Axis;
  _tetrahedron Tetrahedron;
  _cube Cube;
  _cone Cone = _cone(1, 1, 12);
  _cylinder Cylinder = _cylinder(1, 1, 20);
 // _sphere Sphere = _sphere(2.0, 120,400);
  _sphere Sphere = _sphere(2.0, 5,12);
  _matrixPLY matrixObj;

  _PLYobject plyObj;
  _body body;
  _textureLight textLight;
  _chess_board chess_board = _chess_board(1.0,5);

  _gl_widget_ne::_object Object;

  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;

  float Observer_angle_x, old_angle_x;
  float Observer_angle_y, old_angle_y;
  float Observer_distance, old_distance;

  QTimer* timer;
  int STEP_LEGS = 2;
  int STEP_STICK = 5;
  int STEP_CIRCLE = 100;
  bool animationON = false;

  bool firstLightOn = false;
  bool secondLightOn = false;
  bool flatShade = false;
  bool textureOn = false;
  int materialOption = 0;

  bool parallelProjection = false;
  bool obliqueProjection = false;

  int x_move = INT_MIN, y_move = INT_MIN;
  int const SENS_CAMARA = 2;
  int const SENS_SPEED = 4;
  bool orthogonal = false;

  void pick(int x, int y);
  float picked_camera_x = 0;
  float picked_camera_y = 0;

  void update_picked_observer(float x, float y);

};

#endif
