#include <qdebug.h>
#include "stall.h"

Stall::Stall()
{

}
int Stall::belegteBoxen(){
    return pferdeboxen.size();
}
bool Stall::einstellen(Pony* pony){
    pferdeboxen.push_back(pony);
    qDebug()<<"Pony added secussful ";
    qDebug()<<pferdeboxen.size()<<"\n";
}
Pony* Stall::herausholen(std::string){
    //TODO
}

void Stall::pferdeBoxenMallen(QPainter* event){
    for(int i=0; i<pferdeboxen.size(); i++){
        pferdeboxen[i]->mallen(event);
    }
}

float Stall::durchschnitalter(){
    int alter = 0;
    for(int i=0; i<pferdeboxen.size(); i++){
        alter = 2023 - pferdeboxen[i]->getGeburtsjahr();
    }

    return alter/pferdeboxen.size();
}
void Stall::weidegang(){
    //TODO
}
void Stall::zeigInfo(){
    //TODO
}
void Stall::clear(){

    pferdeboxen.clear();
}

QVector<Pony*> Stall::getPonys(){
    return pferdeboxen;
}

