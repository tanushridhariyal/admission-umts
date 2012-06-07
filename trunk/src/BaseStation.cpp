#include <math.h>

#include <time.h>

#include "BaseStation.h"
#include "User.h"


BaseStation::BaseStation(void)
{
}


BaseStation::~BaseStation(void)
{
}

BaseStation::BaseStation(float pilotPower, float bandwidth, float snrTarget, float bitRate, float noisePower, float orthoFactor ,
	float baseStationHeight, float gain, float frequency, float thresholdPower, int averagingPeriod)
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
	_thresholdPower = thresholdPower;
	_averagingPeriod = averagingPeriod;
}

//Computation methods
void BaseStation::computeTotalTransmittedPower(void)
{
	float divisor, totalPower = 0;
	divisor = getBandwidth() /
		(db_to_watt(getSnrTarget()) * getBitRate()) + getOrthoFactor(); // store the constant divisor factor of the formula
	
	for(int i = 0; i < _usersList.size(); i++)
	{
		totalPower = totalPower + db_to_watt(_usersList[i]->getPathLoss())/divisor;
	}
	totalPower = totalPower * dbm_to_watt(getNoisePower()) + dbm_to_watt(getPilotPower());
	totalPower = totalPower / (1-_usersList.size() * (getOrthoFactor()/divisor));

	_totalTransmittedPower.push_back(totalPower);
}

float BaseStation::computeIncreaseEstimation (User *user)
{
	float sum = 0;
	//for the (i -j) frames
	int end_it, divisor, nbUsers;
	
	if (_listOfUsersList.size() > _averagingPeriod)
	{
		end_it = _listOfUsersList.size() - _averagingPeriod;
		divisor = _averagingPeriod;
	} else {
		end_it = 0;
		divisor = _listOfUsersList.size();
	}

	std::vector<User*> usersList;
	
	for (int i = _listOfUsersList.size(); i > end_it; i--)
	{
		nbUsers = _listOfUsersList[i-1].size();
		//for each connected user
		for (int j = 0; j < nbUsers; j++)
		{
		usersList = _listOfUsersList[i-1];
		sum += dbm_to_watt(usersList[j]->getDevotedPower());
		}
		sum = sum / nbUsers;
	}
	return watt_to_dbm(sum / divisor);
}

void BaseStation::computeAverageTransmittedPower(void) 
{
	float sum = 0;
	//for the (i-j) frames
	int end_it;
	float divisor;
	if (_totalTransmittedPower.size() > _averagingPeriod)
	{
		end_it = _totalTransmittedPower.size() - _averagingPeriod;
		divisor = _averagingPeriod;
	} else {
		end_it = _totalTransmittedPower.size();
		divisor = _totalTransmittedPower.size();
	}

	for (int i = _totalTransmittedPower.size(); i >= end_it; i--)
	{
		sum += _totalTransmittedPower[i-1] ;
	}
	_averageTransmittedPower = watt_to_dbm(sum / divisor);
}

bool BaseStation::isAdmissible(User *user)
{
	computeAverageTransmittedPower();
	if (_averageTransmittedPower + computeIncreaseEstimation(user) <= _thresholdPower)
		return true;
	else
		return false;
}

//Convertors
float BaseStation::watt_to_db(float watt_value) 
{
	return 10 * log10(watt_value);

}

float BaseStation::watt_to_dbm(float watt_value)
{
	return 10 * log10(watt_value * 1000);
}

float BaseStation::db_to_watt(float db_value)
{
	return pow(10,((db_value) / 10));
}

float BaseStation::dbm_to_watt(float dbm_value)
{
	return pow(10,((dbm_value) / 10)) / 1000;
}

//Accessors
const std::vector<User*>& BaseStation::getUsersList(void) const
{
	return _usersList;
}

const std::vector<std::vector<User*> >& BaseStation::getListOfUsersList(void)
{
	return _listOfUsersList;
}

User* BaseStation::getUserAt(int index) const
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

const std::vector<float>& BaseStation::getTotalTransmittedPower(void) const
{
	return _totalTransmittedPower;
}

const float& BaseStation::getAverageTransmittedPower(void) const
{
	return _averageTransmittedPower;
}

const float& BaseStation::getThresholdPower(void) const
{
	return _thresholdPower;
}

//Mutators
void BaseStation::setThresholdPower(float thresholdPower)
{
	_thresholdPower = thresholdPower;
}

void BaseStation::addUser(User *user) 
{
	_usersList.push_back(user);
}

void BaseStation::addUserList(const std::vector<User*>& usersList)
{
	_listOfUsersList.push_back(usersList);
}

void BaseStation::removeUserAt(int index)
{
	std::vector<User*>::const_iterator it = getUsersList().begin();
	for (int i = 0; i < index; i++) 
		it++;

	_usersList.erase(it);
}