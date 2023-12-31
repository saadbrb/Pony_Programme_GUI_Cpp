#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QFrame>
#include <QSize>
#include <QVector>
#include <QLineEdit>
#include <memory>

#include "line.h"
#include "pony.h"
#include "ponyhof.h"

#define GRID_ROWS 2
#define GRID_COLS 2
typedef QVector<std::shared_ptr<Pony>> Grid[GRID_ROWS][GRID_COLS];

class Canvas : public QFrame
{
    Q_OBJECT

public:
    enum PonyArt {NONE, Shetlandpony, Islandpferd};
    enum Mode { CREAT, REITEN, INFO};
    explicit Canvas(QWidget *parent = nullptr);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setPonyArt(int ponyArt);
    void clearPonyHofe();
    void setColor();
    void setMode(Mode mode, QLineEdit* lineEdit, QLineEdit *geburtsJahrInfo_, QLineEdit *boolFrage_, QLineEdit *typeInfo_);
    void gridLinesCreate();
    void addPonyToStall(int ponaAnzahl);
    void addPonyToWeide();
    void gridLinesDelete();
    void gridLinesPainter(QPainter* painter);
    void setPonyArtMode(int mode);
    int getWidth();
    int getheight();
    void allePonysZumReitenHollen();


protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    bool dragging;
    QPointF firstPunkt;
    QPointF lastPunkt;
    Grid grid;
    Ponyhof ponyhof;
    QVector < std::shared_ptr<Line>> gridLines;
    int cellSizeX, cellSizeY;
    int breite;
    int hoehe;
    PonyArt ponyArt;
    Mode mode;
    int ponyCounter = 1;
    std::shared_ptr<Pony> pony = nullptr;
    QLineEdit* nameInfo;
    QLineEdit* geburtsJahrInfo;
    QLineEdit* boolFrage;
    QLineEdit* typeInfo;
    std::shared_ptr<Pony> ponya = nullptr;




};

#endif // CANVAS_H
