#include <qdebug.h>
#include "stall.h"

Stall::Stall()
{

}
int Stall::belegteBoxen(){
    return pferdeboxen.size();
}
bool Stall::einstellen(std::shared_ptr<Pony> pony){
    pferdeboxen.push_back(pony);
    qDebug()<<"Pony added secussful ";
    qDebug()<<pferdeboxen.size()<<"\n";
}
void Stall::zumReitenherausholen(QVector<std::shared_ptr<Pony>>& ponyBox){
    qDebug()<<"ich bin in stall und vorher war "<<pferdeboxen.size()<<"\n";
    for(int i=pferdeboxen.size()-1; i>=0; i--){
        if(pferdeboxen[i]->istReitbar(2023)){
            ponyBox.push_back(pferdeboxen[i]);
            pferdeboxen.remove(i);
        }
    }
    qDebug()<<"danach ist: "<<pferdeboxen.size()<<"\n";
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


QVector<std::shared_ptr<Pony>>& Stall::getPonys(){
    return pferdeboxen;
}

