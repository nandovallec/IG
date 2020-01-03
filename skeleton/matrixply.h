#ifndef _MATRIXPLY_H
#define _MATRIXPLY_H
#include "PLYobject.h"
#include "object3d.h"

class _matrixPLY
{
public:
    _matrixPLY();
    vector <_PLYobject> matrix;
    vector <_vertex3f> colorObjects;
    vector<bool> pickedObjects;


    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
    void drawEspecified(int option, _PLYobject &ob, bool firstLight, bool secondLight, int pos);
    void drawGeneric(int option, bool firstLight = false, bool secondLight = false);
    void turnFlatShading(bool firstLight, bool secondLight);
    void turnSmoothShading(bool firstLight, bool secondLight);
    void draw_selection();
    void draw_selection_object();
    void calculateColorsObjects();
    void setPicked(int object, int triangle);
};

#endif // _MATRIXPLY_H
