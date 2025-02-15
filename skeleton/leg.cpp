#include "leg.h"

_leg::_leg()
{
    _cylinder basicModel = _cylinder(1.0, 16.0, 24.0);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 65;
    fillColor.y = 50;
    fillColor.z = 27;
    divideColor(fillColor);
}

void _leg::drawGeneric(int option){

    drawEspecified(option);

    glPushMatrix();
        glTranslated(5,-0.7,5);
        glScalef(.75,.8,5);

        feet.drawGeneric(option);
    glPopMatrix();

}

