#ifndef PONYHOF_H
#define PONYHOF_H
#include <QVector>
#include "stall.h"

class Ponyhof
{
private:
    Stall stall;
    QVector<std::shared_ptr<Pony>> beimReiten;
    QVector<std::shared_ptr<Pony>> weide;
    std::string ponyOrtBox;

public:
    Ponyhof();
    void addPonyToStall(std::shared_ptr<Pony>);
    void stallClear();
    void addPonyToReitenBox();
    void addPonyToWeideBox();
    QVector<std::shared_ptr<Pony>>& getReitenBox();
    QVector<std::shared_ptr<Pony>>& getWeideBox();
    void allePonysMallen(QPainter*event);
    std::shared_ptr<Pony> getInfo(QPointF);
    std::shared_ptr<Pony>  getPony(QPointF punkt);
    void setPonyPositionImGrid(std::shared_ptr<Pony>);
    void setPonyPositionInBox(std::string ponyOrtBox_, std::shared_ptr<Pony>ponyPtr);



};

#endif // PONYHOF_H
