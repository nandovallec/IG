#include "body.h"
#define PI 3.14159265

_body::_body()
{

}

void _body::drawGeneric(int option){
    glPushMatrix();
    glTranslatef(sin(next_translat)*MAX_TRANSLAT,0, cos(next_translat)*MAX_TRANSLAT);
    glRotated(90+360.0*(next_translat/(2*PI))-360.0, 0, 1, 0);
    //cout << 360.0 - 360*(next_translat/(2*PI))<<"   endl  " <<next_translat/6.0<<endl;
        glPushMatrix();
            glScalef(1,1,1);

            torso.drawGeneric(option);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,3.3,0);
            head.drawGeneric(option);
        glPopMatrix();

    glPopMatrix();
}
