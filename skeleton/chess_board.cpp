#include "chess_board.h"

_chess_board::_chess_board(float Size, int division )
{
    Vertices.reserve(4+((division+1)*(division+1)));

    float interval = Size/(float)division;
    float interval_text = 1.0/(float)division;
    float y_vert = Size/(float)division;
    for(int i = 0; i < division+1; i++){
        for(int j = 0; j < division+1; j++){
            Vertices.push_back(_vertex3f(-(Size/2.0)+interval*(float)j,(Size/2.0),-(Size/2.0)+interval*(float)i));
            coordTex.push_back(vector<GLfloat>{interval_text*(float)j, (float)(1.0)-interval_text*(float)i});
        }
    }

    Vertices.push_back(_vertex3f(-Size/2,-Size/2,-Size/2));
    coordTex.push_back(vector<GLfloat>{-1,-1});

    Vertices.push_back(_vertex3f(Size/2,-Size/2,-Size/2));
    coordTex.push_back(vector<GLfloat>{-1,-1});

    Vertices.push_back(_vertex3f(-Size/2,-Size/2,Size/2));
    coordTex.push_back(vector<GLfloat>{-1,-1});

    Vertices.push_back(_vertex3f(Size/2,-Size/2,Size/2));
    coordTex.push_back(vector<GLfloat>{-1,-1});


    Triangles.resize((division*2*division)+10);

    for(int i = 0; i < division; i++){
        for(int j = 0; j < division; j++){
            Triangles.push_back(_vertex3ui(i*(division+1)+j+1,i*(division+1)+j,(i+1)*(division+1)+j));
            Triangles.push_back(_vertex3ui(i*(division+1)+j+1, (i+1)*(division+1)+j, (i+1)*(division+1)+j+1));
        }
    }



    int last = Vertices.size()-1;
    //Back side
    Triangles.push_back(_vertex3ui(0, division, last-3));
    Triangles.push_back(_vertex3ui(division,last-2, last-3));
    // Right side
    Triangles.push_back(_vertex3ui(division, last-4, last-2));
    Triangles.push_back(_vertex3ui(last-4, last, last-2));
    //Front side
    Triangles.push_back(_vertex3ui( last-4,last-4-division, last));
    Triangles.push_back(_vertex3ui(last-4-division, last-1, last));
    //Left side
    Triangles.push_back(_vertex3ui(last-1,  last-4-division,0));
    Triangles.push_back(_vertex3ui(last-3,  last-1,0));
    //Bottom side
    Triangles.push_back(_vertex3ui(last-1,last-3, last-2));
    Triangles.push_back(_vertex3ui(last, last-1,last-2));

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
        //glScalef(5,.1,5);
        drawEspecified(option);
    glPopMatrix();

}
