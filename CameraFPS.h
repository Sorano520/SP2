#ifndef CAMERAFPS_H
#define CAMERAFPS_H

#include "Vector3.h"

class CameraFPS
{
public:
	Vector3 forward;
	Vector3 up;
	Vector3 right;

	CameraFPS();
	~CameraFPS();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
};

#endif