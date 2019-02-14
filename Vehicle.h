#ifndef VEHICLE_H
#define VEHICLE_H

#include "Vector3.h"
#include "Mtx44.h"
#include "Application.h"
#include "GameObject.h"
#include "Environment.h"

class Vehicle : public GameObject
{
public:
	Vehicle();
	~Vehicle();
	void Init(const Vector3&, const Vector3&, const Vector3&, float);
	virtual void Update(double) = 0;
	bool Collision(Environment&);
	bool Collision(Vehicle&);
	void ReverseSpeed();
	void Reset();
	Vector3 getTarget();

	float getRotateValue();
	float dist;
	float distcheck;
	float angle;

protected:
	Vector3 Target;
	Vector3 Up;
	Vector3 DefaultPosition;
	Vector3 DefaultTarget;
	Vector3 DefaultUp;
	float SpeedZAxis;
	float SpeedXAxis;
	float RotateValue;
};

#endif
