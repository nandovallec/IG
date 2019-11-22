#include "hand.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#define PI 3.14159265

_hand::_hand()
{

    _sphere basicModel = _sphere(1.0, 40, 40);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 255;
    fillColor.y = 231;
    fillColor.z = 184;
    calculateColor(fillColor);
}

void _hand::drawGeneric(int option){
    drawEspecified(option);


    glPushMatrix();
        glScalef(3.5,4,3.5);

        stick.drawGeneric(option);
    glPopMatrix();
}

