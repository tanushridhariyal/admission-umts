#include "User.h"


User::User(void)
{
}


User::~User(void)
{
}

//Accessors
const BaseStation& User::getBaseStation(void) const
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

//Mutators
void User::setBaseStation(BaseStation baseStation)
{
	_baseStation = baseStation;
}
