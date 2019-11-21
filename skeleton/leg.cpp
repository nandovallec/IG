#include "leg.h"

_leg::_leg()
{
    _cylinder basicModel = _cylinder(1.0, 16.0, 24.0);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;
}

void _leg::drawGeneric(int option){
    drawEspecified(option);
}
