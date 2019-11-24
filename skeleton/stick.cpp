#include "stick.h"

_stick::
_stick()
{
    _cylinder basicModel = _cylinder(0.5, 16.0, 24.0);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 125;
    fillColor.y = 89;
    fillColor.z = 59;
    calculateColor(fillColor);
}

void _stick::drawGeneric(int option){
    //cout << "abcdefg"<<endl;
    drawEspecified(option);
}
