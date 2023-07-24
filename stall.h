#ifndef STALL_H
#define STALL_H

#include <QVector>
#include "pony.h"


class Stall
{
private:
    QVector<Pony*> pferdeboxen;
public:
    Stall();
    int belegteBoxen();
    bool einstellen(Pony*);
    Pony* herausholen(std::string);
    float durchschnitalter();
    void weidegang();
    QVector<Pony*> getPonys();
    void clear();
    void zeigInfo();
    void pferdeBoxenMallen(QPainter* event);

};

#endif // STALL_H
