#ifndef LINE_H
#define LINE_H
#include <QPointF>
#include <QPainter>
class Line
{
private:
    QPointF firstPunkt, lastPunkt;

public:
    Line(QPointF firstPunkt_,QPointF lastPunkt_): firstPunkt(firstPunkt_), lastPunkt(lastPunkt_){}
    void mallen(QPainter* painter);

};

#endif // LINE_H
