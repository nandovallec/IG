#include "mouth.h"

_mouth::_mouth()
{
    _semiSphere basicModel = _semiSphere(1, 20, 40);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 0;
    fillColor.y = 0;
    fillColor.z = 0;
    divideColor(fillColor);
}

void _mouth::drawGeneric(int option){
    drawEspecified(option);
}

