#pragma once
#include <vector>

class BaseStation; //forward declaration to break-up circular dependencies

class User
{
public:
	User(void);
	~User(void);
	User(int id, float mobileHeight, float cellRadius, BaseStation*);
	void computePathLoss(void);
	void computeDevotedPower(void);

	//Accessors
	BaseStation* getBaseStation(void) const;
	const int& getId(void) const;
	const float& getMobileHeight(void) const;
	const float& getPathLoss(void) const;
	const float& getDevotedPower(void) const;
	const float& getDistance(void) const;

	//Mutators
	void setBaseStation(BaseStation *baseStation);

private:
	BaseStation* _baseStation;

	int _id;
	float _mobileHeight;
	float _pathLoss;
	float _devotedPower;
	float _distance;
};

