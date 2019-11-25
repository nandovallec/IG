#ifndef _REVOLUTIONOBJECT_H
#define _REVOLUTIONOBJECT_H
#include "object3d.h"


class _revolutionObject
{
public:
    _revolutionObject();
    void revolucionar(vector<_vertex3f> &Vertices, int revoluciones);
    void connect(vector<_vertex3f> &Vertices, vector<_vertex3ui> & Triangles,int revoluciones);

    _vertex3f getPointsBetw(_vertex3f x, _vertex3f y, float t);


    int rightVert(int i, int layer, int rev);
    int downVert(int i, int rev);
    int downRight(int i, int layer, int rev);
};

#endif // _REVOLUTIONOBJECT_H
