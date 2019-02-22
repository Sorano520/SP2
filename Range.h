#pragma once

#include "Vector3.h"

class Range
{
public:
	Range();
	~Range();
	Vector3 Center;
	float RangeX[2];
	float RangeZ[2];
	float RotateValue;
};