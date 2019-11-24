#include "hand.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#define PI 3.14159265

_hand::_hand(bool lefty)
{

    _sphere basicModel = _sphere(1.0, 40, 40);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    left = lefty;

    fillColor.x = 255;
    fillColor.y = 231;
    fillColor.z = 184;
    calculateColor(fillColor);
}

void _hand::drawGeneric(int option){
    drawEspecified(option);

    //cout << "micarro"<<endl;

    glPushMatrix();


        glTranslatef(0, -0.25, 0);

        if(left)
            glTranslatef(-next_stick_X,next_stick_Y,0);
        else
            glTranslatef(next_stick_X,next_stick_Y,0);

        if(left)
            glRotatef(-next_stickAirRotat, 0, 0, 1);
        else
            glRotatef(next_stickAirRotat, 0, 0, 1);


        //cout << "aaaa"<<next_stickAirRotat<<endl;
        glRotatef(rotStick, 0, 1, 0);




        glRotatef(90, 0, 0, 1);

        glScalef(0.25,8,0.25);
        sticks.drawGeneric(option);
    glPopMatrix();
}



