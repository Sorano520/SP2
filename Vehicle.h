#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H

#include "Vector3.h"
#include "Mtx44.h"
#include "Application.h"
#include "GameObject.h"
#include "Environment.h"
#include "TrackObject.h"
#include "LapCounter.h"

class Vehicle : public GameObject
{
public:
	Vehicle();
	~Vehicle();
	void Init(const Vector3&, const Vector3&, const Vector3&, float);
	virtual void Update(double) = 0;
	bool Collision(Environment&);
	bool Collision(Vehicle&);
	bool Collision(TrackObject&);
	void ReverseSpeed();
	void Reset();
	Vector3 getTarget();
	virtual int CheckCar() = 0;

	float getRotateValue();
	float dist;
	float distcheck;
	float angle;

	float SpeedZAxis;
	float DefaultSpeedZAxis;
	float RotateValue;
	float RotateSpeed;
	float RotateSpeedCoefficient;
	float DefaultRotateSpeedCoefficient;

	static float SpeedZCoefficientUp;
	static float SpeedZCoefficientDown;
	static bool teleportation;

	LapCounter LapCheck;
protected:
	Vector3 Target;
	Vector3 Up;
	Vector3 DefaultPosition;
	Vector3 DefaultTarget;
	Vector3 DefaultUp;
};

#endif
