#ifndef PLYOBJECT_H
#define PLYOBJECT_H
#include <string>
#include "object3d.h"
#include <cstring>
#include "file_ply_stl.h"
#include "revolutionobject.h"
#include "colors.h"

class _PLYobject:public _object3D,public _revolutionObject
{
    _file_ply File_ply;
public:
  _PLYobject(std::string nombre = "peonZ.ply", float rev = 12, bool ejeY = false, bool ejeX = false);
  void draw_fill(bool selected);
};

#endif // PLYOBJECT_H
