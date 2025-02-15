#include "hand.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#define PI 3.14159265

_hand::_hand(bool lefty)
{

    _sphere basicModel = _sphere(1.0, 40, 40);
    this->Vertices = basicModel.getVertices();
    this->Triangles = basicModel.getTriangles();

    left = lefty;

    fillColor.x = 255;
    fillColor.y = 231;
    fillColor.z = 184;
    divideColor(fillColor);
}

void _hand::drawGeneric(int option){
    drawEspecified(option);

    //cout << "micarro"<<endl;

    glPushMatrix();


        glTranslatef(0, -0.25, 0);

/*        if(left)
            glTranslatef(-next_stick_X,next_stick_Y,0);
        else
            glTranslatef(next_stick_X,next_stick_Y,0);
*/

        //cout << next_stickAirRotat <<endl;
        if(left)
            glRotatef(-next_stickAirRotat, 0.1, 0, 0.9);
        else
            glRotatef(next_stickAirRotat, 0.1, 0, 0.9);


        //cout << "aaaa"<<next_stickAirRotat<<endl;
        //glRotatef(rotStick, 0, 1, 0);




        glRotatef(90, 1, 0, 0);
        glScalef(1,0.3*next_stickScale+1,1);
        glScalef(0.5,4,0.5);

        //glScalef(0.25,8,0.25);
        sticks.drawGeneric(option);
    glPopMatrix();
}
