#include "feet.h"

_feet::_feet()
{
    _semiSphere basicModel = _semiSphere(1.0, 20, 40);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 0;
    fillColor.y = 0;
    fillColor.z = 0;
    divideColor(fillColor);
}
void _feet::drawGeneric(int option){
    this->drawEspecified(option);
}

