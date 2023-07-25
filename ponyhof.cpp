#include <qdebug.h>
#include "ponyhof.h"

Ponyhof::Ponyhof()
{

}

void Ponyhof::addPonyToStall(std::shared_ptr<Pony> pony){
    stall.einstellen(pony);
}
void Ponyhof::addPonyToReitenBox(){
    qDebug()<<"ich bin hier in ponyhofe und vorher war : size"<<beimReiten.size()<<"\n";
    stall.zumReitenherausholen(beimReiten);
    qDebug()<<"weide war vorher :"<<weide.size()<<"\n";
    for(int i=0; i<weide.size(); i++){
        if(weide[i]->istReitbar(2023)){
            beimReiten.push_back(beimReiten[i]);
            weide.removeOne(weide[i]);
        }
    }
    qDebug()<<"danach "<<weide.size()<<"\n";
    qDebug()<<"Danach "<<beimReiten.size();

}


std::shared_ptr<Pony>  Ponyhof::getPony(QPointF punkt){
    for (int i=0; i<stall.getPonys().size(); i++){
        if(stall.getPonys()[i]->isNear(punkt) && stall.getPonys()[i]->istReitbar(2023)){
            ponyOrtBox = "stall";
            return stall.getPonys()[i];
        }
    }
    for(std::shared_ptr<Pony> pony : beimReiten){
        if(pony->isNear(punkt) && pony->istReitbar(2023)){
            ponyOrtBox = "reiten";
            return pony;
        }
    }
    for(std::shared_ptr<Pony> pony : weide){
        if(pony->isNear(punkt) && pony->istReitbar(2023)){
            ponyOrtBox = "weide";
            return pony;
        }
    }
    return nullptr;
}


void Ponyhof::setPonyPositionInBox(std::string ponyOrtBox_,std::shared_ptr<Pony> ponyPtr){
    //    std::cout<<"es war in stall"<<stall.getPonys().size();
    //    std::cout<<"\n es war in reiten"<<beimReiten.size();
    //    std::cout<<"\n es war in weide "<<weide.size()<<"\n";
    if(ponyOrtBox == ponyOrtBox_){
        std::cout<<"nichts zu andern!\n";

        return;
    }
    if(ponyOrtBox == "stall"){

        if(ponyOrtBox_ == "reiten"){
            beimReiten.push_back(ponyPtr);
        }
        else if(ponyOrtBox_ == "weide"){
            weide.push_back(ponyPtr);
        }
        stall.getPonys().removeOne(ponyPtr);
        ponyOrtBox = "n";


    }
    else if (ponyOrtBox == "reiten") {
        if(ponyOrtBox_ == "stall"){
            stall.getPonys().push_back(ponyPtr);
        }
        else if(ponyOrtBox_ == "weide"){
            weide.push_back(ponyPtr);
        }
        beimReiten.removeOne(ponyPtr);

        ponyOrtBox = "n";


    }
    else if (ponyOrtBox == "weide") {

        if(ponyOrtBox_ == "stall"){
            stall.getPonys().push_back(ponyPtr);
        }
        else if(ponyOrtBox_ == "reiten"){
            beimReiten.push_back(ponyPtr);
        }
        weide.removeOne(ponyPtr);
        ponyOrtBox = "n";

    }

}

void Ponyhof::setAllPositionInStall(double ratioX, double ratioY){
    auto& ponys = stall.getPonys();
    for (auto& pony : ponys){
        pony->movePony(ratioX, ratioY);
    }
}
void Ponyhof::setAllPositionInWeide(double ratioX, double ratioY){
    for(auto& pony : weide){
        pony->movePony(ratioX, ratioY);
    }
}
void Ponyhof::setAllPositionInReiten(double ratioX, double ratioY){
    for(auto& pony : beimReiten){
        pony->movePony(ratioX, ratioY);
    }
}
QVector<std::shared_ptr<Pony>>& Ponyhof::getReitenBox(){
    return beimReiten;
}


QVector<std::shared_ptr<Pony> > &Ponyhof::getWeideBox(){
    return weide;
}

std::shared_ptr<Pony> Ponyhof::getInfo(QPointF punkt){
    for (int i=0; i<stall.getPonys().size(); i++){
        if(stall.getPonys()[i]->isNear(punkt)){
            qDebug()<<"gefunden";
            return stall.getPonys()[i];
        }
    }
    for(std::shared_ptr<Pony> pony : beimReiten){
        if(pony->isNear(punkt)){
            qDebug()<<"gefunden";

            return pony;
        }
    }
    for(std::shared_ptr<Pony> pony : weide){
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
    for(std::shared_ptr<Pony> pony : beimReiten){
        pony->mallen(event);
    }
    for(std::shared_ptr<Pony> pony : weide){
        pony->mallen(event);
    }
}
