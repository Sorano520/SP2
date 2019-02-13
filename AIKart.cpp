#include "AIKart.h"

void AIKart::Update(double dt)
{
	float SKYBOXSIZE = 1000.f;
	float carspeed = 3;
	Vector3 view = (Target - getPosition()).Normalized();
	Vector3 right = view.Cross(Up);
	static const float CAMERA_SPEED = 0.01f;
	//SpeedZAxis += (CAMERA_SPEED * dt);
	setPosition(getPosition() + right * SpeedXAxis);
	setPosition(getPosition() + view * SpeedZAxis);
	Target = getPosition() + view;
}