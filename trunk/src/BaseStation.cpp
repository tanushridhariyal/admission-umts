#include "BaseStation.h"


BaseStation::BaseStation(void)
{
}


BaseStation::~BaseStation(void)
{
}

float BaseStation::computeIncreaseEstimation (User user)
{
	//TODO
}
bool BaseStation::isAdmissible(User user)
{
	//TODO
}

//Accessors
const std::set<User>& BaseStation::getUsersList(void) const
{
	return _usersList;
}

const User& BaseStation::getUserAt(int id) const
{
	//TODO	
}

const float& BaseStation::getPilotPower(void) const
{
	return _pilotPower;
}

const float& BaseStation::getBandwidth(void) const
{
	return _bandwidth;
}

const float& BaseStation::getSnrTarget(void) const
{
	return _snrTarget;
}

const float& BaseStation::getBitRate(void) const
{
	return _bitRate;
}

const float& BaseStation::getNoisePower(void) const
{
	return _noisePower;
}

const float& BaseStation::getOrthoFactor(void) const
{
	return _orthoFactor;
}

const float& BaseStation::getBaseStationHeight(void) const
{
	return _baseStationHeight;
}

const float& BaseStation::getGain(void) const
{
	return _gain;
}

const float& BaseStation::getFrequency(void) const
{
	return _frequency;
}

const float& BaseStation::getTotalTransmittedPower(void) const
{
	return _totalTransmittedPower;
}

const float& BaseStation::getThresholdPower(void) const
{
	return _thresholdPower;
}

const float& watt_to_db(float watt_value) 
{
	return 10*log10(watt_value);

}
//Mutators
void BaseStation::setThresholdPower(float thresholdPower)
{
	_thresholdPower = thresholdPower;
}
