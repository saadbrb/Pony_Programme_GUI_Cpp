#ifndef PAINT_H
#define PAINT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Paint; }
QT_END_NAMESPACE

class Canvas;

class Paint : public QWidget
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    void saveImage();
    int checkInt(QString number_to_check);
    ~Paint() override;

private slots:

    void on_pushButton_2_clicked();

    void on_comboBox_activated(int index);

    void on_generator_button_clicked();


    void on_PonyEinstellen_clicked();

    void on_ponyInfo_clicked();

    void on_PonyReitenHolen_clicked();

    void on_weide_clicked();

private:
    Ui::Paint *ui;
    Canvas* canvas;

};
#endif // PAINT_H
