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
    ort = position;
}
void Pony::setPos(QPointF p){
    ort = p;
}

QPointF Pony::getPos(){
    return ort;
}

qreal Pony::minF(qreal x, qreal y){
    return qMin(x,y);
}
qreal Pony::maxF(qreal x, qreal y){
    return qMax(x,y);
}
