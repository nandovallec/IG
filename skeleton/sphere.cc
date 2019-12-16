#include "sphere.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#define PI 3.14159265

_sphere::_sphere(float Size, float Layers, float rev)
{

  revoluciones = rev;
  layers = Layers;
  //Vertices.resize(Layers+2);


  //Vertices.push_back(_vertex3f(0,Size/2.0, 0));

  float prog = 0;//(Size)/Layers;
  for(int i = 0; i <= Layers; i++){
    Vertices.push_back(_vertex3f(Size/2*cos((90-prog)*PI / 180), Size/2*sin((90-prog)*PI / 180), 0));
    prog += (180)/Layers;
  }
  this->revolucionar(Vertices, revoluciones);
  this->connect(Vertices, Triangles, revoluciones);
  //cerr<<"s"<<Size<<"   "<< Size*sin((90-prog)*PI / 180)<<endl;
  //Vertices[Layers+1]=_vertex3f(0,-(Size/2.0),0);
//cerr<<-(Size/2.0)<<endl;
  //cerr<<"tam es "<< Vertices.size()<<endl;
  //if(Layers == 2)
    calculateNormals();

    //if (Layers == 4){
        float progres = 1;
        float step = 1.0/(revoluciones);
        float progres_layer = 1;
        float step_layer = 1.0/(layers);
        progres_layer = progres_layer - step_layer;
        coordTex.push_back({-1, 1});
        for(int j = 0; j < layers-1; j++){
            progres = 1;
            for(int i = 0; i < revoluciones; i++){
                //cout << "Meto" << progres<<", 1" <<endl;

                coordTex.push_back({fabs(progres),fabs(progres_layer)});
                progres = progres - step;
            }
            progres_layer = progres_layer - step_layer;
       }




        coordTex.push_back({-1,0});
        /*cout << "VERT" << Vertices.size() << "   an "<< coordTex.size()<<endl;
        for(auto it: coordTex)
            cout << it[0] << " and "<< it[1]<<"  " << Size<<endl;*/
    //}

}

void _sphere::calculateNormals(){
    //cout << "mehhh"<<endl;
    _vertex3f first, second;

    //std::for_each(v.begin(), v.end(), &foo);
    for(int i = 0; i < Vertices.size(); i++){
        normalVertices.push_back(Vertices[i]);
    }
    for(int i = 0; i < Triangles.size(); i++){
        float sum_x = Vertices[Triangles[i].x].x + Vertices[Triangles[i].y].x + Vertices[Triangles[i].z].x;
        float sum_y = Vertices[Triangles[i].x].y + Vertices[Triangles[i].y].y + Vertices[Triangles[i].z].y;
        float sum_z = Vertices[Triangles[i].x].z + Vertices[Triangles[i].y].z + Vertices[Triangles[i].z].z;

        normalTriangles.push_back(_vertex3f(sum_x/3.0, sum_y/3.0, sum_z/3.0));

    }

    //normalTriangles[revoluciones+1].x = 0;
   /* cout << "AAAA"; Vertices[0].show_values();
    for (auto it: normalVertices){
        it.show_values();
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


void _sphere::draw_texture(){
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



        for(unsigned int i = 0;i<revoluciones;i++){
            if(i == revoluciones -1){
                if(coordTex[Triangles[i]._0][1] == 1){
                    float aver = (coordTex[Triangles[i]._1][0] + coordTex[Triangles[i]._2][0])/2.0;
                    if(coordTex[Triangles[i]._1][0] == 1 || coordTex[Triangles[i]._2][0] == 1)
                        aver = (coordTex[Triangles[i]._1][0] + coordTex[Triangles[i]._2][0]-1.0)/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._0][1]);
                }else if (coordTex[Triangles[i]._0][0] == 1){
                    glTexCoord2f(0,coordTex[Triangles[i]._0][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);


                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;
                if(coordTex[Triangles[i]._1][1] == 1){
                    float aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._2][0])/2.0;
                    if(coordTex[Triangles[i]._0][0] == 1 || coordTex[Triangles[i]._2][0] == 1)
                        aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._2][0]-1.0)/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._1][1]);
                    //cout << "AVER "<< aver<<endl;
                }else if (coordTex[Triangles[i]._1][0] == 1){
                    glTexCoord2f(0,coordTex[Triangles[i]._1][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);


                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;
                if(coordTex[Triangles[i]._2][1] == 1){
                    float aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._1][0])/2.0;
                    if(coordTex[Triangles[i]._0][0] == 1 || coordTex[Triangles[i]._1][0] == 1)
                        aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._1][0]-1.0)/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._2][1]);
                }else if (coordTex[Triangles[i]._2][0] == 1){
                    glTexCoord2f(0,coordTex[Triangles[i]._2][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);


                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl<<endl;
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
            }
            else{
                if(coordTex[Triangles[i]._0][1] == 1){
                    float aver = (coordTex[Triangles[i]._1][0] + coordTex[Triangles[i]._2][0])/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._0][1]);

                }else
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);


                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;
                if(coordTex[Triangles[i]._1][1] == 1){
                    float aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._2][0])/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._1][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);


                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;
                if(coordTex[Triangles[i]._2][1] == 1){
                    float aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._1][0])/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._2][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);


                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl<<endl;
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
            }
        }

        for (unsigned int i = revoluciones;i<Triangles.size()-revoluciones;i++){

            if(((i - (revoluciones*3-1 ))%revoluciones == 0 )||((i-(revoluciones*3-2))%revoluciones == 0)){
                if (coordTex[Triangles[i]._0][0] == 1)
                    glTexCoord2f(0,coordTex[Triangles[i]._0][1]);
                else
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);

                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;

                if(coordTex[Triangles[i]._1][0] == 1)
                    glTexCoord2f(0,coordTex[Triangles[i]._1][1]);
                else
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);

                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;

                if (coordTex[Triangles[i]._2][0] == 1)
                    glTexCoord2f(0,coordTex[Triangles[i]._2][1]);
                else
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);

                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl;
            //cout <<endl<<endl;
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
            }else{
                if(coordTex[Triangles[i]._0][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);

                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;

                if(coordTex[Triangles[i]._1][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);

                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;

                if(coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);

                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl;

            }

        }

        for(unsigned int i = Triangles.size()-revoluciones; i<Triangles.size();i++){
            if(i == Triangles.size()-revoluciones){
                if(coordTex[Triangles[i]._0][1] == 0){
                    float aver = (coordTex[Triangles[i]._1][0] + coordTex[Triangles[i]._2][0])/2.0;
                    if(coordTex[Triangles[i]._1][0] == 1 || coordTex[Triangles[i]._2][0] == 1)
                        aver = (coordTex[Triangles[i]._1][0] + coordTex[Triangles[i]._2][0]-1.0)/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._0][1]);
                }else if (coordTex[Triangles[i]._0][0] == 1){
                    glTexCoord2f(0,coordTex[Triangles[i]._0][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);


                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;
                if(coordTex[Triangles[i]._1][1] == 0){
                    float aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._2][0])/2.0;
                    if(coordTex[Triangles[i]._0][0] == 1 || coordTex[Triangles[i]._2][0] == 1)
                        aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._2][0]-1.0)/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._1][1]);
                    //cout << "AVER "<< aver<<endl;
                }else if (coordTex[Triangles[i]._1][0] == 1){
                    glTexCoord2f(0,coordTex[Triangles[i]._1][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);


                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;
                if(coordTex[Triangles[i]._2][1] == 0){
                    float aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._1][0])/2.0;
                    if(coordTex[Triangles[i]._0][0] == 1 || coordTex[Triangles[i]._1][0] == 1)
                        aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._1][0]-1.0)/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._2][1]);
                }else if (coordTex[Triangles[i]._2][0] == 1){
                    glTexCoord2f(0,coordTex[Triangles[i]._2][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);


                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl<<endl;
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
            }
            else{
                if(coordTex[Triangles[i]._0][1] == 0){
                    float aver = (coordTex[Triangles[i]._1][0] + coordTex[Triangles[i]._2][0])/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._0][1]);

                }else
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);


                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                //cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;
                if(coordTex[Triangles[i]._1][1] == 0){
                    float aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._2][0])/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._1][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);


                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                //cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;
                if(coordTex[Triangles[i]._2][1] == 0){
                    float aver = (coordTex[Triangles[i]._0][0] + coordTex[Triangles[i]._1][0])/2.0;
                    glTexCoord2f(aver, coordTex[Triangles[i]._2][1]);
                }else
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);


                //cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl<<endl;
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
            }

        }


        /*for (unsigned int i = Triangles.size()-2-revoluciones;i<Triangles.size();i++){
            //cout << "meh"<<endl;
                if(coordTex[Triangles[i]._0][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._0][0],coordTex[Triangles[i]._0][1]);
                else if (coordTex[Triangles[i]._0][0] == 1)
                    glTexCoord2f(0,coordTex[Triangles[i]._0][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._0]));      // UP RIGHT CORNER
                cout << "Vertex " << Triangles[i]._0 << "           "<< coordTex[Triangles[i]._0][0] << "    and     "<< coordTex[Triangles[i]._0][1]<<endl;

                if(coordTex[Triangles[i]._1][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._1][0],coordTex[Triangles[i]._1][1]);
                else if (coordTex[Triangles[i]._1][0] == 1)
                    glTexCoord2f(0,coordTex[Triangles[i]._1][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._1]));      // DOWN LEFT CORNER
                cout << "Vertex " << Triangles[i]._1 << "           "<< coordTex[Triangles[i]._1][0] << "    and     "<< coordTex[Triangles[i]._1][1]<<endl;

                if(coordTex[Triangles[i]._2][0] != -1)
                    glTexCoord2f(coordTex[Triangles[i]._2][0],coordTex[Triangles[i]._2][1]);
                else if (coordTex[Triangles[i]._2][0] == 1)
                    glTexCoord2f(0,coordTex[Triangles[i]._2][1]);
                glVertex3fv((GLfloat *) &(Vertices[(Triangles)[i]._2]));      // DOWN RIGHT CORNER
                cout << "Vertex " << Triangles[i]._2 << "           "<< coordTex[Triangles[i]._2][0] << "    and     "<< coordTex[Triangles[i]._2][1]<<endl;


        }*/




        glEnd();

    glDisable(GL_TEXTURE_2D);
}
