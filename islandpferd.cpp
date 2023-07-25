#include <cmath>
#include "islandpferd.h"


bool Islandpferd::hatEkzemer(){
    return ekzemer;
}
bool Islandpferd::istReitbar(int diesesJahr) {
    return (diesesJahr-geburtsJahr) >= 10;
}
void Islandpferd::zeigInfo() {
    //TODO
}
QPointF Islandpferd::getRefPunkt() {
    return firstPunkt;
}
void Islandpferd::movePony(double ratioX, double ratioY){
    firstPunkt.rx() = ratioX * firstPunkt.x();
    firstPunkt.ry() = ratioY * firstPunkt.y();
    lastPunkt.rx() = ratioX * lastPunkt.x();
    lastPunkt.ry() = ratioY * lastPunkt.y();
}

void Islandpferd::movePony(QPointF movePunkt) {
    QPointF tpr = movePunkt - firstPunkt;
    firstPunkt += tpr;
    lastPunkt += tpr;
}


//mallt Circle
void Islandpferd::mallen(QPainter* objkt){

    rad = std::hypot(firstPunkt.x() - lastPunkt.x(), firstPunkt.y() - lastPunkt.y());
    objkt->setPen(QPen(color, 2, Qt::SolidLine));

    objkt->setBrush(color);

    double x = firstPunkt.x() - rad;
    double y = firstPunkt.y() - rad;
    double diameter = rad * 2;

    objkt->drawEllipse(QRectF(x, y, diameter, diameter));
}
bool Islandpferd::isNear(QPointF p){

    double distance = std::hypot(firstPunkt.x() - p.x(), firstPunkt.y() - p.y());
    return distance <= rad;
}
