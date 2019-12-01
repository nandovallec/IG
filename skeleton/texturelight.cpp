#include "texturelight.h"
#define PI 3.14159265

_textureLight::_textureLight()
{

}

void _textureLight::nextStep(int step){
    stepCircle += ((2*PI)/step);
    if(stepCircle > 2*PI)
            stepCircle -= 2*PI;

}

void _textureLight::prevStep(int step){
    stepCircle -= ((2*PI)/step);
    if(stepCircle < 0)
            stepCircle += 2*PI;

}


