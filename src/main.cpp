#include "admission_umts.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	admission_umts w;
	w.show();
	return a.exec();
}
