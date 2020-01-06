#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include "object3d.h"
#include <QtGui>
#include "colors.h"
#include <qobject.h>

class _chess_board : public _object3D
{
public:
    _chess_board(float Size = 1.0, int division = 1);
    void drawGeneric(int option, bool first = true, bool second = true);
    void drawEspecified(int option, bool first, bool second);
    void draw_texture();
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
    void turnFlatShading(bool firstLight, bool secondLight);
    void turnSmoothShading(bool firstLight, bool secondLight);
    void draw_selection();
    void draw_texture_flat_shading(bool first, bool second);
    void draw_texture_gourand_shading(bool first, bool second);
};

#endif // _CHESS_BOARD_H
