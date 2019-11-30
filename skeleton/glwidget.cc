/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;


bool animation = false;



// Polished silver
GLfloat mat_ambient[]  = { 0.23125,  0.23125,  0.23125,  1.0 };
GLfloat mat_diffuse[]  = { 0.2775,   0.2775,   0.2775,   1.0 };
GLfloat mat_specular[] = { 0.773911, 0.773911, 0.773911, 1.0 };
GLfloat shine[] = { 189.6 };


float posicion_luz_x	  = 2;
float posicion_luz_z	  = 2;
GLfloat posicion_luz_0[]  = { 0.0, 6.0, 5.0, 0.0 };							// DIRECCIONAL - inf
GLfloat posicion_luz_1[]  = { posicion_luz_x, 0, posicion_luz_z, 1.0 };	// POSICIONAL
GLfloat luz_difusa_1[]	  = { 1.0, 0.0, 1.0, 0.0 };
GLfloat luz_especular_1[] = { 1.0, 0.0, 1.0, 0.0 };







/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/


_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);

  timer = new QTimer();
  QObject::connect(timer,SIGNAL(timeout()),this, SLOT(animation()));
  timer->stop();
}


/*****************************************************************************//**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{

  switch(Keyevent->key()){
  case Qt::Key_1:Object=OBJECT_TETRAHEDRON;break;
  case Qt::Key_2:Object=OBJECT_CUBE;break;
  case Qt::Key_3:Object=OBJECT_CONE;break;
  case Qt::Key_4:Object=OBJECT_CYLINDER;break;
  case Qt::Key_5:Object=OBJECT_SPHERE;break;
  case Qt::Key_6:Object=OBJECT_PLY;break;
  case Qt::Key_7:Object=OBJECT_BODY;break;

  case Qt::Key_8:

      cout<<"meh"<<endl;
      Sphere.draw_point();

     /* glColor3f(0.0,0.0,0.0);

        Sphere.calculateNormals();
      glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz_0);
          glLightfv(GL_LIGHT1, GL_POSITION, posicion_luz_1);
          glLightfv(GL_LIGHT1, GL_DIFFUSE,  luz_difusa_1);
          glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular_1);


          glEnable(GL_LIGHTING);
          glEnable(GL_LIGHT0);
          glEnable(GL_LIGHT1);
          glEnable(GL_NORMALIZE);

          glEnableClientState( GL_VERTEX_ARRAY );
          glEnableClientState( GL_NORMAL_ARRAY );

          glVertexPointer( 3, GL_FLOAT, 0, Sphere.Vertices.data() );
           glNormalPointer( GL_FLOAT, 0, Sphere.normalVertices.data() );

           // Para añadir las luces a las texturas, descomentar las siguientes líneas
           // if (imagen != ""){ draw_texturas(imagen); }

           //else{
               glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
               glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
               glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
               glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);

               glDrawElements( GL_TRIANGLES, Sphere.Triangles.size()*3, GL_UNSIGNED_INT, Sphere.Triangles.data() ) ;
           //}

           glDisableClientState( GL_NORMAL_ARRAY );
           glDisableClientState( GL_VERTEX_ARRAY );

           glDisable(GL_NORMALIZE);
           glDisable(GL_LIGHT0);
              glDisable(GL_LIGHT1);
              glDisable(GL_LIGHTING);*/
      break;





  case Qt::Key_P:Draw_point=!Draw_point;break;
  case Qt::Key_L:Draw_line=!Draw_line;break;
  case Qt::Key_F:Draw_fill=!Draw_fill;break;
  case Qt::Key_C:Draw_chess=!Draw_chess;break;

  //New keys
  case Qt::Key_A:activateAnimation();break;

  case Qt::Key_Q:body.incrStickDegree(5); update(); break;
  case Qt::Key_W:body.decrStickDegree(5); update(); break;

  case Qt::Key_S:body.incrLegsDegree(5); update(); break;
  case Qt::Key_D:body.decrLegsDegree(5); update(); break;

  case Qt::Key_Z:body.nextStepThrow(20); update(); break;
  case Qt::Key_X:body.prevStepThrow(20); update(); break;


  case Qt::Key_E:increaseStep(1); update(); break;
  case Qt::Key_R:decreaseStep(1); update(); break;

  case Qt::Key_T:increaseStep(2); update(); break;
  case Qt::Key_Y:decreaseStep(2); update(); break;

  case Qt::Key_U:increaseStep(3); update(); break;
  case Qt::Key_I:decreaseStep(3); update(); break;



  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:Observer_distance*=1.2;break;
  case Qt::Key_PageDown:Observer_distance/=1.2;break;
  }

  update();
}


/*****************************************************************************//**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}



/*****************************************************************************//**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}



/*****************************************************************************//**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{
  Axis.draw_line();

  if (Draw_point){
    glPointSize(5);
    glColor3fv((GLfloat *) &BLACK);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
    case OBJECT_CUBE:Cube.draw_point(); break;
    case OBJECT_CONE:Cone.draw_point(); break;
    case OBJECT_CYLINDER:Cylinder.draw_point(); break;
    case OBJECT_SPHERE:Sphere.draw_point(); break;
    case OBJECT_PLY:plyObj.draw_point();break;
    case OBJECT_BODY:body.draw_point(); break;

    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(3);
    glColor3fv((GLfloat *) &MAGENTA);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
    case OBJECT_CUBE:Cube.draw_line(); break;
    case OBJECT_SPHERE:Sphere.draw_line();break;
    case OBJECT_CYLINDER:Cylinder.draw_line();break;
    case OBJECT_CONE:Cone.draw_line();break;
    case OBJECT_PLY:plyObj.draw_line();break;
    case OBJECT_BODY:body.draw_line();break;

    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &BLUE);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
    case OBJECT_CUBE:Cube.draw_fill();break;

    case OBJECT_SPHERE:
        glColor3f(0.0,0.0,0.0);

                Sphere.calculateNormals();
              glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz_0);
                  glLightfv(GL_LIGHT1, GL_POSITION, posicion_luz_1);
                  glLightfv(GL_LIGHT1, GL_DIFFUSE,  luz_difusa_1);
                  glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular_1);


                  glEnable(GL_LIGHTING);
                  glEnable(GL_LIGHT0);
                  glEnable(GL_LIGHT1);
                  glEnable(GL_NORMALIZE);

                  glEnableClientState( GL_VERTEX_ARRAY );
                  glEnableClientState( GL_NORMAL_ARRAY );

                  glVertexPointer( 3, GL_FLOAT, 0, Sphere.Vertices.data() );
                   glNormalPointer( GL_FLOAT, 0, Sphere.normalVertices.data() );

                   // Para añadir las luces a las texturas, descomentar las siguientes líneas
                   // if (imagen != ""){ draw_texturas(imagen); }

                   //else{
                       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
                       glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
                       glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
                       glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);

                       glDrawElements( GL_TRIANGLES, Sphere.Triangles.size()*3, GL_UNSIGNED_INT, Sphere.Triangles.data() ) ;
                   //}

                   glDisableClientState( GL_NORMAL_ARRAY );
                   glDisableClientState( GL_VERTEX_ARRAY );

                   glDisable(GL_NORMALIZE);
                   glDisable(GL_LIGHT0);
                      glDisable(GL_LIGHT1);
                      glDisable(GL_LIGHTING);






        Sphere.draw_fill();








        break;



    case OBJECT_CONE:Cone.draw_fill();break;
    case OBJECT_CYLINDER:Cylinder.draw_fill();break;
    case OBJECT_PLY:plyObj.draw_fill();break;
    case OBJECT_BODY:body.draw_fill();break;

    default:break;
    }
  }

  if (Draw_chess){
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;
    case OBJECT_CUBE:Cube.draw_chess();break;
    case OBJECT_SPHERE:Sphere.draw_chess();break;
    case OBJECT_CONE:Cone.draw_chess();break;
    case OBJECT_CYLINDER:Cylinder.draw_chess();break;
    case OBJECT_PLY:plyObj.draw_chess();break;
    case OBJECT_BODY:body.draw_chess();break;
    default:break;
    }
  }
}



/*****************************************************************************//**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}


/*****************************************************************************//**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
}


/*****************************************************************************//**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;
}

void _gl_widget::activateAnimation(){
    if (animationON){
        timer->stop();
        animationON = false;
    }else{
        timer->start(20); //time specified in ms
        animationON = true;
    }
}

void _gl_widget::increaseStep(int option){
    switch(option){
        case 1:
            if(STEP_STICK <= 85)
                STEP_STICK+=5;
            body.incrStepThrow();
            break;
        case 2:
            if(STEP_LEGS <= 30)
                STEP_LEGS+=2;
            break;
        case 3:
            if(STEP_CIRCLE <= 200)
                STEP_CIRCLE+=3;
            cout << STEP_CIRCLE<<endl;
            break;
    }
}

void _gl_widget::decreaseStep(int option){
    switch(option){
        case 1:
            if(STEP_STICK >= 2)
                STEP_STICK-=1;
            body.decrStepThrow();
            break;
        case 2:
            if(STEP_LEGS >= 5)
                STEP_LEGS-=2;
            break;
        case 3:
            if(STEP_CIRCLE >= 7)
                STEP_CIRCLE-=3;
            break;
    }
}



