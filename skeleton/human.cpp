#include "human.h"

#define PI 3.14159265

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
    _human::stepsTrow = 20;
    _human::next_stickAirRotat = 0;
    _human::next_stickScale = 0;
    _human::next_translat = 0;
    _human::stickAscending = true;
    _human::stepsCircle = 20;

}

void _human::draw_point(){
    drawGeneric(0);
}
void _human::draw_line(){
    drawGeneric(1);
}
void _human::draw_fill2(){
    //cout << "aa"<<endl;
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
            _object3D::draw_fill2();
            break;
        case 3:
            _object3D::draw_chess();
            break;
    }
}

void _human::divideColor(_vertex3f &colors){
    colors.x = colors.x / 255.0;
    colors.y = colors.y / 255.0;
    colors.z = colors.z / 255.0;

}
void _human::decrStickDegree(int step){
    //cout << rotStick<<endl;
    stepsTrow = 180 / step;
    rotStick -= step;
    if(rotStick < 0)
        rotStick += 180;
    //cout << rotStick<<endl<<endl;

    //cout << next_stick_X << "    " << next_stick_Y << "      "<< next_stickAirRotat << endl;


    if(!stickAscending){
        next_stickScale += MAX_SCALE / stepsTrow;
        next_stickAirRotat += MAX_AIR_ROT / stepsTrow;

        if(next_stickScale >= MAX_SCALE || next_stickAirRotat >= MAX_AIR_ROT){
            next_stickScale = MAX_SCALE ;
            next_stickAirRotat = MAX_AIR_ROT ;
            stickAscending = true;
        }

    }else{
        next_stickScale -= MAX_SCALE / stepsTrow;
        next_stickAirRotat -= MAX_AIR_ROT / stepsTrow;

        if(next_stickScale <= 0  || next_stickAirRotat <= 0){
            next_stickScale = 0;
            next_stickAirRotat = 0;
            stickAscending = false;
        }
    }


}

void _human::incrStickDegree(int step){
    //cout << rotStick<<endl;
    stepsTrow = 180 / step;

    rotStick = rotStick +step;

    if(rotStick > 180)
        rotStick = rotStick - 180;
    //cout << rotStick<<endl<<endl;


    if(stickAscending){
        next_stickScale += MAX_SCALE / stepsTrow;
        next_stickAirRotat += MAX_AIR_ROT / stepsTrow;

        if(next_stickScale >= MAX_SCALE || next_stickAirRotat >= MAX_AIR_ROT){
            next_stickScale = MAX_SCALE ;
            next_stickAirRotat = MAX_AIR_ROT ;
            stickAscending = false;
        }

    }else{
        next_stickScale -= MAX_SCALE / stepsTrow;
        next_stickAirRotat -= MAX_AIR_ROT / stepsTrow;

        if(next_stickScale <= 0  || next_stickAirRotat <= 0){
            next_stickScale = 0;
            next_stickAirRotat = 0;
            stickAscending = true;
        }
    }

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

void _human::nextStepThrow(int step){
    next_translat += ((2*PI)/step);
    if(next_translat > 2*PI)
            next_translat -= 2*PI;

}

void _human::prevStepThrow(int step){
    next_translat -= ((2*PI)/step);
    if(next_translat < 0)
            next_translat += 2*PI;

}

void _human::incrStepThrow(){
    if(stepsTrow < 50){
        stepsTrow++;
    }
}
void _human::decrStepThrow(){
    if(stepsTrow >= 2){
        stepsTrow--;
    }
}




