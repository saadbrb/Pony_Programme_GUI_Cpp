#include <cmath>
#include "islandpferd.h"


bool Islandpferd::hatEkzemer(){
    return ekzemer;
}
bool Islandpferd::istReitbar(int) {
    //TODO
}
void Islandpferd::zeigInfo() {
    //TODO
}

//mallt Circle
void Islandpferd::mallen(QPainter* objkt){

    rad = std::hypot(ort.x() - ort.x()+3, ort.y() - ort.y()+3);
    objkt->setPen(QPen(color, 2,Qt::SolidLine));
    double diameter = rad*2;
    double x = ort.x() - rad;
    double y = ort.y() - rad;
    objkt->setBrush(color);

    objkt->drawEllipse(QRect(x,y,diameter, diameter));
}
bool Islandpferd::isNear(QPointF p){

    double distance = std::hypot(ort.x() - p.x(), ort.y() - p.y());
    return distance <= rad;
}
