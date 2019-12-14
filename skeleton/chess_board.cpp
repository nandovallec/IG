#include "chess_board.h"

_chess_board::_chess_board(float Size )
{
    Vertices.resize(8);


    Vertices[0]=_vertex3f(Size/2,Size/2,-Size/2);
    Vertices[1]=_vertex3f(-Size/2, Size/2,-Size/2);
    Vertices[2]=_vertex3f(-Size/2,-Size/2,-Size/2);
    Vertices[3]=_vertex3f(Size/2,-Size/2,-Size/2);

    Vertices[4]=_vertex3f(Size/2,Size/2,Size/2);
    Vertices[5]=_vertex3f(-Size/2, Size/2,Size/2);
    Vertices[6]=_vertex3f(-Size/2,-Size/2,Size/2);
    Vertices[7]=_vertex3f(Size/2,-Size/2,Size/2);

    Triangles.resize(12);

    Triangles[0]=_vertex3ui(1,0,2);
    Triangles[1]=_vertex3ui(2,0,3);
    Triangles[2]=_vertex3ui(4,0,5);     // TOP
    Triangles[3]=_vertex3ui(5,0,1);
    Triangles[4]=_vertex3ui(5,1,6);
    Triangles[5]=_vertex3ui(6,1,2);
    Triangles[6]=_vertex3ui(6,2,7);
    Triangles[7]=_vertex3ui(7,2,3);
    Triangles[8]=_vertex3ui(7,3,4);
    Triangles[9]=_vertex3ui(4,3,0);
    Triangles[10]=_vertex3ui(4,5,7);
    Triangles[11]=_vertex3ui(5,6,7);

    coordTex = vector <vector <GLfloat>>{{0,1},{1,1},{-1,-1},{-1,-1},{0,0},{1,0},{-1,-1},{-1,-1}};

}

void _chess_board::draw_point(){
    drawGeneric(0);
}
void _chess_board::draw_line(){
    drawGeneric(1);
}
void _chess_board::draw_fill(){
    drawGeneric(2);
}
void _chess_board::draw_chess(){
    drawGeneric(3);
}

void _chess_board::draw_texture(){
    drawGeneric(4);
}


void _chess_board::drawEspecified(int option){
    switch(option){
        case 0:
            _basic_object3D::draw_point();
            break;
        case 1:
            _object3D::draw_line();
            break;
        case 2:
            _object3D::draw_fill();
            break;
        case 3:
            _object3D::draw_chess();
            break;
        case 4:
            _object3D::draw_texture();
    }
}
void _chess_board::drawGeneric(int option){
    //cout<<"Enter"<<option<<endl;

    glPushMatrix();
        glScalef(5,.1,5);
        drawEspecified(option);
    glPopMatrix();

}
