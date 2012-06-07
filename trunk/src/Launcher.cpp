#include <time.h>

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
	_polygon << QPointF(0, 0);

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
		User *user = new User(i, mobileHeight, _baseStation);
		_baseStation->addUser(user);
	}
	_baseStation->computeTotalTransmittedPower();
	_baseStation->addUserList(_baseStation->getUsersList());
	_baseStation->computeAverageTransmittedPower();

	//Updating graph. Note : y values have to be <0 to be consistent with what is expected
	_polygon << QPointF(0, -(_baseStation->getAverageTransmittedPower()));
	qDebug() << _baseStation->getAverageTransmittedPower()*3;
	
	//Randomly managing flow of user within the cell
	generateFlow();

	ui.resultLabel->setText(QString("Simulation completed"));
	qDebug() << "Simulation completed";
}

void Launcher::generateFlow(void)
{
	QTime time_;
	time_.start();
	int MAX_NB_FRAMES_PER_IT = 10;
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
}

void Launcher::updateGraphPath(void)
{
	QGraphicsScene *scene = new QGraphicsScene();
	graphPath = QPainterPath();
	graphPath.addPolygon(_polygon);
	
	//Adding admission threshold line
	//graphPath.moveTo(0, -75);
	//graphPath.lineTo(ui.graphResults->width()-5, -75);

	//Painting path
	QPainter painter(this);
	painter.setWorldMatrixEnabled(false);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawPath(graphPath);

	QGraphicsPathItem *_curve = new QGraphicsPathItem(graphPath);
	_curve->setVisible(true);
	ui.graphResults->setScene(scene);
	ui.graphResults->scene()->addItem(_curve);	
}

void Launcher::updateResultLabels(User *user, bool accepted)
{
	ui.lastPathLossLabel->setText(QString::number(user->getPathLoss(), 'f'));
	ui.lastDevotedPowerLabel->setText(QString::number(user->getDevotedPower(), 'f'));
	ui.lastAveragePowerLabel->setText(QString::number(_baseStation->getAverageTransmittedPower(), 'f'));
	ui.lastPowerIncreaseLabel->setText(QString::number(_baseStation->computeIncreaseEstimation(user), 'f'));

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

void Launcher::wait_until_next_second()
{
	qDebug() << "Waiting 'til next second...";
    time_t before = time(0);
    while (difftime(time(0), before) < 1);
}


void Launcher::callRequest(void)
{	
	qDebug() << "Running call request";

	float mobileHeight;
	if (ui.urbanRadioButton->isChecked())
		mobileHeight = ui.mobileHeightTextBox->text().toFloat();
	else 
		mobileHeight = ui.sub_MobileHeightTextBox->text().toFloat();
	
	int idUser = _baseStation->getListOfUsersList().back().size() + _baseStation->getListOfUsersList().size();
	User *user = new User(idUser, mobileHeight, _baseStation);
	bool accepted = _baseStation->isAdmissible(user);
	if (accepted)
	{
		_baseStation->addUser(user);
		_baseStation->computeTotalTransmittedPower();
		_baseStation->addUserList(_baseStation->getUsersList());
		_baseStation->computeAverageTransmittedPower();
	}
	_polygon << QPointF(_baseStation->getListOfUsersList().size()*10, -(_baseStation->getAverageTransmittedPower()));
	qDebug() << _baseStation->getAverageTransmittedPower()*3;
	updateResultLabels(user, accepted);
}

void Launcher::routine(void)
{
	qDebug() << "Running routine";

	int nbUsers = _baseStation->getListOfUsersList().back().size();
	int index = rand() % nbUsers;
	_baseStation->removeUserAt(index);
	_baseStation->computeTotalTransmittedPower();
	_baseStation->addUserList(_baseStation->getUsersList());
	_baseStation->computeAverageTransmittedPower();

	_polygon << QPointF(_baseStation->getListOfUsersList().size()*10, -(_baseStation->getAverageTransmittedPower()));
	qDebug() << _baseStation->getAverageTransmittedPower()*3;
}