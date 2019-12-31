#include "pupil.h"

_pupil::_pupil()
{
    _semiSphere basicModel = _semiSphere(.5, 20, 40);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 0;
    fillColor.y = 0;
    fillColor.z = 0;
    divideColor(fillColor);
}

void _pupil::drawGeneric(int option){


    drawEspecified(option);
}


