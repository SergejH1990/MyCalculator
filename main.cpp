#include "taschenrechnerw.h"

#include <QApplication>
#include <QtMath>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaschenrechnerW MyCalculator;
    MyCalculator.show();
    return a.exec();
}
