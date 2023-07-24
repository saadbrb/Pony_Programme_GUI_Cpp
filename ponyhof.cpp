#include <qdebug.h>
#include "ponyhof.h"

Ponyhof::Ponyhof()
{

}

void Ponyhof::addPonyToStall(Pony* pony){
    stall.einstellen(pony);
}
void Ponyhof::addPonyToReitenBox(Pony* pony){
    beimReiten.push_back(pony);
}

QVector<Pony*>& Ponyhof::getWeideBox(){
    return weide;
}

Pony* Ponyhof::getInfo(QPointF punkt){
    for (int i=0; i<stall.getPonys().size(); i++){
        if(stall.getPonys()[i]->isNear(punkt)){
            qDebug()<<"gefunden";
            return stall.getPonys()[i];
        }
    }
    for(Pony* pony : beimReiten){
        if(pony->isNear(punkt)){
            qDebug()<<"gefunden";

            return pony;
        }
    }
    for(Pony* pony : weide){
        if(pony->isNear(punkt)){
            qDebug()<<"gefunden";

            return pony;
        }
    }
    return nullptr;
}

void Ponyhof::addPonyToWeideBox(){
    qDebug()<<"Size ist "<<weide.size();
    for (int i=0; i<stall.getPonys().size(); i++){
        weide.push_back(stall.getPonys()[i]);
    }
    qDebug()<<"Size ist "<<weide.size();
    stall.clear();
}

void Ponyhof::stallClear(){

    stall.clear();
}


void Ponyhof::allePonysMallen(QPainter*event){
    stall.pferdeBoxenMallen(event);
    for(Pony* pony : beimReiten){
        pony->mallen(event);
    }
    for(Pony* pony : weide){
        pony->mallen(event);
    }
}
