#include <QMouseEvent>
#include <QPainterPath>
#include <random>
#include <string>
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

}

void Canvas::addPonyToWeide(){
    ponyhof.addPonyToWeideBox();
    for(int i=0; i<ponyhof.getWeideBox().size(); i++){
        QPointF ort_;
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
        ort_.rx() = x;
        ort_.ry() = y;
        ponyhof.getWeideBox()[i]->setPos(ort_);

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
        gridLinesCreate();
    }
    if(mode == INFO && dragging){
        pony = ponyhof.getInfo(firstPunkt);
        if(pony != nullptr){
            nameInfo->setText(QString::fromStdString(pony->getName()));
            geburtsJahrInfo->setText(QString::number(pony->getGeburtsjahr()));
            if(pony->getType() == "island"){
                typeInfo->setText(QString("Hat Ekzem: "));
                if(dynamic_cast<class Islandpferd*>(pony)->hatEkzemer()){
                    boolFrage->setText(QString(" Yes "));
                }
                else if (!(dynamic_cast<class Islandpferd*>(pony)->hatEkzemer())) {
                    boolFrage->setText(QString(" No "));
                }

            }
            else if(pony->getType()== "shetland"){
                typeInfo->setText(QString("Ist Kinderlieb: "));
                if(dynamic_cast<class Shetlandpony*>(pony)->istKinderlieb()){
                    boolFrage->setText(QString(" Yes "));
                }
                else if (!(dynamic_cast<class Shetlandpony*>(pony)->istKinderlieb())) {
                    boolFrage->setText(QString(" No "));
                }
            }

        }
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
    if((event->button() & Qt::LeftButton) && dragging){
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
            QPointF ort;
            std::random_device rd; // Initialisiert einen Zufallsgenerator
            std::mt19937 gen(rd()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
            std::uniform_int_distribution<> dis(0, ((cellSizeX*60) / 100)-3); // Uniforme Verteilung zwischen 50 und 100

            double x = dis(gen);
            std::random_device rd_; // Initialisiert einen Zufallsgenerator
            std::mt19937 gen_(rd_()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
            std::uniform_int_distribution<> dis_(cellSizeY, (this->height()-3)); // Uniforme Verteilung zwischen 50 und 100
            double y = dis_(gen_);
            ort.rx() = x;
            ort.ry() = y;

            std::random_device ya; //Zufallszahlengenerator
            std::mt19937 qa(ya()); //Mersenne Twister 19937 Generator, mit rd als Seed
            std::uniform_int_distribution<> distra(1950, 2023); //Uniforme Verteilung

            int randomYear = distra(qa); //Erzeugen Sie eine Zufallszahl zwischen 1950 und 2023
            std::string name = "ShetlandPony" + std::to_string(ponyCounter);
            ponyCounter++;
            bool kinderLieb = std::rand() % 2;

            ponyhof.addPonyToStall(new class Shetlandpony(randomYear,name, ort,Qt::red, kinderLieb));
        }
    }
    else if (ponyArt == Islandpferd) {
        for(int i=0; i<ponyAnzahl; i++){
            cellSizeX = this->width() / GRID_COLS;
            cellSizeY = this->height() / GRID_ROWS;
            QPointF ort;
            std::random_device rd; // Initialisiert einen Zufallsgenerator
            std::mt19937 gen(rd()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
            std::uniform_int_distribution<> dis(0, ((cellSizeX*60) / 100)-3); // Uniforme Verteilung zwischen 50 und 100

            double x = dis(gen);
            std::random_device rd_; // Initialisiert einen Zufallsgenerator
            std::mt19937 gen_(rd_()); // Mersenne-Twister-Generator, der auf rd initialisiert ist
            std::uniform_int_distribution<> dis_(cellSizeY, (this->height()-3)); // Uniforme Verteilung zwischen 50 und 100
            double y = dis_(gen_);
            ort.rx() = x;
            ort.ry() = y;
            std::random_device ya; //Zufallszahlengenerator
            std::mt19937 qa(ya()); //Mersenne Twister 19937 Generator, mit rd als Seed
            std::uniform_int_distribution<> distra(1950, 2023); //Uniforme Verteilung

            int randomYear = distra(qa); //Erzeugen Sie eine Zufallszahl zwischen 1950 und 2023
            std::string name = "IslandpferdPony" + std::to_string(ponyCounter);
            ponyCounter++;
            bool ekzemer = std::rand() % 2;

            ponyhof.addPonyToStall(new class Islandpferd(randomYear,name, ort,Qt::blue, ekzemer));
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
    QPointF firstPunkt;
    firstPunkt.rx() = 0;
    firstPunkt.ry() = cellSizeY;
    QPointF lastPunkt;
    lastPunkt.rx() = cellSizeX;
    lastPunkt.ry() = cellSizeY;
    gridLines.push_back(new Line(firstPunkt, lastPunkt));

    firstPunkt.rx() = cellSizeX;
    firstPunkt.ry() = 0;
    lastPunkt.rx() = cellSizeX;
    lastPunkt.ry() = this->height();
    gridLines.push_back(new Line(firstPunkt, lastPunkt));

    firstPunkt.rx() = (cellSizeX*60) / 100;
    firstPunkt.ry() = cellSizeY;
    lastPunkt.rx() = (cellSizeX*60) / 100;
    lastPunkt.ry() = this->height();
    gridLines.push_back(new Line(firstPunkt, lastPunkt));

}


void Canvas::gridLinesDelete(){
    for(int i=0; i<gridLines.size(); i++){
        delete   gridLines[i];
    }
    gridLines.clear();
}

void Canvas::gridLinesPainter(QPainter* painter){
    for(int i=0; i<gridLines.size(); i++){
        gridLines[i]->mallen(painter);
    }

}


