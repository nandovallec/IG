#include "human.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_human::_human()
{


}

void _human::draw_point(){
    drawGeneric(0);
}
void _human::draw_line(){
    drawGeneric(1);
}
void _human::draw_fill(){
    drawGeneric(2);
}
void _human::draw_chess(){
    drawGeneric(3);
}


void _human::drawEspecified(int option){
    //cout << "bbb"<< option<<endl;
    switch(option){
        case 0:
            _basic_object3D::draw_point();
            break;
        case 1:
            _object3D::draw_line();
            break;
        case 2:
            _object3D::draw_fill();
            break;
        case 3:
            _object3D::draw_chess();
            break;
    }
}


