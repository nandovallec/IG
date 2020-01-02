#include "PLYobject.h"
#include <fstream>
#include <sstream>
#include <qdir.h>




_PLYobject::_PLYobject(string name, float rev, bool ejeY, bool ejeX){
    revoluciones = rev;
    /*std::ifstream infile;
    std::string line;
    bool begCoord = false;
    float x,y,z;
    cerr<<"xxxxxxxxxxxxxx"<<endl;
    string dirs = QDir::current().currentPath().toStdString();

            cerr<<dirs<<endl;
    infile.open(dirs+"/peon.ply");
    if(!infile.is_open())
        cerr<<"NOOO"<<endl;


    for(std::string line; getline(infile, line );){
        cerr<<"xxxxxxxxxxxxxx"<<endl;

        cerr<<line<<endl;
        if(begCoord){

            std::istringstream iss(line);
            iss >> x >> y >> z;
            Vertices.push_back(_vertex3f(x,y,z));
        }
        if (!begCoord && line.find("end") != std::string::npos)
           begCoord = true;

    }
    if(Vertices[0].x != 0)
        Vertices.insert(Vertices.begin(),_vertex3f(0,Vertices[0].y,0));
    if(Vertices[Vertices.size()-1].x != 0)
        Vertices.insert(Vertices.end(), _vertex3f(0, Vertices[Vertices.size()-1].y));
    */

    if (File_ply.open(name.c_str())){
      File_ply.read(Vertices,Triangles);
      std::cout << "File read correctly" << std::endl;
      //for(auto i: Vertices)
      //    cerr<<"----"<< i.x<<"----"<<i.y<<"----"<<i.z<<endl;

      if(Triangles.size() <= 1){
          if(ejeY){
              if(Vertices[0].x != 0)
                  Vertices.insert(Vertices.begin(),_vertex3f(0,Vertices[0].y,0));
              if(Vertices[Vertices.size()-1].x != 0)
                  Vertices.insert(Vertices.end(), _vertex3f(0, Vertices[Vertices.size()-1].y, 0));

              this->revolucionar(Vertices, revoluciones);
          }else if(ejeX){
                  if(Vertices[0].y != 0)
                      Vertices.insert(Vertices.begin(),_vertex3f(Vertices[0].x, 0, 0));
                  if(Vertices[Vertices.size()-1].y != 0)
                      Vertices.insert(Vertices.end(), _vertex3f(Vertices[Vertices.size()-1].x, 0 , 0));

                  this->revolucionarX(Vertices, revoluciones);
          }else{
              if(Vertices[0].x != 0)
                  Vertices.insert(Vertices.begin(),_vertex3f(0, 0, Vertices[0].z));
              if(Vertices[Vertices.size()-1].x != 0)
                  Vertices.insert(Vertices.end(), _vertex3f(0 , 0, Vertices[Vertices.size()-1].z));

              this->revolucionarZ(Vertices, revoluciones);
          }
          Triangles.clear();
          this->connect(Vertices, Triangles, revoluciones);
      }
    }
    else std::cout << "File can't be opened" << std::endl;

}
