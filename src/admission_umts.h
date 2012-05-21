#ifndef ADMISSION_UMTS_H
#define ADMISSION_UMTS_H

#include <QtGui/QWidget>
#include "ui_admission_umts.h"

class admission_umts : public QWidget
{
	Q_OBJECT

public:
	admission_umts(QWidget *parent = 0, Qt::WFlags flags = 0);
	~admission_umts();

private:
	Ui::admission_umtsClass ui;
};

#endif // ADMISSION_UMTS_H
