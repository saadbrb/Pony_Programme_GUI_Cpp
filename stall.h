#ifndef STALL_H
#define STALL_H

#include <QVector>
#include "pony.h"


class Stall
{
private:
    QVector<std::shared_ptr<Pony>> pferdeboxen;
public:
    Stall();
    int belegteBoxen();
    bool einstellen(std::shared_ptr<Pony>);
    void zumReitenherausholen(QVector<std::shared_ptr<Pony>>& ponyBox);
    float durchschnitalter();
    void weidegang();
    QVector<std::shared_ptr<Pony> > &getPonys();
    void clear();
    void zeigInfo();
    void pferdeBoxenMallen(QPainter* event);

};

#endif // STALL_H
