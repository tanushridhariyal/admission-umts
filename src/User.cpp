#include "User.h"
#include "BaseStation.h"


User::User(void)
{
}


User::~User(void)
{
	delete _baseStation;
}

//Accessors
BaseStation* User::getBaseStation(void) const
{
	return _baseStation;
}

const int& User::getId(void) const
{
	return _id;
}

const float& User::getMobileHeight(void) const
{
	return _mobileHeight;
}

const float& User::getPathLoss(void) const
{
	return _pathLoss;
}

const float& User::getDevotedPower(void) const
{
	return _devotedPower;
}

const float& User::getDistance(void) const
{
	return _distance;
}

//Mutators
//void User::setBaseStation(BaseStation baseStation)
//{
//	_baseStation = baseStation;
//}


//Fonctions
void User::computePathLoss(void)
{
	float F,B,E;
	
	F=46.3+33.9*log10(_baseStation->getFrequency())-13.82*log10(_baseStation->getBaseStationHeight());
	B=44.9-6.55*log10(_baseStation->getBaseStationHeight());
	E=(1.1*log10(_baseStation->getFrequency())-0.7)*_mobileHeight-(1.56*log10(_baseStation->getFrequency())-0.8);

	_pathLoss= F + B*log10(_distance)-E + _baseStation->getGain();
}

void User::computeDevotedPower(void)
{
}



