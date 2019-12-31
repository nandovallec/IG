#include "eye.h"

_eye::_eye()
{
    _semiSphere basicModel = _semiSphere(1, 20, 40);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 255;
    fillColor.y = 255;
    fillColor.z = 255;
    divideColor(fillColor);
}

void _eye::drawGeneric(int option){
    drawEspecified(option);

    glPushMatrix();
        glTranslatef(0,.4,0.2);
        glScaled(.25,.6,.5);
        pupil.drawGeneric(option);
    glPopMatrix();
}
