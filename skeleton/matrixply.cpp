#include "matrixply.h"

_matrixPLY::_matrixPLY()
{
    int axis = 0;
    matrix.reserve(16);
    for(int i = 0; i < 16; i++, axis++){
        axis = axis % 3;
        if(axis == 0){
            matrix.push_back(_PLYobject("peon.ply", 12, true, false));
        }else if(axis == 1){
            matrix.push_back(_PLYobject("peonX.ply", 12, false, true));
        }else{
            matrix.push_back(_PLYobject("peonZ.ply", 12, false, false));
        }

    }
}

void _matrixPLY::draw_point(){
    drawGeneric(0);
}
void _matrixPLY::draw_line(){
    drawGeneric(1);
}
void _matrixPLY::draw_fill(){
    if(colorObjects.empty())
        calculateColorsObjects();
    drawGeneric(2);
}
void _matrixPLY::draw_chess(){
    drawGeneric(3);
}

void _matrixPLY::turnFlatShading(bool firstLight, bool secondLight){
    drawGeneric(4, firstLight, secondLight);
}

void _matrixPLY::turnSmoothShading(bool firstLight, bool secondLight){
    drawGeneric(5, firstLight, secondLight);
}

void _matrixPLY::draw_selection(){
    drawGeneric(6);
}

void _matrixPLY::draw_selection_object(){
    drawGeneric(7);
}


void _matrixPLY::drawEspecified(int option, _PLYobject & obj, bool firstLight, bool secondLight, int pos){
    //cout << "bbb"<< obj.nomb<<endl;
    switch(option){
        case 0:
            obj.draw_point();
            break;
        case 1:
            obj.draw_line();
            break;
        case 2:
            obj.draw_fill(pickedObjects[pos]);
            break;
        case 3:
            obj.draw_chess();
            break;
        case 4:
            obj.turnFlatShading(firstLight, secondLight);
            break;
        case 5:
            obj.turnSmoothShading(firstLight, secondLight);
            break;
        case 6:
            obj.draw_selection();
            break;
        case 7:
            glColor3fv((GLfloat *) &colorObjects[pos]);
            obj.draw_fill2();
            break;

    }
}

void _matrixPLY::drawGeneric(int option, bool firstLight, bool secondLight){
    float eje_y = -4.5;
    for(int i = 0; i < 4; i++){
        float eje_x = -4.5;
        for(int j = 0; j < 4; j++){
            glPushMatrix();
                //cout << "Dibujo en " << eje_x << " y "<< eje_y<<endl;
                glTranslatef(eje_x, eje_y, 0);
                //cout << "aa" << i*4 + j<<endl;
                drawEspecified(option, matrix[i*4 + j], firstLight, secondLight, i*4+j);
            glPopMatrix();
            eje_x += 3.0;
        }
        eje_y += 3.0;
    }
}

void _matrixPLY::calculateColorsObjects(){
    for(int i = 0; i < matrix.size(); i++){
        pickedObjects.push_back(false);
        vector<float> color = _object3D::intToRGB(i);
        colorObjects.push_back(_vertex3f(color[0], color[1], color[2]));
    }
}

void _matrixPLY::setPicked(int obj, int triangle){
    pickedObjects[obj] = !pickedObjects[obj];
    matrix[obj].setPicked(triangle);
}

vector<float> _matrixPLY::getPos(int id){
    vector<float> res;
    int row = floor((float)id/4.0);
    int col = id % 4;

    switch(col){
        case 0:
            res.push_back(-4.5);
            break;
        case 1:
            res.push_back(-1.5);
            break;
        case 2:
            res.push_back(1.5);
            break;
        case 3:
            res.push_back(4.5);
            break;
    }
    switch(row){
        case 0:
            res.push_back(-4.5);
            break;
        case 1:
            res.push_back(-1.5);
            break;
        case 2:
            res.push_back(1.5);
            break;
        case 3:
            res.push_back(4.5);
            break;
    }

    return res;
}


