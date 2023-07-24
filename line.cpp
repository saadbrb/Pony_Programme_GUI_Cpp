#include "line.h"



void Line::mallen(QPainter* painter){

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));

    painter->drawLine(firstPunkt, lastPunkt);
}
