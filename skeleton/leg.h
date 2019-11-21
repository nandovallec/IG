#ifndef LEG_H
#define LEG_H
#include "human.h"
#include "cylinder.h"
#include "feet.h"

class _leg : public _human
{
private:
    //_cylinder cylinder =
    _feet feet;
public:
    _leg();
    void drawGeneric(int option);

};

#endif // LEG_H
