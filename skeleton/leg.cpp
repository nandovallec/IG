#include "leg.h"

_leg::_leg()
{
    _cylinder basicModel = _cylinder(1.0, 16.0, 24.0);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 65;
    fillColor.y = 50;
    fillColor.z = 27;
    calculateColor(fillColor);
}

void _leg::drawGeneric(int option){

    drawEspecified(option);

    glPushMatrix();
        glScalef(1.5,.8,3);
        glTranslated(0,-0.9,0);
        feet.drawGeneric(option);
    glPopMatrix();

}
