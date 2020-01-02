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

void _matrixPLY::drawEspecified(int option, _PLYobject & obj, bool firstLight, bool secondLight){
    //cout << "bbb"<< obj.nomb<<endl;
    switch(option){
        case 0:
            obj.draw_point();
            break;
        case 1:
//            glColor3fv((GLfloat *) &lineColor);
            obj.draw_line();
            break;
        case 2:
 //           glColor3fv((GLfloat *) &fillColor);
            obj.draw_fill();
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
    }
}

void _matrixPLY::drawGeneric(int option, bool firstLight, bool secondLight){
    int eje_y = -4.5;
    for(int i = 0; i < 4; i++){
        int eje_x = -4.5;
        for(int j = 0; j < 4; j++){
            glPushMatrix();
                glTranslatef(eje_x, eje_y, 0);
                //cout << "aa" << i*4 + j<<endl;
                drawEspecified(option, matrix[i*4 + j], firstLight, secondLight);
            glPopMatrix();
            eje_x += 3.0;
        }
        eje_y += 3.0;
    }
}
