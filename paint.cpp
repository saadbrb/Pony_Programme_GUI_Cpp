#include <QColorDialog>
#include <QGridLayout>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QPainter>
#include <QDateTime>
#include "paint.h"
#include "canvas.h"
#include "ui_paint.h"

Paint::Paint(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Paint)
{
    ui->setupUi(this);

    canvas = new Canvas();
    // Erstellen von Menubar

    QAction *quit = new QAction("&Quit");
    QAction *save = new QAction("Save &Image");
    QMenu *fileMenu = new QMenu("File");
    QMenuBar *menuBar = new QMenuBar();

    fileMenu->addAction(quit);
    fileMenu->addAction(save);
    menuBar->addMenu(fileMenu);
    ui->verticalLayout__->setMenuBar(menuBar);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(save, &QAction::triggered, this, &Paint::saveImage);

    //Erstellen vom Frame

    ui->verticalLayout__->replaceWidget(ui->frame, canvas);
    delete ui->frame;
    ui->frame = canvas;
    ui->comboBox->addItem(tr("NoMode"), Canvas::NONE);
    ui->comboBox->addItem(tr("Shetlandpony"), Canvas::Shetlandpony);
    ui->comboBox->addItem(tr("Islandpferd"), Canvas::Islandpferd);

    //    ui->comboBox->addItem(tr("Freehand"), Canvas::FREE_HAND);
    //    ui->comboBox->addItem(tr("Circle"), Canvas::CIRCLE);
    //    ui->comboBox->addItem(tr("Rectangle"), Canvas::RECTANGLE);
    //    ui->comboBox->addItem(tr("Polygon"), Canvas::POLYGON);
    //    ui->comboBox->addItem(tr("Triangle"), Canvas::TRIANGLE);
    // canvas->setMode(Canvas::COL);

}

void Paint::saveImage() {
    // Größe des ViewpfirstPunkts ermitteln
    QSize viewpfirstPunktSize = canvas->size();

    // QImage-Objekt erstellen
    QImage image(viewpfirstPunktSize, QImage::Format_RGB32);

    // QPainter-Objekt erstellen, um auf das QImage-Objekt zu zeichnen
    QPainter painter(&image);

    // Den Inhalt des ViewpfirstPunkts in das QImage-Objekt zeichnen
    canvas->render(&painter);

    // Automatisch speichern des Bildes
    QString directory = "/home/saad/Bilder/"; // Hier den gewünschten Pfad einsetzen
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString fileName = directory + "image_" + timestamp + ".png";
    image.save(fileName);

}

Paint::~Paint()
{
    delete ui;
}


int Paint::checkInt(QString number_to_check){
    bool isInt = false;

    // Konvertiere den QString in einen int
    bool ok;
    int intValue = number_to_check.toInt(&ok);

    // Überprüfe, ob die Konvertierung erfolgreich war und der QString eine Ganzzahl ist
    if (ok)
    {
        // Der QString ist eine Ganzzahl
        isInt = true;
        return intValue;
    }
    else
    {
        // Der QString ist keine Ganzzahl
        isInt = false;
        return -1;
    }


}


//class A {
//public:
//    A(){};
//    A(const A&);
//    virtual ~A() = default;
//public:
//  virtual void print() = 0;
//};

//class B : public A  {
//public:
//    string name;
//    B(string name_):name(name_){};
//    void print() override {
//        std::cout << name << std::endl;
//    }
//};

//class S {
//    public:
//    std::vector<std::shared_ptr<A>> T;
//};

//int main()
//{
//    S s;
//    std::shared_ptr<A> a = nullptr;
//    if (!a) {
//        std::cout << "a is nullptr" << endl;
//    }
//    a = make_shared<B>("B0");
//    a->print();
//    s.T.push_back(std::make_shared<B>("B1"));
//    std::unique_ptr<A> b = std::make_unique<B>("B2");
//    // s.T.front()->print();

//    return 0;
//}



void Paint::on_pushButton_2_clicked()
{
    connect(ui->pushButton_2, &QPushButton::clicked, qApp, &QApplication::quit);


}


void Paint::on_comboBox_activated(int mode)
{
    mode = ui->comboBox->itemData(
                ui->comboBox->currentIndex(), Qt::UserRole).toInt();
    canvas->setPonyArtMode(mode);
    qDebug()<<"PonyArtMode Changed to "<<mode;
}


void Paint::on_generator_button_clicked()
{
    int zahl = checkInt(ui->get_number_of_objekt->text());
    if(zahl > 0){
        qDebug()<<zahl;
        canvas->addPonyToStall(zahl);

    }
    else{

        ui->get_number_of_objekt->setText(QString ("Invalide Inpute"));
    }

}


void Paint::on_PonyEinstellen_clicked()
{

    qDebug()<<"Mode Changed to Einstellen";
    canvas->setMode(Canvas::CREAT,ui->name,ui->geburtsJahr, ui->boolFrag, ui->bool_frage_text);
}


void Paint::on_ponyInfo_clicked()
{
    qDebug()<<"Mode Changed to Info";
    canvas->setMode(Canvas::INFO, ui->name,ui->geburtsJahr, ui->boolFrag, ui->bool_frage_text);
}


void Paint::on_PonyReitenHolen_clicked()
{
    qDebug()<<"Mode Changed to Reitenholen";
    canvas->setMode(Canvas::REITEN, ui->name,ui->geburtsJahr, ui->boolFrag, ui->bool_frage_text);
}


void Paint::on_weide_clicked()
{

    canvas->addPonyToWeide();
}


void Paint::on_reitenHollen_clicked()
{
    canvas->allePonysZumReitenHollen();
}

