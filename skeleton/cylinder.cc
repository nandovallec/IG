#include "cylinder.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cylinder::_cylinder(float Size, float Layers, float rev)
{
  layers = Layers;
  revoluciones = rev;


  Vertices.push_back(_vertex3f(0,Size/2.0, 0));

  float prog = 0;
  for(int i = 0; i <= Layers; i++){
    Vertices.push_back(_vertex3f(Size/2.0, (Size/2.0)-prog, 0));
    prog += (Size)/Layers;
  }
  Vertices.push_back(_vertex3f(0,-(Size/2.0),0));
    //Vertices[1].show_values();
    //Vertices[2].show_values();
    cout<<endl<<endl;
//cerr<<-(Size/2.0)<<endl;
  this->revolucionar(Vertices, revoluciones);
  this->connect(Vertices, Triangles, revoluciones);

    if (Layers == 1){
        float progres = 1;
        float step = 1.0/(revoluciones);
        coordTex.push_back({-1,-1});
        for(int i = 0; i < revoluciones; i++){
            //cout << "Meto" << progres<<", 1" <<endl;

            coordTex.push_back({fabs(progres),1});
            progres = progres - step;
        }
        progres = 1;
        for(int i = 0; i < revoluciones; i++){
            //cout << "Meto " << progres<<", 0" <<endl;

            coordTex.push_back({fabs(progres),0});
            progres = progres - step;
        }



        coordTex.push_back({-1,-1});
        cout << "VERT" << Vertices.size() << "   an "<< coordTex.size()<<endl;
    }
}

void _cylinder::draw_texture(){
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




        for (unsigned int i = 0;i<Triangles.size();i++){

            if((i == (revoluciones*3-1 ) )||(i == (revoluciones*3-2))){
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
            cout <<endl<<endl;
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
