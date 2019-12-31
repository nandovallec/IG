#ifndef _EYE_H
#define _EYE_H
#include "human.h"
#include "semisphere.h"
#include "pupil.h"


class _eye : public _human
{
private:
    _pupil pupil;
public:
    _eye();
    void drawGeneric(int option);

};

#endif // _EYE_H
