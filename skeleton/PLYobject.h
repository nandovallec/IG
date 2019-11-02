#ifndef PLYOBJECT_H
#define PLYOBJECT_H
#include <string>
#include "object3d.h"
#include <cstring>
#include "file_ply_stl.h"

class _PLYobject:public _object3D
{
    _file_ply File_ply;
public:
  _PLYobject(std::string nombre = "ant.ply", float rev = 12);
};

#endif // PLYOBJECT_H
