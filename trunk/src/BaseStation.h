#pragma once

#include <set>
#include <math.h>
#include "User.h"


class BaseStation
{
public:
	BaseStation(void);
	~BaseStation(void);
	float computeIncreaseEstimation (User user);
	bool isAdmissible(User user);

	//Accessors
	const std::set<User>& getUsersList(void) const;
	const User& getUserAt(int id) const;
	const float& getPilotPower(void) const;
	const float& getBandwidth(void) const;
	const float& getSnrTarget(void) const;
	const float& getBitRate(void) const;
	const float& getNoisePower(void) const;
	const float& getOrthoFactor(void) const;
	const float& getBaseStationHeight(void) const;
	const float& getGain(void) const;
	const float& getFrequency(void) const;
	const float& getTotalTransmittedPower(void) const;
	const float& getThresholdPower(void) const;
	const float& watt_to_db(float) ;
	//Mutators
	void setThresholdPower(float thresholdPower);

private:
	std::set<User> _usersList;

	float _pilotPower;
	float _bandwidth;
	float _snrTarget;
	float _bitRate;
	float _noisePower;
	float _orthoFactor;
	float _baseStationHeight;
	float _gain;
	float _frequency;
	float _totalTransmittedPower;
	float _thresholdPower;
};

