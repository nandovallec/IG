#include "body.h"

_body::_body()
{

}

void _body::drawGeneric(int option){
    glPushMatrix();
        glScalef(1,1,1);

        torso.drawGeneric(option);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,3.3,0);
        head.drawGeneric(option);
    glPopMatrix();
}
