#include <QMouseEvent>
#include <QPainterPath>
#include <random>
#include <string>
#include <memory>
#include <QPainter>
#include <QDebug>
#include <vector>
#include <math.h>
#include <cmath>
#include <QPointF>
#include <QVector>
#include "shetlandpony.h"
#include "islandpferd.h"
#include "QPainter"
#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QFrame(parent)
{
    dragging = false;

    cellSizeX = this->width() / GRID_COLS;

    cellSizeY = this->height() / GRID_ROWS;
     breite = this->width();
     hoehe = this->height();
}

void Canvas::addPonyToWeide(){
    ponyhof.addPonyToWeideBox();
    for(int i=0; i<ponyhof.getWeideBox().size(); i++){
        QPointF firstPunkt_;
        cellSizeX = this->width() / GRID_COLS;

        cellSizeY = this->height() / GRID_ROWS;
        std::random_device rd; // Initialisiert einen Zufallsgenerator
        std::mt19937 gen(rd()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
        std::uniform_int_distribution<> dis(cellSizeX, ( this->width()-3)); // Uniforme Verteilung zwischen 50 und 100

        double x = dis(gen);
        std::random_device rd_; // Initialisiert einen Zufallsgenerator
        std::mt19937 gen_(rd_()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
        std::uniform_int_distribution<> dis_(0, (this->height()-3)); // Uniforme Verteilung zwischen 50 und 100
        double y = dis_(gen_);
        firstPunkt_.rx() = x;
        firstPunkt_.ry() = y;
        ponyhof.getWeideBox()[i]->setPos(firstPunkt_);

    }
}
void Canvas::allePonysZumReitenHollen(){

    ponyhof.addPonyToReitenBox();
    for(int i=0; i<ponyhof.getReitenBox().size(); i++){
        QPointF firstPunkt_;
        cellSizeX = this->width() / GRID_COLS;

        cellSizeY = this->height() / GRID_ROWS;
        std::random_device rd; // Initialisiert einen Zufallsgenerator
        std::mt19937 gen(rd()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
        std::uniform_int_distribution<> dis(0, cellSizeX-3); // Uniforme Verteilung zwischen 50 und 100

        double x = dis(gen);
        std::random_device rd_; // Initialisiert einen Zufallsgenerator
        std::mt19937 gen_(rd_()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
        std::uniform_int_distribution<> dis_(0, (cellSizeY-3)); // Uniforme Verteilung zwischen 50 und 100
        double y = dis_(gen_);
        firstPunkt_.rx() = x;
        firstPunkt_.ry() = y;
        ponyhof.getReitenBox()[i]->setPos(firstPunkt_);
    }
}


QSize Canvas::minimumSizeHint() const {
    return QSize(200,200);
}
QSize Canvas::sizeHint() const {
    return QSize(640,480);
}
void Canvas::paintEvent(QPaintEvent* event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.fillRect(QRectF(0,0, this->width()-1, this->height()-1), Qt::white);
    painter.drawRect(QRectF(0,0,this->width()-1, this->height()-1));
    if(breite != this->width() || hoehe != this->height()){
        std::cout<<"breite :"<<breite<<" hoehe: "<<hoehe<<"\n";
        std::cout<<"this->width() :"<<this->width()<<" this->height(): "<<this->height()<<"\n";

        gridLinesCreate();

        double ratioX, ratioY;
        ratioX = ((double)this->width()) / breite;
        ratioY = ((double)this->height()) / hoehe;
        ponyhof.setAllPositionInReiten(ratioX, ratioY);
        ponyhof.setAllPositionInStall(ratioX, ratioY);
        ponyhof.setAllPositionInWeide(ratioX, ratioY);
        breite = this->width();
        hoehe = this->height();
    }
    if(mode == INFO && dragging){
        pony = ponyhof.getInfo(firstPunkt);
        if(pony != nullptr){
            nameInfo->setText(QString::fromStdString(pony->getName()));
            geburtsJahrInfo->setText(QString::number(pony->getGeburtsjahr()));
            if(pony->getType() == "island"){
                typeInfo->setText(QString("Hat Ekzem: "));
                //std::dynamic_pointer_cast<Polygone>(graphObjkt)->isNear(lastPunkt)
                //std::shared_ptr<class Islandpferd> islandpferd = std::dynamic_pointer_cast<class Islandpferd>(pony);
                //if(pony != nullptr) {
                //std::shared_ptr<Islandpferd> islandpferd = std::dynamic_pointer_cast<Islandpferd>(pony);
                //if(islandpferd != nullptr && islandpferd->hatEkzemer()) {}}

                if(std::dynamic_pointer_cast<class Islandpferd>(pony)->hatEkzemer()){
                    std::string a = "w";
                    boolFrage->setText(QString(a));
                }
                else if (!(std::dynamic_pointer_cast<class Islandpferd>(pony)->hatEkzemer())) {
                    boolFrage->setText(QString(" No "));
                }

            }
            else if(pony->getType()== "shetland"){
                typeInfo->setText(QString("Ist Kinderlieb: "));
                //if(dynamic_cast<class Shetlandpony*>(pony)->istKinderlieb()){


                if (std::dynamic_pointer_cast<class Shetlandpony>(pony)->istKinderlieb()){
                    boolFrage->setText(QString(" Yes "));
                }
                else if (!std::dynamic_pointer_cast<class Shetlandpony>(pony)->istKinderlieb()) {
                    boolFrage->setText(QString(" No "));
                }
            }

        }
    }
    else if(mode == REITEN && dragging){

        if(firstPunkt == lastPunkt){
            ponya = ponyhof.getPony(firstPunkt);
        }
        if(ponya == nullptr){

            qDebug()<<"is a nullptr";
            return;
        }
        if(ponya != nullptr){
            qDebug()<<"type ";
            ponya->movePony(lastPunkt);
            ponyhof.allePonysMallen(&painter);
        }

    }
    else if(!dragging){
        //p is referencePoint
        if(ponya != nullptr){
            QPointF p = ponya->getRefPunkt();
            cellSizeX = this->width() / GRID_COLS;
            cellSizeY = this->height() / GRID_ROWS;
            if((p.x()>= 0 && p.x()<cellSizeX) && (p.y()>=0 && p.y()<cellSizeY)){
                //"stall"; "reiten";"weide";
                // bin reiten
                ponyhof.setPonyPositionInBox("reiten",ponya);
            }

            else if ((p.x()>= 0 && p.x()<(cellSizeX*60) / 100) && (p.y()>=cellSizeY && p.y()<this->height()-1)) {
                //ich bin am stall
                ponyhof.setPonyPositionInBox("stall",ponya);
            }
            else if ((p.x()>= cellSizeX && p.x()<(this->width()-1) && (p.y()>=0 && p.y()<this->height()))) {
                //ich bin am weide
                ponyhof.setPonyPositionInBox("weide",ponya);
            }
            else if ((p.x()>= (cellSizeX*60) / 100) && p.x()<(cellSizeX) && (p.y()>=cellSizeY && p.y()<this->height()-1)) {
                //ich bin am leer
                QPointF punkt;
                std::random_device rd; // Initialisiert einen Zufallsgenerator
                std::mt19937 gen(rd()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
                std::uniform_int_distribution<> dis(0, cellSizeX-3); // Uniforme Verteilung zwischen 50 und 100

                double x = dis(gen);
                std::random_device rd_; // Initialisiert einen Zufallsgenerator
                std::mt19937 gen_(rd_()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
                std::uniform_int_distribution<> dis_(cellSizeY, this->height()-2); // Uniforme Verteilung zwischen 50 und 100
                double y = dis_(gen_);
                punkt.rx() = x;
                punkt.ry() = y;
                ponya->movePony(punkt);
            }
        }
        ponya == nullptr;

    }
    gridLinesPainter(&painter);
    ponyhof.allePonysMallen(&painter);
    update();


}
void Canvas::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        dragging = true;
        firstPunkt = event->pos();
        lastPunkt = firstPunkt;
        update();
    }
}
void Canvas::mouseMoveEvent(QMouseEvent* event){
    if((event->buttons() & Qt::LeftButton) && dragging){
        lastPunkt = event->pos();
        update();
    }
}
void Canvas::mouseReleaseEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton && dragging){
        dragging = false;
        lastPunkt = event->pos();
        update();
    }
}

int Canvas::getWidth(){
    update();
    return this->width();
}
int Canvas::getheight(){
    update();
    return this->height();
}

void Canvas::addPonyToStall(int ponyAnzahl){
    if(ponyArt == NONE || mode != CREAT){
        return;
    }
    if(ponyArt == Shetlandpony){
        for(int i=0; i<ponyAnzahl; i++){
            cellSizeX = getWidth() / GRID_COLS;
            cellSizeY = getheight() / GRID_ROWS;
            QPointF firstPunkt_;
            std::random_device rd; // Initialisiert einen Zufallsgenerator
            std::mt19937 gen(rd()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
            std::uniform_int_distribution<> dis(0, ((cellSizeX*60) / 100)-3); // Uniforme Verteilung zwischen 50 und 100

            double x = dis(gen);
            std::random_device rd_; // Initialisiert einen Zufallsgenerator
            std::mt19937 gen_(rd_()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
            std::uniform_int_distribution<> dis_(cellSizeY, (this->height()-3)); // Uniforme Verteilung zwischen 50 und 100
            double y = dis_(gen_);
            firstPunkt_.rx() = x;
            firstPunkt_.ry() = y;

            std::random_device ya; //Zufallszahlengenerator
            std::mt19937 qa(ya()); //Mersenne Twister 19937 Generator, mit rd als Seed
            std::uniform_int_distribution<> distra(1950, 2023); //Uniforme Verteilung

            int randomYear = distra(qa); //Erzeugen Sie eine Zufallszahl zwischen 1950 und 2023
            std::string name = "ShetlandPony" + std::to_string(ponyCounter);
            ponyCounter++;
            bool kinderLieb = std::rand() % 2;

            ponyhof.addPonyToStall(std::make_shared<class Shetlandpony>(randomYear,name, firstPunkt_,Qt::red, kinderLieb));
        }
    }
    else if (ponyArt == Islandpferd) {
        for(int i=0; i<ponyAnzahl; i++){
            cellSizeX = this->width() / GRID_COLS;
            cellSizeY = this->height() / GRID_ROWS;
            QPointF firstPunkt_;
            std::random_device rd; // Initialisiert einen Zufallsgenerator
            std::mt19937 gen(rd()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
            std::uniform_int_distribution<> dis(0, ((cellSizeX*60) / 100)-3); // Uniforme Verteilung zwischen 50 und 100

            double x = dis(gen);
            std::random_device rd_; // Initialisiert einen Zufallsgenerator
            std::mt19937 gen_(rd_()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
            std::uniform_int_distribution<> dis_(cellSizeY, (this->height()-3)); // Uniforme Verteilung zwischen 50 und 100
            double y = dis_(gen_);
            firstPunkt_.rx() = x;
            firstPunkt_.ry() = y;
            std::random_device ya; //Zufallszahlengenerator
            std::mt19937 qa(ya()); //Mersenne Twister 19937 Generator, mit rd als Seed
            std::uniform_int_distribution<> distra(1950, 2023); //Uniforme Verteilung

            int randomYear = distra(qa); //Erzeugen Sie eine Zufallszahl zwischen 1950 und 2023
            std::string name = "IslandpferdPony" + std::to_string(ponyCounter);
            ponyCounter++;
            bool ekzemer = std::rand() % 2;

            ponyhof.addPonyToStall(std::make_shared< class Islandpferd>(randomYear,name, firstPunkt_,Qt::blue, ekzemer));
        }}
    update();
}
void Canvas::setMode(Mode mode, QLineEdit* nameInfo_, QLineEdit* geburtsJahrInfo_, QLineEdit* boolFrage_, QLineEdit* typeInfo_){
    this->mode = mode;

    //        lineEdit.setText(QString::fromStdString(pony->getName()));
    //        lineEdit_.setText(QString::number(pony->getGeburtsjahr()));
    nameInfo = nameInfo_;
    geburtsJahrInfo = geburtsJahrInfo_;
    boolFrage = boolFrage_;
    typeInfo = typeInfo_;
    update();
}

void Canvas::setPonyArtMode(int mode){
    ponyArt = (Canvas::PonyArt) mode;
    update();
}



void Canvas::gridLinesCreate(){
    gridLinesDelete();
    cellSizeX = this->width() / GRID_COLS;

    cellSizeY = this->height() / GRID_ROWS;
    QPointF firstPunkt_;
    firstPunkt_.rx() = 0;
    firstPunkt_.ry() = cellSizeY;
    QPointF lastPunkt_;
    lastPunkt_.rx() = cellSizeX;
    lastPunkt_.ry() = cellSizeY;
    gridLines.push_back(std::make_shared<class Line>(firstPunkt_, lastPunkt_));

    firstPunkt_.rx() = cellSizeX;
    firstPunkt_.ry() = 0;
    lastPunkt_.rx() = cellSizeX;
    lastPunkt_.ry() = this->height();
    gridLines.push_back(std::make_shared< Line>(firstPunkt_, lastPunkt_));

    firstPunkt_.rx() = (cellSizeX*60) / 100;
    firstPunkt_.ry() = cellSizeY;
    lastPunkt_.rx() = (cellSizeX*60) / 100;
    lastPunkt_.ry() = this->height();
    gridLines.push_back(std::make_shared< Line>(firstPunkt_, lastPunkt_));

}


void Canvas::gridLinesDelete(){
    //    for(int i=0; i<gridLines.size(); i++){
    //        delete   gridLines[i];
    //    }
    if(gridLines.size()>0){
        gridLines.clear();
    }
}

void Canvas::gridLinesPainter(QPainter* painter){
    for(int i=0; i<gridLines.size(); i++){
        gridLines[i]->mallen(painter);
    }

}


