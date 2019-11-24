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
    _human::stepsTrow = 20;
    _human::next_stickAirRotat = 0;
    _human::next_stick_X = 0;
    _human::next_stick_Y = 0;
    _human::stickAscending = true;

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
    cout << rotStick<<endl;

    rotStick -= step;
    if(rotStick < 0)
        rotStick += 180;
    cout << rotStick<<endl<<endl;

}

void _human::incrStickDegree(int step){
    cout << rotStick<<endl;
    rotStick = rotStick +step;

    if(rotStick > 180)
        rotStick = rotStick - 180;
    cout << rotStick<<endl<<endl;

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

void _human::nextStepThrow(){
    //cout << next_stick_X << "    " << next_stick_Y << "      "<< next_stickAirRotat << endl;
    if(stickAscending){
        next_stick_X += MAX_X / stepsTrow;
        next_stick_Y += MAX_Y / stepsTrow;
        next_stickAirRotat += MAX_AIR_ROT / stepsTrow;

        if(next_stick_X >= MAX_X || next_stick_Y >= MAX_Y || next_stickAirRotat >= MAX_AIR_ROT){
            next_stick_X = MAX_X ;
            next_stick_Y = MAX_Y ;
            next_stickAirRotat = MAX_AIR_ROT ;
            stickAscending = false;
        }

    }else{
        next_stick_X -= MAX_X / stepsTrow;
        next_stick_Y -= MAX_Y / stepsTrow;
        next_stickAirRotat -= MAX_AIR_ROT / stepsTrow;

        if(next_stick_X <= 0 || next_stick_Y <= 0 || next_stickAirRotat <= 0){
            next_stick_X = 0;
            next_stick_Y = 0;
            next_stickAirRotat = 0;
            stickAscending = true;
        }
    }


}

void _human::prevStepThrow(){
    //cout << next_stick_X << "    " << next_stick_Y << "      "<< next_stickAirRotat << endl;
    if(!stickAscending){
        next_stick_X += MAX_X / stepsTrow;
        next_stick_Y += MAX_Y / stepsTrow;
        next_stickAirRotat += MAX_AIR_ROT / stepsTrow;

        if(next_stick_X >= MAX_X || next_stick_Y >= MAX_Y || next_stickAirRotat >= MAX_AIR_ROT){
            next_stick_X = MAX_X ;
            next_stick_Y = MAX_Y ;
            next_stickAirRotat = MAX_AIR_ROT ;
            stickAscending = true;
        }

    }else{
        next_stick_X -= MAX_X / stepsTrow;
        next_stick_Y -= MAX_Y / stepsTrow;
        next_stickAirRotat -= MAX_AIR_ROT / stepsTrow;

        if(next_stick_X <= 0 || next_stick_Y <= 0 || next_stickAirRotat <= 0){
            next_stick_X = 0;
            next_stick_Y = 0;
            next_stickAirRotat = 0;
            stickAscending = false;
        }
    }


}




