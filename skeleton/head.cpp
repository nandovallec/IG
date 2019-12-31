#include "head.h"

_head::_head()
{
    _sphere basicModel = _sphere(4, 20, 40);
    this->Vertices = basicModel.Vertices;
    this->Triangles = basicModel.Triangles;

    fillColor.x = 255;
    fillColor.y = 231;
    fillColor.z = 184;
    divideColor(fillColor);
}

void _head::drawGeneric(int option){
    drawEspecified(option);

    glPushMatrix();
        glTranslatef(.7,.6,1.6);
        glRotatef(15,0,1,0);
        glRotatef(60,1,0,0);
        glScalef(.75,.5,.75);
        rightEye.drawGeneric(option);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-.7,.6,1.6);
        glRotatef(-15,0,1,0);
        glRotatef(60,1,0,0);
        glScalef(.75,.5,.75);
        leftEye.drawGeneric(option);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-.4,1.9);
        glRotatef(180, 0, 0, 1);
        glScalef(1,.5,.2);

        mouth.drawGeneric(option);
    glPopMatrix();


}

