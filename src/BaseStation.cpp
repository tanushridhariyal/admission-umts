#include <math.h>

#include "BaseStation.h"
#include "User.h"


BaseStation::BaseStation(void)
{
}


BaseStation::~BaseStation(void)
{
}

BaseStation::BaseStation(float pilotPower, float bandwidth, float snrTarget, float bitRate, float noisePower, float orthoFactor ,
	float baseStationHeight, float gain, float frequency, float totalTransmittedPower, float thresholdPower)
{
	_pilotPower = pilotPower;
	_bandwidth = bandwidth;
	_snrTarget = snrTarget;
	_bitRate = bitRate;
	_noisePower = noisePower;
	_orthoFactor = orthoFactor;
	_baseStationHeight = baseStationHeight;
	_gain = gain;
	_frequency = frequency;
	_totalTransmittedPower = totalTransmittedPower;
	_thresholdPower = thresholdPower;
}

float BaseStation::computeIncreaseEstimation (User user)
{
	//TODO
	return 2;
}

bool BaseStation::isAdmissible(User user)
{
	//TODO
	return true;
}

//Accessors
const std::vector<User>& BaseStation::getUsersList(void) const
{
	return _usersList;
}

const User& BaseStation::getUserAt(int index) const
{
	return _usersList[index];
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

float watt_to_db(float watt_value) 
{
	return 10*log10(watt_value);

}
//Mutators
void BaseStation::setThresholdPower(float thresholdPower)
{
	_thresholdPower = thresholdPower;
}
