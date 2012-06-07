#pragma once

#include <QtGui>
#include <vector>

#include "ui_admission_umts.h"
#include "BaseStation.h"

class Launcher : public QWidget
{
	Q_OBJECT

	friend class CallRequestThread;
	friend class RoutineThread;

public:
	Launcher(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Launcher();
	void generateFlow(void);

public slots:
	void launchSimulation(void);
	static void wait_until_next_second(void);

private:
	Ui::admission_umtsClass ui;
	BaseStation *_baseStation;
	QGraphicsPathItem *_curve;
	QPainterPath graphPath;
	QPolygonF _polygon;

private slots:
	void callRequest(void);
	void routine(void);
	void updateGraphPath(void);
	void updateResultLabels(User *user, bool accepted);
};
