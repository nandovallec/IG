#ifndef _MATRIXPLY_H
#define _MATRIXPLY_H
#include "PLYobject.h"
#include "object3d.h"

class _matrixPLY
{
public:
    _matrixPLY();
    vector <_PLYobject> matrix;

    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
    void drawEspecified(int option, _PLYobject &ob, bool firstLight, bool secondLight);
    void drawGeneric(int option, bool firstLight = false, bool secondLight = false);
    void turnFlatShading(bool firstLight, bool secondLight);
    void turnSmoothShading(bool firstLight, bool secondLight);

};

#endif // _MATRIXPLY_H
