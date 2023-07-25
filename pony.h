#ifndef PONY_H
#define PONY_H

#include <iostream>
#include <QPointF>
#include <QPainter>
#include <memory>


class Pony
{
protected:
    int geburtsJahr;
    std::string name;
    QPointF firstPunkt;
    QPointF lastPunkt;
    QColor color;
    std::string type;

public:
    Pony(int geburtsJahr_, std::string name_, QPointF firstPunkt_,  QColor color_):geburtsJahr(geburtsJahr_),
        name(name_), firstPunkt(firstPunkt_), color(color_){
        lastPunkt.rx() = firstPunkt.x() + 6;
        lastPunkt.ry() = firstPunkt.y() + 6;
    }
    std::string getName();
    void setName(std::string name);
    int getGeburtsjahr();
    void setGeburtsjahr(int geburtsJahr_);
    void setzePos(const QPointF& position);
    QPointF getPos();
    void setPos(QPointF);
    qreal minF(qreal x, qreal y);
    qreal maxF(qreal x, qreal y);
    std::string getType();
    virtual void movePony(QPointF) = 0 ;
    virtual void mallen(QPainter* objkt) = 0;
    virtual bool istReitbar(int) = 0 ;
    virtual void zeigInfo() = 0;
    virtual QPointF getRefPunkt() = 0;
    virtual bool isNear(QPointF p) = 0; //Diese Funktion prüft, ob diese gedrücktte maus auf dem Objekt ist
    virtual ~Pony() = default;
};

#endif // PONY_H
