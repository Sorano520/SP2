#ifndef VEHICLE_H
#define VEHICLE_H

#include "Vector3.h"
#include "Mtx44.h"
#include "Application.h"

class Vehicle
{
public:
	Vehicle();
	~Vehicle();
	void Init(const Vector3&, const Vector3&, const Vector3&);
	void Update(double);

	float getX();
	float getY();
	float getZ();

	float getTargetX();
	float getTargetY();
	float getTargetZ();
	Vector3 Up;

	float getRotateValue();

private:
	Vector3 Position;
	Vector3 Target;
	Vector3 DefaultPosition;
	Vector3 DefaultTarget;
	Vector3 DefaultUp;
	float SpeedZAxis;
	float SpeedXAxis;
	float RotateValue;
};

#endif
