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
	//_totalTransmittedPower = totalTransmittedPower;
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
/*const std::vector<User>& BaseStation::getUsersList(void) const
{
	return _usersList;
}

const User& BaseStation::getUserAt(int index) const
{
	return _usersList[index];
}
*/
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

/*const float& BaseStation::getTotalTransmittedPower(void) const
{
	return _totalTransmittedPower;
}
*/
const float& BaseStation::getThresholdPower(void) const
{
	return _thresholdPower;
}

float watt_to_db(float watt_value) 
{
	return 10*log10(watt_value);

}
float db_to_watt(float db_value)
{
	return pow(10,(db_value/10));
}

//Mutators
void BaseStation::setThresholdPower(float thresholdPower)
{
	_thresholdPower = thresholdPower;
}

void BaseStation::addUser(User* user1) {
	_usersList.push_back(user1);
}

void BaseStation::computeTotalTransmitted()
{
	float divisor,totalPower;
	divisor = getBandwidth()/(getSnrTarget()*getBitRate())+getOrthoFactor(); // store the constant divisor factor of the formula
	for(int i=0;i<_usersList.size();i++)
	{
		totalPower=totalPower+db_to_watt(_usersList[i]->getPathLoss())/divisor;
	}
	
	totalPower=totalPower*db_to_watt(getNoisePower()-30)+db_to_watt(getPilotPower()-30);

	totalPower=totalPower/(1-_usersList.size()*(getOrthoFactor()/divisor));

	_totalTransmitted.push_back(totalPower);



	//_totalTransmitted.push_back(Pt); 
}
