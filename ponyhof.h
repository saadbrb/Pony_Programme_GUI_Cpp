#ifndef PONYHOF_H
#define PONYHOF_H

#include "stall.h"

class Ponyhof
{
private:
    Stall stall;
    QVector<Pony*> beimReiten;
    QVector<Pony*> weide;

public:
    Ponyhof();
    void addPonyToStall(Pony*);
    void stallClear();
    void addPonyToReitenBox(Pony*);
    void addPonyToWeideBox();
    QVector<Pony*>& getWeideBox();
    void allePonysMallen(QPainter*event);
    Pony* getInfo(QPointF);

};

#endif // PONYHOF_H
