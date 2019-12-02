#ifndef TEXTURELIGHT_H
#define TEXTURELIGHT_H
#include <GL/gl.h>
#include "torso.h"
#include "axis.h"
#include "cube.h"
#include "cone.h"
#include "cylinder.h"
#include "tetrahedron.h"
#include "sphere.h"
#include "PLYobject.h"
#include "human.h"
#include "body.h"


class _textureLight
{
private:
    // Polished silver
    GLfloat mat_ambient[4]  = { 0.23125,  0.23125,  0.23125,  1.0 };
    GLfloat mat_diffuse[4]  = { 0.2775,   0.2775,   0.2775,   1.0 };
    GLfloat mat_specular[4] = { 0.773911, 0.773911, 0.773911, 1.0 };
    GLfloat shine[1] = { 89.6 };


    float radiusLight	  = 5;
    float stepCircle	  = 0;
    GLfloat posicion_luz_0[4]  = { 0.0, 5.0, 0.0, 0.0 };							// DIRECCIONAL - inf therefore difussion and specular doesnt use position
    GLfloat posicion_luz_1[4]  = { radiusLight, 4, radiusLight, 1.0 };	// POSICIONAL
    GLfloat luz_difusa_1[4]	  = { 1.0, 0.0, 1.0, 0.0 };
    GLfloat luz_especular_1[4] = { 1.0, 0.0, 1.0, 0.0 };





public:
    _textureLight();
    void smoothShading();

    template <typename T>
    void turnLight(T &obj, bool first, bool second);
    void nextStep(int step);
    void prevStep(int step);


};

template <typename T>
void _textureLight::turnLight(T &obj, bool first, bool second){
    glColor3f(0.0,0.0,0.0);
    glShadeModel (obj.shadeKind);
    posicion_luz_1[0] = radiusLight*sin(stepCircle);
    posicion_luz_1[2] = radiusLight*cos(stepCircle);
    if(obj.normalVertices.size()==0)
        obj.calculateNormals();

    if(first)
        glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz_0);

    if(second){
        glLightfv(GL_LIGHT1, GL_POSITION, posicion_luz_1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,  luz_difusa_1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular_1);
    }
    //glLight


    glEnable(GL_LIGHTING);
    if(first)
        glEnable(GL_LIGHT0);
    if(second)
        glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    //cout << obj.Vertices.size() << "aaaa";
        //obj.Vertices.pop_back();
        //obj.normalVertices.pop_back();
        glVertexPointer( 3, GL_FLOAT, 0, obj.Vertices.data() );
        glNormalPointer( GL_FLOAT, 0, obj.normalVertices.data() );
        //cout << obj.Vertices.size() << endl;

    // Para añadir las luces a las texturas, descomentar las siguientes líneas
    // if (imagen != ""){ draw_texturas(imagen); }

    //else{
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);


        //OPTION1
        if(obj.shadeKind != GL_FLAT)
            glDrawElements( GL_TRIANGLES, (obj.Triangles.size())*3, GL_UNSIGNED_INT, obj.Triangles.data() ) ;
        else{
        //OPTION2
        glBegin(GL_TRIANGLES);
                for (int i = 0; i<obj.Triangles.size(); i++) {
                    glNormal3fv((GLfloat *)&(obj.normalTriangles[i]));
                    glVertex3fv((GLfloat *)&obj.Vertices[obj.Triangles[i].x]);
                    glVertex3fv((GLfloat *)&obj.Vertices[obj.Triangles[i].y]);
                    glVertex3fv((GLfloat *)&obj.Vertices[obj.Triangles[i].z]);
                }
                glEnd();
        }
    //}

    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHTING);




}


#endif // TEXTURELIGHT_H
