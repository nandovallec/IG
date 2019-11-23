#ifndef _BODY_H
#define _BODY_H
#include "human.h"
#include "head.h"
#include "torso.h"
#include <QApplication>
#include <QtGui>

#include <qobject.h>


class _body : public _human, public QObject
{
protected:
    _torso torso;
    _head head;


public:
    _body();
    void drawGeneric(int option);
    void startAnimation();



};

#endif // _BODY_H
