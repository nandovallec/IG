#include "arm.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_arm::_arm(float Size, float Layers, float rev, bool lefty)
{
    hand = new _hand(lefty);
    left = lefty;
    revoluciones = rev;
    layers = Layers;

    Vertices.push_back(_vertex3f(0,Size/1.5, 0));
    _vertex3f beginning = _vertex3f(Size/10,Size, 0);
    _vertex3f ending = _vertex3f(Size/4, -Size, 0);


    float num = 1/Layers;
    float prog = 0;
    float prog_height = prog;
    for(int i = 0; i < Layers-Layers/4; i++){
      //if(i >= (Layers/2)){
        //Vertices.push_back(_vertex3f(0+prog*.4, (Size/2.0)-prog_height, 0));
        Vertices.push_back(getPointsBetw(beginning, ending, prog));
          //prog_height += (Size)/((float)Layers/(3./2.));

    //  }
    prog +=num;

   //   prog += (Size)/Layers;
    }
    Vertices.push_back(_vertex3f(0,Vertices[Vertices.size()-1].y,0));
    Vertices[0].y = Vertices[1].y;
  //cerr<<-(Size/2.0)<<endl;
    this->revolucionar(Vertices, revoluciones);
    this->connect(Vertices, Triangles, revoluciones);

    fillColor.x = 226;
    fillColor.y = 14;
    fillColor.z = 29;
    calculateColor(fillColor);
}

void _arm::drawGeneric(int option){
    glPushMatrix();
        glScalef(1.2,1,1.2);
        drawEspecified(option);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1,0);
        //
        //cout << "Roto "<<rotStick<<endl;
        glRotatef(rotStick, 0, 1, 0);

        hand->drawGeneric(option);
    glPopMatrix();
}

