#include "QtPairProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtPairProject w;
	w.setWindowTitle("Painter");
	w.show();
	return a.exec();
}
