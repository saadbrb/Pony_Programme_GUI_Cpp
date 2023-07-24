#include <cmath>
#include <qdebug.h>
#include "shetlandpony.h"

bool Shetlandpony::istKinderlieb(){
    return kinderlieb;
}
bool Shetlandpony::istReitbar(int){
    //TODO
}
void Shetlandpony::zeigInfo() {
    //TODO
}
//Rectangle mallen
void Shetlandpony::mallen(QPainter* objkt){
    qreal x = ort.x();
    qreal y = ort.y();
    qreal with = ort.x()+6 - x;
    qreal height = ort.y()+6 -y;
    objkt->setBrush(color);
    objkt->setPen(QPen (color, 2, Qt::SolidLine));
    objkt->drawRect(QRectF(x,y,with, height));

}
bool Shetlandpony::isNear(QPointF p){
    qreal minX = minF(ort.x(), ort.x()+6 );
    qreal minY = minF(ort.y(), ort.y()+6 );
    qreal maxX = maxF(ort.x(), ort.x()+6);
    qreal maxY = maxF(ort.y(), ort.y()+6);
    if ((minX <= p.x() && p.x()<= maxX) && (minY <= p.y() && p.y()<=maxY))
            qDebug()<<"is clicked";
    return (minX <= p.x() && p.x()<= maxX) && (minY <= p.y() && p.y()<=maxY);
}
