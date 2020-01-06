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

  QString File_name("image.jpg");
  QImage Image;
  QImageReader Reader(File_name);
  Reader.setAutoTransform(true);
  Image = Reader.read();
  if (Image.isNull()) {
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                             tr("Cannot load %1.").arg(QDir::toNativeSeparators(File_name)));
    exit(-1);
  }
  Image=Image.mirrored();
  Image=Image.convertToFormat(QImage::Format_RGB888);
  chess_board.setImage(Image);
  Sphere.setImage(Image);
  Cylinder.setImage(Image);

  //cout <<std::dec <<"R" << Cylinder.intToRGB(5)[2]<<endl;
  cout << "FIN" << _object3D::RGBtoint(_object3D::intToRGB(1122867)) << endl;
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
  case Qt::Key_8:Object=OBJECT_BOARD; break;
  case Qt::Key_9:Object=OBJECT_MATRIX; break;


  case Qt::Key_P:Draw_point=!Draw_point;break;
  case Qt::Key_L:Draw_line=!Draw_line;break;
  case Qt::Key_F:Draw_fill=!Draw_fill;break;


  //New keys
  case Qt::Key_A:activateAnimation();break;

  case Qt::Key_Q:body.incrStickDegree(STEP_STICK); update(); break;
  case Qt::Key_W:body.decrStickDegree(STEP_STICK); update(); break;

  case Qt::Key_S:body.incrLegsDegree(STEP_LEGS); update(); break;
  case Qt::Key_D:body.decrLegsDegree(STEP_LEGS); update(); break;

  case Qt::Key_Z:body.nextStepThrow(STEP_CIRCLE); update(); break;
  case Qt::Key_X:body.prevStepThrow(STEP_CIRCLE); update(); break;


  case Qt::Key_E:increaseStep(1); update(); break;
  case Qt::Key_R:decreaseStep(1); update(); break;

  case Qt::Key_T:increaseStep(2); update(); break;
  case Qt::Key_Y:decreaseStep(2); update(); break;

  case Qt::Key_U:increaseStep(3); update(); break;
  case Qt::Key_I:decreaseStep(3); update(); break;


  case Qt::Key_J: firstLightOn = !firstLightOn; break;
  case Qt::Key_K: secondLightOn = !secondLightOn; break;

  case Qt::Key_M: materialOption++; materialOption = materialOption % 3; _object3D::optionMaterial = materialOption; break;

  case Qt::Key_F1:
      firstLightOn = false;
      secondLightOn = false;
      textureOn = false;
      Draw_chess = false;
      Draw_fill = true;
        break;
  case Qt::Key_F2:
      Draw_fill = false;
      Draw_chess=!Draw_chess;
      break;
  case Qt::Key_F3:
      flatShade = true;
      Draw_fill = true;
      break;
  case Qt::Key_F4:
      flatShade = false;
      Draw_fill = true;
      break;

  case Qt::Key_F5:
      Draw_fill = true;
      textureOn = !textureOn;
      break;
  case Qt::Key_F6:
      Draw_fill = true;
      flatShade = true;
      textureOn = true;
      break;

  case Qt::Key_F7:
      Draw_fill = true;
      flatShade = false;
      textureOn = true;
      break;


  case Qt::Key_C:

      /*if(!parallelProjection && !obliqueProjection){
          old_angle_x = Observer_angle_x;
          old_angle_y = Observer_angle_y;
          old_distance = Observer_distance;
      }

      if(!obliqueProjection){
          Observer_angle_x = 90;
          Observer_angle_y = 0;
          Observer_distance = 5;
      }else{
          Observer_angle_x = old_angle_x;
          Observer_angle_y = old_angle_y;
          Observer_distance = old_distance;
      }

      obliqueProjection = !obliqueProjection;
      parallelProjection = false;*/
      orthogonal = false;


      break;
  case Qt::Key_V:
      /*if(!parallelProjection && !obliqueProjection){
          old_angle_x = Observer_angle_x;
          old_angle_y = Observer_angle_y;
          old_distance = Observer_distance;
      }

      if(!parallelProjection){
          Observer_angle_x = 0;
          Observer_angle_y = 0;
          Observer_distance = 5;
      }else{
          Observer_angle_x = old_angle_x;
          Observer_angle_y = old_angle_y;
          Observer_distance = old_distance;
      }
      obliqueProjection = false;
      parallelProjection = !parallelProjection;
*/
      orthogonal = true;


      break;


  }
  if (!obliqueProjection && !parallelProjection){
      switch(Keyevent->key()){
          case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
          case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
          case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
          case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
          case Qt::Key_PageUp:Observer_distance*=1.2;break;
          case Qt::Key_PageDown:Observer_distance/=1.2;break;
      }
  }
  update();
}

void _gl_widget::wheelEvent(QWheelEvent *event){
    if(event->delta() < 0)
        Observer_distance*=1.2;
    else
        Observer_distance/=1.2;
    cout << "Zoom es: "<< Observer_distance << endl;
    update();
}

void _gl_widget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() == Qt::RightButton){
        if(x_move == INT_MIN && y_move == INT_MIN){
            x_move = event -> x();
            y_move = event -> y();
        }
        //cout << x_move << " event" << event->x()<<endl;
        if(x_move - event->x() > SENS_CAMARA){
            Observer_angle_y -= ANGLE_STEP*SENS_SPEED;
            x_move = event -> x();
            update();

        }else if(x_move - event->x() < -SENS_CAMARA){
            Observer_angle_y += ANGLE_STEP*SENS_SPEED;
            x_move = event -> x();
            update();

        }

        if(y_move - event->y() > SENS_CAMARA){
            Observer_angle_x -= ANGLE_STEP*SENS_SPEED;
            y_move = event -> y();
            update();

        }else if(y_move - event->y() < -SENS_CAMARA){
            Observer_angle_x += ANGLE_STEP*SENS_SPEED;
            y_move = event -> y();
            update();
        }

    }
}

void _gl_widget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        x_move = INT_MIN;
        y_move = INT_MIN;
        //cout << "New es "<< event->windowPos().x() -13 << "  .  " << 800.0 - event->windowPos().y() - 14 <<endl; // y esta empieza arriba hasta abajo
        if(Draw_fill == true && firstLightOn == false && secondLightOn == false && textureOn == false)
            pick(event->x(), this->Window->getHeight()-event->y());
        //cout << "Meh "<< this->Window->GL_widget->height()<<endl;
//        float pixel[4];

//        glReadPixels(event->windowPos().x(), event->windowPos().y(), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel);
//       glReadPixels(event->x(), event->y(), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel);

//        cout << "The pixels are: "<< pixel[0]<<" .  " << pixel[1]<<" .  " << pixel[2]<<" .  " << pixel[3] <<endl;
        update();
    }
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

    if (orthogonal)
        glOrtho(-2.0, 2.0, -2.0, 2.0, -5, 5);
    else
        glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);



  //glOrtho(X_MIN, X_MAX, Y_MIN, Y_MAX, -1000, 1000);
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
  if(orthogonal){
    float zoom = 1.5 /Observer_distance;
    glScalef(zoom, zoom, zoom);
  }else
    glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
  glTranslatef(-picked_camera_x,-picked_camera_y,0); // Opposite sign than axis, has to be done before rotation or it will rotate with last centre

}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{
  glPushMatrix();
    glTranslatef(picked_camera_x,picked_camera_y,0);     // Opposite sign than observer
    Axis.draw_line();
  glPopMatrix();

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
    case OBJECT_BOARD:chess_board.draw_point();break;
    case OBJECT_MATRIX:matrixObj.draw_point();break;
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
    case OBJECT_BOARD:chess_board.draw_line();break;
    case OBJECT_MATRIX:matrixObj.draw_line();break;
    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &BLUE);
    switch (Object){
    case OBJECT_TETRAHEDRON:
        if(firstLightOn || secondLightOn)
            if(flatShade)
                Tetrahedron.turnFlatShading(firstLightOn, secondLightOn);
            else
                Tetrahedron.turnSmoothShading(firstLightOn, secondLightOn);
        else
            Tetrahedron.draw_fill();
    break;
    case OBJECT_CUBE:if(firstLightOn || secondLightOn)
            if(flatShade)
                Cube.turnFlatShading(firstLightOn, secondLightOn);
            else
                Cube.turnSmoothShading(firstLightOn, secondLightOn);
        else
            Cube.draw_fill();
    break;

    case OBJECT_SPHERE:
        if((firstLightOn || secondLightOn)&& !textureOn)
            if(flatShade)
                Sphere.turnFlatShading(firstLightOn, secondLightOn);
            else
                Sphere.turnSmoothShading(firstLightOn, secondLightOn);
        else{
            if(textureOn){
                if(firstLightOn || secondLightOn)
                    if(flatShade)
                        Sphere.draw_texture_flat_shading(firstLightOn, secondLightOn);
                    else
                        Sphere.draw_texture_gourand_shading(firstLightOn, secondLightOn);
                else
                    Sphere.draw_texture();
            }else
                Sphere.draw_fill();
        }
    break;

    case OBJECT_CONE:
        if(firstLightOn || secondLightOn)
            if(flatShade)
                Cone.turnFlatShading( firstLightOn, secondLightOn);
            else
                Cone.turnSmoothShading(firstLightOn, secondLightOn);
        else
            Cone.draw_fill();
    break;

    case OBJECT_CYLINDER:
        if((firstLightOn || secondLightOn)&& !textureOn)
            if(flatShade)
                Cylinder.turnFlatShading(firstLightOn, secondLightOn);
            else
                Cylinder.turnSmoothShading(firstLightOn, secondLightOn);
        else{
            if(textureOn){
                if(firstLightOn || secondLightOn)
                    if(flatShade)
                        Cylinder.draw_texture_flat_shading(firstLightOn, secondLightOn);
                    else
                        Cylinder.draw_texture_gourand_shading(firstLightOn, secondLightOn);
                else
                    Cylinder.draw_texture();
            }else
                Cylinder.draw_fill();
        }
    break;

    case OBJECT_PLY:
        if(firstLightOn || secondLightOn)
            if(flatShade)
                plyObj.turnFlatShading(firstLightOn, secondLightOn);
            else
                plyObj.turnSmoothShading(firstLightOn, secondLightOn);
        else
            plyObj._object3D::draw_fill();
    break;

    case OBJECT_BODY:
        if(firstLightOn || secondLightOn)
            if(flatShade)
                body.turnFlatShading(firstLightOn, secondLightOn);
            else
                body.turnSmoothShading(firstLightOn, secondLightOn);
        else
            body.draw_fill2();
    break;

    case OBJECT_BOARD:

        if((firstLightOn || secondLightOn)&& !textureOn)
            if(flatShade)
                chess_board.turnFlatShading(firstLightOn, secondLightOn);
            else
                chess_board.turnSmoothShading(firstLightOn, secondLightOn);
        else{
            if(textureOn){
                if(firstLightOn || secondLightOn)
                    if(flatShade)
                        chess_board.draw_texture_flat_shading(firstLightOn, secondLightOn);
                    else
                        chess_board.draw_texture_gourand_shading(firstLightOn, secondLightOn);
                else
                    chess_board.draw_texture();
            }else
                chess_board.draw_fill();
        }
    break;

    case OBJECT_MATRIX:
        if(firstLightOn || secondLightOn)
            if(flatShade)
                matrixObj.turnFlatShading(firstLightOn, secondLightOn);
            else
                matrixObj.turnSmoothShading(firstLightOn, secondLightOn);
        else
            matrixObj.draw_fill();
    break;

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
    case OBJECT_BOARD:chess_board.draw_chess();break;
    case OBJECT_MATRIX:matrixObj.draw_chess(); break;
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
#include <QOpenGLFunctions>

void _gl_widget::pick(int x, int y)
{
  makeCurrent();
  // Frame Buffer Object to do the off-screen rendering
  GLuint FBO;

  glGenFramebuffers(1,&FBO);
  glBindFramebuffer(GL_FRAMEBUFFER,FBO);

  // Texture for drawing
  GLuint Color_texture;
  glGenTextures(1,&Color_texture);
  glBindTexture(GL_TEXTURE_2D,Color_texture);
  // RGBA8
  glTexStorage2D(GL_TEXTURE_2D,1,GL_RGBA8, this->Window->width(),  this->Window->height());
  // this implies that there is not mip mapping
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);  //MipMapping = not loading all texture, kind of fog at the end limitting to only visible on screen
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  // Texure for computing the depth
  GLuint Depth_texture;
  glGenTextures(1,&Depth_texture);
  glBindTexture(GL_TEXTURE_2D,Depth_texture);
  // Float
  glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24, this->Window->width(),this->Window->height());

  // Attatchment of the textures to the FBO
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Color_texture,0);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,Depth_texture,0);

  // OpenGL will draw to these buffers (only one in this case)
  static const GLenum Draw_buffers[]={GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1,Draw_buffers);

  /*************************/

  switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_selection();break;
      case OBJECT_CUBE:Cube.draw_selection();break;
      case OBJECT_SPHERE:Sphere.draw_selection();break;
      case OBJECT_CONE:Cone.draw_selection();break;
      case OBJECT_CYLINDER:Cylinder.draw_selection();break;
      case OBJECT_PLY:plyObj.draw_selection();break;
      case OBJECT_BOARD:chess_board.draw_selection();break;
      case OBJECT_MATRIX:matrixObj.draw_selection_object();break;
      default:break;
  }

  /*************************/

  // get the pixel
  unsigned char pixel[4];
  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT,1);
  glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,pixel);

  //cout << "The pixels are: "<< (float)pixel[0]<<" .  " << (float)pixel[1]<<" .  " << (float)pixel[2]<<" .  " << (float)pixel[3] <<endl;

  /*************************/
    if(pixel[3] != 0){
        vector <float> color = vector <float> {(float)pixel[0],(float)pixel[1],(float)pixel[2],(float)pixel[3]};
        // convertir de RGB a identificador
        int id = _object3D::RGBtoint(color);
        //cout<<"ID es : " << id<<endl;
        // actualizar el identificador de la parte seleccionada en el objeto
        switch (Object){
            case OBJECT_TETRAHEDRON:Tetrahedron.setPicked(id);break;
            case OBJECT_CUBE:Cube.setPicked(id);break;
            case OBJECT_SPHERE:Sphere.setPicked(id);break;
            case OBJECT_CONE:Cone.setPicked(id);break;
            case OBJECT_CYLINDER:Cylinder.setPicked(id);break;
            case OBJECT_PLY:plyObj.setPicked(id);break;
            case OBJECT_BODY:body.setPicked(id);break;
            case OBJECT_BOARD:chess_board.setPicked(id);break;
            default:break;
        }

        if(Object == OBJECT_MATRIX){




            glGenTextures(1,&Depth_texture);
            glBindTexture(GL_TEXTURE_2D,Depth_texture);
            // Float
            glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24, this->Window->width(),this->Window->height());

            // Attatchment of the textures to the FBO
            //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Color_texture,0);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,Depth_texture,0);


            //glDrawBuffers(1,Draw_buffers);


            matrixObj.draw_selection();
            unsigned char pixel2[4];

            //glReadBuffer(GL_FRONT);
            //glPixelStorei(GL_PACK_ALIGNMENT,1);
            glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,pixel2);
            //cout << "The pixels are: "<< (float)pixel2[0]<<" .  " << (float)pixel2[1]<<" .  " << (float)pixel2[2]<<" .  " << (float)pixel2[3] <<endl;

            vector <float> color2 = vector <float> {(float)pixel2[0],(float)pixel2[1],(float)pixel2[2],(float)pixel2[3]};
            int id2 = _object3D::RGBtoint(color2);
            //cout << "El nuevo id es "<< id2 <<endl;
            matrixObj.setPicked(id, id2);
            vector<float> pos = matrixObj.getPos(id);
            update_picked_observer(pos[0], pos[1]);

        }
    }
  /*************************/

  glDeleteTextures(1,&Color_texture);
  glDeleteTextures(1,&Depth_texture);
  glDeleteFramebuffers(1,&FBO);
  // the normal framebuffer takes the control of drawing
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,defaultFramebufferObject());
}


void _gl_widget::update_picked_observer(float x, float y){
    if(x == picked_camera_x && y == picked_camera_y){
        picked_camera_x = 0;
        picked_camera_y = 0;
    }else{
        picked_camera_x = x;
        picked_camera_y = y;
    }
    cout << "New pos is:" << picked_camera_x << " || "<< picked_camera_y<<endl;

}


