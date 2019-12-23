/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "object3d.h"
#define PI 3.14159265

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glBegin(GL_TRIANGLES);
  for (unsigned int i=0;i<Triangles.size();i++){
      //cerr<<i<<"  connect "<< Triangles[i]._0<<" "<<Triangles[i]._0<< "  "<<Triangles[i]._0<<"  "<<i<<endl;
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
  }
  glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);

    for (unsigned int i=0;i<Triangles.size();i++){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(0.0,1.0,0.0);
    for (unsigned int i=0;i<Triangles.size();i=i+2){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glColor3f(0.0,.5,0.5);
    for (unsigned int i=1;i<Triangles.size();i=i+2){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();

}

vector<_vertex3ui> _object3D::getTriangles(){
    return Triangles;
}

void _object3D::calculateNormals(){
    cout << "Object"<<endl;
    _vertex3f first, second;
    for(int i = 0; i < Vertices.size(); i++){
        normalVertices.push_back(_vertex3f(0.0,0.0,0.0));
    }
    //std::for_each(v.begin(), v.end(), &foo);
    for(int i = 0; i < Triangles.size(); i++){
        first = Vertices[Triangles[i].y] - Vertices[Triangles[i].x];
        second = Vertices[Triangles[i].z] - Vertices[Triangles[i].x];

        _vertex3f to_add = first.cross_product(second);

        normalTriangles.push_back(to_add);

        //cout << endl<<"size"<<normalTriangles.size() <<"    i"<<Triangles[i].x;to_add.show_values();
        //cout << "Product "<<i <<"   "<<(first.cross_product(second)).dot_product(_vertex3f(0.1,0.1,0.1))<<endl;
        //cout << "Adding to "<<Triangles[i].x << "   "<<Triangles[i].y << "   "<<Triangles[i].z << "   "<<endl;
        normalVertices[Triangles[i].x] = normalVertices[Triangles[i].x] + normalTriangles[i];
        normalVertices[Triangles[i].y] = normalVertices[Triangles[i].y] + normalTriangles[i];
        normalVertices[Triangles[i].z] = normalVertices[Triangles[i].z] + normalTriangles[i];

    }

    //normalTriangles[revoluciones+1].x = 0;

  /*  for (auto it: normalTriangles){
        float sqr = it.x * it.x + it.y * it.y + it.z + it.z;
        it.x = it.x / (float)sqrt(sqr);
        it.y = it.y / (float)sqrt(sqr);
        it.z = it.z / (float)sqrt(sqr);
    }*/

    // Let x=a y=b z=c, when I insert the shading it gets the rotation wrong so I have to rotate the Vertices
    /*Triangles[12].x = 13;
    Triangles[12].y = 12;
    Triangles[12].z = 1;

    */
    //normalTriangles.push_back(normalTriangles[normalTriangles.size()-1]);
    //cout<< "t"<<Triangles.size()<<"    tn"<<normalTriangles.size();
    //cout<<Triangles.size()<<endl;
    //Triangles.erase(Triangles.begin()+revoluciones);
    //cout<<Triangles.size()<<endl;
}





void _object3D::nextStep(int step){
    stepCircle += ((2*PI)/step);
    if(stepCircle > 2*PI)
            stepCircle -= 2*PI;

}

void _object3D::prevStep(int step){
    stepCircle -= ((2*PI)/step);
    if(stepCircle < 0)
            stepCircle += 2*PI;

}

void _object3D::turnFlatShading(bool first, bool second){
    glShadeModel(GL_FLAT);
    glColor3f(0.0,0.0,0.0);
    //cout << "Rad"<<endl;
    static int cou = 0;
    //cou++;
    //cout << "meh"<< cou;
    posicion_luz_1[0] = radiusLight*sin(stepCircle);
    posicion_luz_1[2] = radiusLight*cos(stepCircle);
    if(normalVertices.size() == 0)
        calculateNormals();

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

    //glEnableClientState( GL_VERTEX_ARRAY );
    //glEnableClientState( GL_NORMAL_ARRAY );
    //cout << obj.Vertices.size() << "aaaa";
        //obj.Vertices.pop_back();
        //obj.normalVertices.pop_back();
        //glVertexPointer( 3, GL_FLOAT, 0, obj.Vertices.data() );
        //glNormalPointer( GL_FLOAT, 0, obj.normalVertices.data() );
        //cout << obj.Vertices.size() << endl;


    //else{
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine[optionMaterial]);


        //OPTION1
        //if(obj.shadeKind != GL_FLAT)
            //glDrawElements( GL_TRIANGLES, (obj.Triangles.size())*3, GL_UNSIGNED_INT, obj.Triangles.data() ) ;
            //obj.draw_fill();
        //else{
        //OPTION2
        glPolygonMode(GL_FRONT,GL_FILL);
        //cout << "Tam "<< obj.Vertices.size() << "      "<< obj.Triangles.size()<<endl;
        glBegin(GL_TRIANGLES);
                //Fallo esta en obj.revoluciones*3

                //cout << endl<<"Fallos: "; Triangles[12].show_values(); cout << "     "; Triangles[13].show_values();

                /*obj.normalTriangles[obj.revoluciones*3].x *= 5.0; mir 5 y 8
                obj.normalTriangles[obj.revoluciones*3].y *= 5.0;
                obj.normalTriangles[obj.revoluciones*3].z *= 5.0;*/
                for (int i = 0; i<Triangles.size(); i++) {
                    glNormal3fv((GLfloat *) &(normalTriangles[i]));
                    glVertex3fv((GLfloat *) &Vertices[Triangles[i].x]);
                    glVertex3fv((GLfloat *) &Vertices[Triangles[i].y]);
                    glVertex3fv((GLfloat *) &Vertices[Triangles[i].z]);

                }

                /*for (unsigned int i=0;i<obj.Vertices.size();i++){
                  glVertex3fv((GLfloat *) &obj.Vertices[i]);
                }*/
                //obj.draw_point();
                glEnd();

        //}*/
    //}

    //glDisableClientState( GL_NORMAL_ARRAY );
    //glDisableClientState( GL_VERTEX_ARRAY );

    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHTING);

}
void _object3D::turnSmoothShading(bool first, bool second){
    glShadeModel(GL_SMOOTH);
    glColor3f(0.0,0.0,0.0);
    posicion_luz_1[0] = radiusLight*sin(stepCircle);
    posicion_luz_1[2] = radiusLight*cos(stepCircle);
    if(normalVertices.size()==0)
        calculateNormals();

    if(first)
        glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz_0);

    if(second){
        glLightfv(GL_LIGHT1, GL_POSITION, posicion_luz_1);
        glLightfv(GL_LIGHT1, GL_AMBIENT,  luz_ambient_1);
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

    //glEnableClientState( GL_VERTEX_ARRAY );
    //glEnableClientState( GL_NORMAL_ARRAY );
    //cout << obj.Vertices.size() << "aaaa";
        //obj.Vertices.pop_back();
        //obj.normalVertices.pop_back();
        //glVertexPointer( 3, GL_FLOAT, 0, obj.Vertices.data() );
        //glNormalPointer( GL_FLOAT, 0, obj.normalVertices.data() );
        //cout << obj.Vertices.size() << endl;


    //else{
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine[optionMaterial]);


        //OPTION1
        //if(obj.shadeKind != GL_FLAT)
            //glDrawElements( GL_TRIANGLES, (obj.Triangles.size())*3, GL_UNSIGNED_INT, obj.Triangles.data() ) ;
            //obj.draw_fill();
        //else{
        //OPTION2
        glPolygonMode(GL_FRONT,GL_FILL);
        //cout << "Tam "<< obj.Vertices.size() << "      "<< obj.Triangles.size()<<endl;
        glBegin(GL_TRIANGLES);
                //Fallo esta en obj.revoluciones*3
                //cout << endl<<"Fallos: "; Vertices[8].show_values(); cout << "     "; Vertices[7].show_values();
                /*obj.normalTriangles[obj.revoluciones*3].x *= 5.0; mir 5 y 8
                obj.normalTriangles[obj.revoluciones*3].y *= 5.0;
                obj.normalTriangles[obj.revoluciones*3].z *= 5.0;*/

                for (int i = 0; i<Triangles.size(); i++) {
                    glNormal3fv((GLfloat *) &(normalVertices[Triangles[i].x]));
                    glVertex3fv((GLfloat *) &Vertices[Triangles[i].x]);
                    glNormal3fv((GLfloat *) &(normalVertices[Triangles[i].y]));
                    glVertex3fv((GLfloat *) &Vertices[Triangles[i].y]);
                    glNormal3fv((GLfloat *) &(normalVertices[Triangles[i].z]));
                    glVertex3fv((GLfloat *) &Vertices[Triangles[i].z]);

                }

                /*for (unsigned int i=0;i<obj.Vertices.size();i++){
                  glVertex3fv((GLfloat *) &obj.Vertices[i]);
                }*/
                //obj.draw_point();
                glEnd();

        //}*/
    //}

    //glDisableClientState( GL_NORMAL_ARRAY );
    //glDisableClientState( GL_VERTEX_ARRAY );

    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHTING);

}

void _object3D::draw_texture(){
    // Code for reading an image
    glEnable(GL_TEXTURE_2D);

    //unsigned int texture;
    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);

        // Code to control the application of the texture
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Code to pass the image to OpenGL to form a texture 2D
        glTexImage2D(GL_TEXTURE_2D,0,3,Image.width(),Image.height(),0,GL_RGB,GL_UNSIGNED_BYTE,Image.bits());

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glPolygonMode(GL_FRONT,GL_FILL);
        glBegin(GL_TRIANGLES);


        for (unsigned int i=0;i<Triangles.size();i++){

                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;

                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;

                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl;



        }

        glEnd();

    glDisable(GL_TEXTURE_2D);
}

void _object3D::setImage(QImage image){
    this->Image = image;
}

void _object3D::draw_texture_flat_shading(bool first, bool second){
    // Code for reading an image
    glShadeModel(GL_FLAT);
    glColor3f(0.0,0.0,0.0);
    //static int cou = 0;
    //cou++;
    //cout << "meh"<< cou<<endl;
    posicion_luz_1[0] = radiusLight*sin(stepCircle);
    posicion_luz_1[2] = radiusLight*cos(stepCircle);
    if(normalVertices.size() == 0)
        calculateNormals();

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

    //glEnableClientState( GL_VERTEX_ARRAY );
    //glEnableClientState( GL_NORMAL_ARRAY );
    //cout << obj.Vertices.size() << "aaaa";
        //obj.Vertices.pop_back();
        //obj.normalVertices.pop_back();
        //glVertexPointer( 3, GL_FLOAT, 0, obj.Vertices.data() );
        //glNormalPointer( GL_FLOAT, 0, obj.normalVertices.data() );
        //cout << obj.Vertices.size() << endl;


    //else{
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine[optionMaterial]);
    glEnable(GL_TEXTURE_2D);

    //unsigned int texture;
    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);

        // Code to control the application of the texture
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Code to pass the image to OpenGL to form a texture 2D
        glTexImage2D(GL_TEXTURE_2D,0,3,Image.width(),Image.height(),0,GL_RGB,GL_UNSIGNED_BYTE,Image.bits());

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glPolygonMode(GL_FRONT,GL_FILL);
        glBegin(GL_TRIANGLES);


        for (unsigned int i=0;i<Triangles.size();i++){
                glNormal3fv((GLfloat *) &(normalTriangles[i]));

                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;

                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;

                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl;



        }

        glEnd();



    glDisable(GL_TEXTURE_2D);

    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHTING);
}

void _object3D::draw_texture_gourand_shading(bool first, bool second){
    // Code for reading an image
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glColor3f(0.0,0.0,0.0);
    posicion_luz_1[0] = radiusLight*sin(stepCircle);
    posicion_luz_1[2] = radiusLight*cos(stepCircle);
    if(normalVertices.size()==0)
        calculateNormals();

    if(first)
        glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz_0);

    if(second){
        glLightfv(GL_LIGHT1, GL_POSITION, posicion_luz_1);
        glLightfv(GL_LIGHT1, GL_AMBIENT,  luz_ambient_1);
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

    //else{
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[optionMaterial]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine[optionMaterial]);
    //unsigned int texture;
    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);

        // Code to control the application of the texture
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Code to pass the image to OpenGL to form a texture 2D
        glTexImage2D(GL_TEXTURE_2D,0,3,Image.width(),Image.height(),0,GL_RGB,GL_UNSIGNED_BYTE,Image.bits());

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glPolygonMode(GL_FRONT,GL_FILL);
        glBegin(GL_TRIANGLES);


        for (unsigned int i=0;i<Triangles.size();i++){
                glNormal3fv((GLfloat *) &(normalVertices[Triangles[i].x]));
                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;

                glNormal3fv((GLfloat *) &(normalVertices[Triangles[i].y]));
                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;

                glNormal3fv((GLfloat *) &(normalVertices[Triangles[i].z]));
                if(coordTex[Triangles[i]._0][0] != -1 && coordTex[Triangles[i]._1][0] != -1 && coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl;



        }


        glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHTING);
}






