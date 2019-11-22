#ifndef _HEAD_H
#define _HEAD_H
#include "human.h"
#include "sphere.h"
#include "eye.h"
#include "mouth.h"

class _head : public _human
{
private:
    _eye leftEye;
    _eye rightEye;
    _mouth mouth;
public:
    _head();
    void drawGeneric(int option);

};

#endif // _HEAD_H
