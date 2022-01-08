#ifndef TASCHENRECHNERW_H
#define TASCHENRECHNERW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TaschenrechnerW; }
QT_END_NAMESPACE

class TaschenrechnerW : public QMainWindow
{
    Q_OBJECT

public:
    TaschenrechnerW(QWidget *parent = nullptr);

    ~TaschenrechnerW();

private:
    double LCDZahl;
    double ersteZahl;
    bool trackButton;
    int ergebnis;

private:
    Ui::TaschenrechnerW *ui;

private slots:
    void num_pressed();
    void ausgabeManipulation();
    void on_dezi_released();
    void operationen();
    void istGleich();

};
#endif // TASCHENRECHNERW_H
