#include "torso.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#define PI 3.14159265

_torso::_torso(float Size, float Layers, float rev)
{
    _human::rotStick=0;

    /*ANTIGUO TORSO
    revoluciones = rev;
    layers = Layers;

    _vertex3f beginning = _vertex3f(Size/3.0,Size/2.0, 0);
    _vertex3f ending = _vertex3f.(Size/1.75, -Size/2.0, 0);
    //Vertices.push_back(beginning);

    float num = 1/Layers;
    float prog = 0;
    float prog_height = prog;
    for(int i = 0; i < Layers; i++){
      //if(i >= (Layers/2)){
        //Vertices.push_back(_vertex3f(0+prog*.4, (Size/2.0)-prog_height, 0));
        Vertices.push_back(getPointsBetw(beginning, ending, prog));
          //prog_height += (Size)/((float)Layers/(3./2.));

      //}
      prog +=num;

   //   prog += (Size)/Layers;
    }
    Vertices.push_back(_vertex3f(0,Vertices[Vertices.size()-1].y,0));
    Vertices[0].y = Vertices[1].y;
  //cerr<<-(Size/2.0)<<endl;
    this->revolucionar();
    this->connect();
    */


    revoluciones = rev;
    layers = Layers;
    //Vertices.resize(Layers+2);


    //Vertices.push_back(_vertex3f(0,Size/2.0, 0));

    float prog = 0;//(Size)/Layers;
    for(int i = 0; i <= Layers - Layers/3 ; i++){
        if(i > Layers/5)
      Vertices.push_back(_vertex3f(Size/2*cos((90-prog)*PI / 180), Size/2*sin((90-prog)*PI / 180), 0));
      prog += (180)/Layers;
    }
      Vertices.insert(Vertices.begin(), _vertex3f(0,Vertices[0].y,0));
      Vertices.push_back((_vertex3f(0,Vertices[Vertices.size()-1].y,0)));

      this->revolucionar();
      this->connect();

      fillColor.x = 226;
      fillColor.y = 14;
      fillColor.z = 29;
      calculateColor(fillColor);

}



void _torso::drawGeneric(int option){
    //brazoDer.drawGeneric(option);
    drawEspecified(option);

    glPushMatrix();
        glTranslated(3.3,0.7,0);
        glRotated(50,0,0,1);

        rightArm.drawGeneric(option);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-3.3,0.7,0);
        glRotatef(-50,0,0,1);

        leftArm.drawGeneric(option);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.3, -1.5, 0);
        glRotatef(rotLegs, 1, 0, 0);
        glScalef(1.2,1,1.2);
        rightLeg.drawGeneric(option);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.3, -1.5, 0);
        glRotatef(-rotLegs, 1, 0, 0);
        glScalef(1.2,1,1.2);
        leftLeg.drawGeneric(option);
    glPopMatrix();



}



