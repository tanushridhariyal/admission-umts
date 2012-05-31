#pragma once
#include <vector>

class User; //forward declaration to break-up circular dependencies

class BaseStation
{
public:
	BaseStation(void);
	~BaseStation(void);
	BaseStation(float pilotPower, float bandwidth, float snrTarget, float bitRate, float noisePower, float orthoFactor , 
		float baseStationHeight, float gain, float frequency, float totalTransmittedPower, float thresholdPower);
	float computeIncreaseEstimation (User user);
	bool isAdmissible(User user);

	//Accessors
	const std::vector<User>& getUsersList(void) const;
	const User& getUserAt(int index) const;
	const float& getPilotPower(void) const;
	const float& getBandwidth(void) const;
	const float& getSnrTarget(void) const;
	const float& getBitRate(void) const;
	const float& getNoisePower(void) const;
	const float& getOrthoFactor(void) const;
	const float& getBaseStationHeight(void) const;
	const float& getGain(void) const;
	const float& getFrequency(void) const;
	//const float& getTotalTransmittedPower(void) const;
	const float& getThresholdPower(void) const;
	float watt_to_db(float);
	float db_to_watt(float);
	//Mutators
	void setThresholdPower(float thresholdPower);
	void addUser(User*) ;
	void computeTotalTransmitted();

private:
	std::vector<User*> _usersList;
	std::vector<float> _totalTransmitted;
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

