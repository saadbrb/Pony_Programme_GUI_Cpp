#ifndef PONY_H
#define PONY_H

#include <iostream>
#include <QPointF>
#include <QPainter>


class Pony
{
protected:
    int geburtsJahr;
    std::string name;
    QPointF ort;
    QColor color;
    std::string type;

public:
    Pony(int geburtsJahr_, std::string name_, QPointF ort_,  QColor color_):geburtsJahr(geburtsJahr_),
        name(name_), ort(ort_), color(color_){}
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
    virtual void mallen(QPainter* objkt) = 0;
    virtual bool istReitbar(int) = 0 ;
    virtual void zeigInfo() = 0;
    virtual bool isNear(QPointF p) = 0; //Diese Funktion prüft, ob diese gedrücktte maus auf dem Objekt ist
    virtual ~Pony() = default;
};

#endif // PONY_H
