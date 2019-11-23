#include "human.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
_human::_human()
{
    _human::rotStick = 0;
    _human::rotLegs = 0;
    _human::reverseLegs = false;

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
            glColor3fv((GLfloat *) &lineColor);
            _object3D::draw_line();
            break;
        case 2:
            glColor3fv((GLfloat *) &fillColor);
            _object3D::draw_fill();
            break;
        case 3:
            _object3D::draw_chess();
            break;
    }
}

void _human::calculateColor(_vertex3f &colors){
    colors.x = colors.x / 255.0;
    colors.y = colors.y / 255.0;
    colors.z = colors.z / 255.0;

}
void _human::decrStickDegree(int step){
    rotStick -= step;
    if(rotStick < 0)
        rotStick += 180;

}

void _human::incrStickDegree(int step){
    rotStick = rotStick +step;

    if(rotStick > 180)
        rotStick = rotStick - 180;
}

void _human::decrLegsDegree(int step){
    if(!reverseLegs){

        rotLegs -= step;

        if(rotLegs < -MAX_DEGREE_LEGS){
            rotLegs = -MAX_DEGREE_LEGS + step;
            reverseLegs = !reverseLegs;
        }
    }else{
        rotLegs = rotLegs +step;

        if(rotLegs > MAX_DEGREE_LEGS){
            rotLegs = MAX_DEGREE_LEGS - step;
            reverseLegs = !reverseLegs;
        }
    }

}

void _human::incrLegsDegree(int step){
    if(!reverseLegs){

        rotLegs = rotLegs +step;

        if(rotLegs > MAX_DEGREE_LEGS){
            rotLegs = MAX_DEGREE_LEGS - step;
            reverseLegs = !reverseLegs;
        }
    }else{

        rotLegs -= step;

        if(rotLegs < -MAX_DEGREE_LEGS){
            rotLegs = -MAX_DEGREE_LEGS + step;
            reverseLegs = !reverseLegs;
        }
    }

}




