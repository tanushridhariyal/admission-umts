#pragma once
#include <vector>

class User; //forward declaration to break-up circular dependencies

class BaseStation
{
public:
	BaseStation(void);
	~BaseStation(void);
	BaseStation(float pilotPower, float bandwidth, float snrTarget, float bitRate, float noisePower, float orthoFactor , 
		float baseStationHeight, float gain, float frequency, float thresholdPower, int averagingPeriod);
	
	//Computation methods
	void computeTotalTransmittedPower(void);
	float computeIncreaseEstimation (User *user);
	void computeAverageTransmittedPower(void);
	bool isAdmissible(User *user);

	//Convertors
	static float watt_to_db(float);
	static float watt_to_dbm(float);
	static float db_to_watt(float);
	static float dbm_to_watt(float);

	//Accessors
	const std::vector<User*>& getUsersList(void) const;
	const std::vector<std::vector<User*> >& getListOfUsersList(void);
	User* getUserAt(int index) const;
	const float& getPilotPower(void) const;
	const float& getBandwidth(void) const;
	const float& getSnrTarget(void) const;
	const float& getBitRate(void) const;
	const float& getNoisePower(void) const;
	const float& getOrthoFactor(void) const;
	const float& getBaseStationHeight(void) const;
	const float& getGain(void) const;
	const float& getFrequency(void) const;
	const std::vector<float>& getTotalTransmittedPower(void) const;
	const float& getAverageTransmittedPower(void) const;
	const float& getThresholdPower(void) const;
	
	//Mutators
	void setThresholdPower(float thresholdPower);
	void addUser(User*);
	void addUserList(const std::vector<User*>& usersList);
	void removeUserAt(int index);

private:
	std::vector<User*> _usersList;
	std::vector<std::vector<User*> > _listOfUsersList;
	std::vector<float> _totalTransmittedPower;
	float _averageTransmittedPower;
	float _pilotPower;
	float _bandwidth;
	float _snrTarget;
	float _bitRate;
	float _noisePower;
	float _orthoFactor;
	float _baseStationHeight;
	float _gain;
	float _frequency;
	float _thresholdPower;
	int _averagingPeriod;
};

