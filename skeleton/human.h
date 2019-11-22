#ifndef HUMAN_H
#define HUMAN_H
#include "object3d.h"

class _human:public _object3D
{
protected:
    _vertex3f lineColor = _vertex3f(0,1,.57647);
    _vertex3f fillColor = _vertex3f(.3647,.9725,1);
    static int const MAX_DEGREE_LEGS = 15;
    inline static int rotStick;
    inline static int rotLegs;
    inline static bool reverseLegs;


    //_vertex3f RED(1.0,0,0);
    //_vertex3f fillColor[3]{.5,.5,.5};
    //_vertex3f chessColor[6]{.25, .25, .25, .25, .25, .25};
public:
  _human();

  void draw_point();
  void draw_line();

  void draw_fill();
  void draw_chess();

  virtual void drawGeneric(int option) = 0;
  void drawEspecified(int option);
  void calculateColor(_vertex3f &colors);

  //First degree of freedom
  void incrStickDegree(int step);
  void decrStickDegree(int step);

  //Second degree of freedom
  void incrLegsDegree(int step);
  void decrLegsDegree(int step);



};



#endif // HUMAN_H
