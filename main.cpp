#include "taschenrechnerw.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// Load style sheet from file
	{
		QFile File(":/stylesheet.qss");
		File.open(QFile::ReadOnly);
		const QString StyleSheet = QLatin1String(File.readAll());
		app.setStyleSheet(StyleSheet);
	}

	TaschenrechnerW MyCalculator;
	MyCalculator.show();
	return app.exec();
}
