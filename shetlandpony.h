#ifndef SHETLANDPONY_H
#define SHETLANDPONY_H

#include "pony.h"

class Shetlandpony : public Pony
{
private:
    bool kinderlieb;
public:
    Shetlandpony(int geburtsJahr_, std::string name_, QPointF ort_,QColor color_, bool kinderlieb_):
        Pony(geburtsJahr_, name_, ort_, color_), kinderlieb(kinderlieb_){
        type = "shetland";
    }
    bool istKinderlieb();
    bool istReitbar(int) override;
    void zeigInfo() override;
    void mallen(QPainter* objkt) override;
    bool isNear(QPointF p) override;

};

#endif // SHETLANDPONY_H
