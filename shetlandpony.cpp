#include <cmath>
#include <qdebug.h>
#include "shetlandpony.h"

bool Shetlandpony::istKinderlieb(){
    return kinderlieb;
}
bool Shetlandpony::istReitbar(int jahr){
    int alter = jahr-geburtsJahr;
    if(alter>=5 && alter<=12)
        return true;
    if(alter<=8 && kinderlieb)
        return true;
    return false;
}


void Shetlandpony::movePony(QPointF movePunkt) {
    QPointF tpr = movePunkt - firstPunkt;
    firstPunkt += tpr;
    lastPunkt += tpr;

}
void Shetlandpony::movePony(double ratioX, double ratioY){
    firstPunkt.rx() = ratioX * firstPunkt.x();
    firstPunkt.ry() = ratioY * firstPunkt.y();
    lastPunkt.rx() = ratioX * lastPunkt.x();
    lastPunkt.ry() = ratioY * lastPunkt.y();

}
void Shetlandpony::zeigInfo() {
    //TODO
}
//Rectangle mallen
void Shetlandpony::mallen(QPainter* objkt){
    qreal x = firstPunkt.x();
    qreal y = firstPunkt.y();
    qreal with = lastPunkt.x() - x;
    qreal height =lastPunkt.y() - y;

    objkt->setPen(QPen(color,2,Qt::SolidLine));
    objkt->setBrush(color);
    objkt->drawRect(QRectF(x,y,with,height));

}
bool Shetlandpony::isNear(QPointF p){
    qreal minX = minF(firstPunkt.x(), firstPunkt.x()+6 );
    qreal minY = minF(firstPunkt.y(), firstPunkt.y()+6 );
    qreal maxX = maxF(firstPunkt.x(), firstPunkt.x()+6);
    qreal maxY = maxF(firstPunkt.y(), firstPunkt.y()+6);
    if ((minX <= p.x() && p.x()<= maxX) && (minY <= p.y() && p.y()<=maxY))
        qDebug()<<"is clicked";
    return (minX <= p.x() && p.x()<= maxX) && (minY <= p.y() && p.y()<=maxY);
}
QPointF Shetlandpony::getRefPunkt() {
    QPointF p;
    p.rx() = firstPunkt.x() + lastPunkt.x();
    p.ry() = lastPunkt.y() + firstPunkt.y();
    p /= 2;
    return p;
}
