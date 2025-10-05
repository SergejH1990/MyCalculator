#include "taschenrechnerw.h"

#include <QApplication>
#include <QtMath>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// Load style sheat from file
	QFile File(":/stylesheet.qss");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	app.setStyleSheet(StyleSheet);

	TaschenrechnerW MyCalculator;
	MyCalculator.show();
	return app.exec();
}
