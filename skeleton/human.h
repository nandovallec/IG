#ifndef HUMAN_H
#define HUMAN_H
#include "object3d.h"

class _human:public _object3D
{
private:

public:
  _human();

  void draw_point();
  void draw_line();

  void draw_fill();
  void draw_chess();

  virtual void drawGeneric(int option) = 0;
  void drawEspecified(int option);

};



#endif // HUMAN_H
