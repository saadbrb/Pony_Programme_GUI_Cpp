#include <memory>

#include "pony.h"


std::string Pony::getName(){
    return name;
}
void Pony::setName(std::string name){
    this->name = name;
}
int Pony::getGeburtsjahr(){
    return geburtsJahr;
}
void Pony::setGeburtsjahr(int geburtsJahr){
    this->geburtsJahr = geburtsJahr;
}

std::string Pony::getType(){
    return type;
}

void Pony::setzePos(const QPointF& position){
    firstPunkt = position;
}
void Pony::setPos(QPointF p){
    firstPunkt = p;
    lastPunkt.rx() = firstPunkt.x() + 6;
    lastPunkt.ry() = firstPunkt.y() + 6;
}

QPointF Pony::getPos(){
    return firstPunkt;
}

qreal Pony::minF(qreal x, qreal y){
    return qMin(x,y);
}
qreal Pony::maxF(qreal x, qreal y){
    return qMax(x,y);
}
