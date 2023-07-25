#ifndef ISLANDPFERD_H
#define ISLANDPFERD_H

#include "pony.h"

class Islandpferd : public Pony
{
private:
    bool ekzemer;
    double rad;
public:
    Islandpferd(int geburtsJahr_, std::string name_, QPointF firstPunkt_, QColor color_, bool ekzemer_):
        Pony(geburtsJahr_, name_, firstPunkt_, color_), ekzemer(ekzemer_){
        type = "island";
    }
    bool hatEkzemer();
    bool istReitbar(int) override;
    void zeigInfo() override;
    void mallen(QPainter* objkt) override;
    bool isNear(QPointF p) override;
    void movePony(QPointF) override ;
    QPointF getRefPunkt() override;



};

#endif // ISLANDPFERD_H
