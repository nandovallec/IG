#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include "object3d.h"
#include <QtGui>
#include "colors.h"
#include <qobject.h>

class _chess_board : public _object3D
{
public:
    _chess_board(float Size = 1.0);
    void drawGeneric(int option);
    void drawEspecified(int option);
    void draw_texture();
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

#endif // _CHESS_BOARD_H
