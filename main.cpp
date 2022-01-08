#include "taschenrechnerw.h"

#include <QApplication>
#include <QtMath>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaschenrechnerW w;
    w.show();
    return a.exec();
}
