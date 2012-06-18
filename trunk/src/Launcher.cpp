#include <time.h>
#include <math.h>

#include <QDebug>
#include <QString>

#include "Launcher.h"
#include "User.h"

using namespace std;

Launcher::Launcher(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	srand((unsigned) time(NULL));
	ui.setupUi(this);

	//Connecting slots
	QObject::connect(ui.launchSimulationButton, SIGNAL(clicked()), this, SLOT(launchSimulation()));
}

Launcher::~Launcher()
{
}

void Launcher::launchSimulation(void)
{
	qDebug() << "Launch Simulation button clicked";
	ui.resultLabel->setText(QString("Simulation in progress...\nPlease wait."));
	qDebug() << "Simulation in progress";

	nbRejected = 0;
	nbTotal = 0;
	_polygon = QPolygonF();
	_polygon << QPointF(0, 0);

	int initNbUsers = ui.initNbUsersTextBox->text().toInt();
	float baseStationHeight, mobileHeight, gain, frequency;
	if (ui.urbanRadioButton->isChecked())
	{
		baseStationHeight = ui.baseStationHeightTextBox->text().toFloat();
		mobileHeight = ui.mobileHeightTextBox->text().toFloat();
		gain = ui.gainTextBox->text().toFloat();
		frequency = ui.frequencyTextBox->text().toFloat();
	} else {
		baseStationHeight = ui.sub_BaseStationHeightTextBox->text().toFloat();
		mobileHeight = ui.sub_MobileHeightTextBox->text().toFloat();
		gain = ui.sub_GainTextBox->text().toFloat();
		frequency = ui.sub_FrequencyTextBox->text().toFloat();
	}

	//Initialiazing base station
	_baseStation = new BaseStation(ui.pilotPowerTextBox->text().toFloat(),
		ui.bandwidthpilotPowerTextBox->text().toFloat()* 1000000,
		ui.snrTargetTextBox->text().toFloat(),
		ui.bitRateTextBox->text().toFloat(),
		ui.noisePowerTextBox->text().toFloat(),
		ui.orthoFactorTextBox->text().toFloat(),
		ui.baseStationHeightTextBox->text().toFloat(),
		ui.gainTextBox->text().toFloat(),
		ui.frequencyTextBox->text().toFloat(),
		ui.thresholdPowerTextBox->text().toFloat(),
		ui.timePeriodTextBox->text().toInt());

	//Simulating existing users
	for (int i = 0; i < initNbUsers; i++)
	{
		User *user = new User(i, mobileHeight, ui.cellRadiusTextBox->text().toFloat(), _baseStation);
		_baseStation->addUser(user);
	}
	_baseStation->addUserList(_baseStation->getUsersList());
	_baseStation->computeTotalTransmittedPower();
	//_baseStation->computeDevotedPowerAllUsers();
	_baseStation->computeAverageTransmittedPower();
	
	//Randomly managing flow of user within the cell
	generateFlow();

	ui.resultLabel->setText(QString("Simulation completed"));
	qDebug() << "Simulation completed";
}

void Launcher::generateFlow(void)
{
	QTime time_;
	time_.start();
	int MAX_NB_FRAMES_PER_IT = 1000;
	while (time_.elapsed() < ui.durationTextBox->text().toInt() * 1000)
	{	
		for (int i = 0; i <= rand()% MAX_NB_FRAMES_PER_IT; i++)
		{
			int choice = rand() % 2;
			switch (choice)
			{	
			case 0:				//Routine
				QTimer::singleShot(0, this, SLOT(routine()));
				QTimer::singleShot(0, this, SLOT(updateGraphPath()));
				break;	
			case 1:				//Call request
				QTimer::singleShot(0, this, SLOT(callRequest()));
				QTimer::singleShot(0, this, SLOT(updateGraphPath()));
			}
		}
		wait_until_next_second();
	}
	QTimer::singleShot(100, this, SLOT(updateUsersDistribution()));
}

void Launcher::updateGraphPath(void)
{
	float threshold_lvl = ui.thresholdPowerTextBox->text().toFloat(); 
	QGraphicsScene *scene = new QGraphicsScene();
	QPainterPath graphPath = QPainterPath();
	graphPath.addPolygon(_polygon);
	
	QLineF line_thr(QPointF(0, -threshold_lvl *3), QPointF(ui.graphResults->width()-5, -threshold_lvl *3));
	QGraphicsLineItem *line_thrItem = new QGraphicsLineItem(line_thr);
	line_thrItem->setPen(QPen(Qt::red, 1));

	QGraphicsPathItem *_curve = new QGraphicsPathItem(graphPath);
	ui.graphResults->setScene(scene);
	ui.graphResults->setRenderHint(QPainter::Antialiasing, true);
	ui.graphResults->scene()->addItem(_curve);
	ui.graphResults->scene()->addItem(line_thrItem);
}

void Launcher::updateResultLabels(User *user, bool accepted)
{
	ui.lastPathLossLabel->setText(QString::number(user->getPathLoss(), 'f'));
	ui.lastDevotedPowerLabel->setText(QString::number(user->getDevotedPower(), 'f'));
	ui.lastAveragePowerLabel->setText(QString::number(_baseStation->getAverageTransmittedPower(), 'f'));
	ui.lastPowerIncreaseLabel->setText(QString::number(_baseStation->computeIncreaseEstimation(user), 'f'));
	ui.nbRejectedLabel->setText(QString::number(nbRejected));
	ui.admissionRateLabel->setText(QString::number((nbTotal - nbRejected) *100 / nbTotal) + '%');

	QPalette plt;
	if (accepted)
	{
		plt.setColor(QPalette::WindowText, Qt::green);
		ui.lastBoolResultLabel->setPalette(plt);
		ui.lastBoolResultLabel->setText("Last request accepted");
	} else {
		plt.setColor(QPalette::WindowText, Qt::red);
		ui.lastBoolResultLabel->setPalette(plt);
		ui.lastBoolResultLabel->setText("Last request rejected");
	}
}

void Launcher::updateUsersDistribution(void)
{
	QGraphicsScene *scene = new QGraphicsScene();

	QGraphicsEllipseItem *circleItem = new QGraphicsEllipseItem(0, 0, 150, 150);
	circleItem->setVisible(true);
	ui.usersDistribution->setScene(scene);
	ui.usersDistribution->scene()->addItem(circleItem);

	int center_pos = 75;
	//Setting base station pixel
	QColor c_base("red");
	QImage *image = new QImage(5, 5, QImage::Format_Indexed8);
	image->setColor(0, c_base.rgb());
	QPixmap imagePixmap_base(QPixmap::fromImage(*image,Qt::AutoColor));
    QGraphicsPixmapItem* item_base = new QGraphicsPixmapItem(imagePixmap_base);
	item_base->setPos(center_pos, center_pos);
	ui.usersDistribution->scene()->addItem(item_base);

	int nbUsers = _baseStation->getListOfUsersList().back().size();

	//Setting users pixel
	for (int i = 0; i < nbUsers; i++)
	{
		int rd;
		float userDistance = _baseStation->getListOfUsersList().back().at(i)->getDistance() / ui.cellRadiusTextBox->text().toFloat();
		int coeff_x = 1;
		int coeff_y = 1;
		rd = rand()%2;
		if (rd == 1)
			coeff_x = - 1;
		rd = rand()%2;
		if (rd == 1)
			coeff_y = -1;
				
		float angle = ((float) (rand()%90 + 1)) *3.14159265/180; //angle needs to be expressed in radians
		float Y = coeff_y * (userDistance * center_pos)* cos(angle);
		float X = coeff_x * (sqrt(pow((userDistance * center_pos), 2) - pow(Y, 2)));

		float scaled_Y = center_pos + Y;
		float scaled_X = center_pos + X;
		ui.usersDistribution->scene()->addEllipse(scaled_X, scaled_Y, 3, 3, QPen(Qt::black, 3));
	}
	ui.usersDistribution->setRenderHint(QPainter::Antialiasing, true);
	ui.nbUsersLabel->setText(QString::number(nbUsers));
	ui.distanceLastUserLabel->setText(QString::number(_baseStation->getListOfUsersList().back().back()->getDistance()));
}

void Launcher::wait_until_next_second()
{
	qDebug() << "Waiting 'til next second...";
    time_t before = time(0);
    while (difftime(time(0), before) < 1);
}


void Launcher::callRequest(void)
{	
	//qDebug() << "Running call request";

	float mobileHeight;
	if (ui.urbanRadioButton->isChecked())
		mobileHeight = ui.mobileHeightTextBox->text().toFloat();
	else 
		mobileHeight = ui.sub_MobileHeightTextBox->text().toFloat();
	
	int idUser = _baseStation->getListOfUsersList().back().size() + _baseStation->getListOfUsersList().size();
	User *user = new User(idUser, mobileHeight, ui.cellRadiusTextBox->text().toFloat(), _baseStation);
	bool accepted = _baseStation->isAdmissible(user);
	if (accepted)
	{
		_baseStation->addUser(user);
		_baseStation->addUserList(_baseStation->getUsersList());
		_baseStation->computeTotalTransmittedPower();
		//_baseStation->computeDevotedPowerAllUsers();
		_baseStation->computeAverageTransmittedPower();
	} else {
		nbRejected++;
	}
	_polygon << QPointF(_baseStation->getListOfUsersList().size(), -(_baseStation->getAverageTransmittedPower() *3 + _baseStation->computeIncreaseEstimation(user)*3));
	nbTotal++;
	updateResultLabels(user, accepted);
}

void Launcher::routine(void)
{
	//qDebug() << "Running routine";

	int nbUsers = _baseStation->getListOfUsersList().back().size();
	int index = 0;
	if (nbUsers != 0) {
		index = rand() % nbUsers;
		_baseStation->removeUserAt(index);
		_baseStation->addUserList(_baseStation->getUsersList());
		_baseStation->computeTotalTransmittedPower();
		//_baseStation->computeDevotedPowerAllUsers();
		_baseStation->computeAverageTransmittedPower();
	}

	//_polygon << QPointF(_baseStation->getListOfUsersList().size(), -(_baseStation->getAverageTransmittedPower()  *3));
}