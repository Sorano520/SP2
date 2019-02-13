#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	verticalvalue = 0;
	horizontalvalue = 0;
	Shoot = false;
	OtherCam = false;
	speed = speedright = 0;
}

void Camera3::Update(double dt, Vehicle& Car)
{
	float SKYBOXSIZE = 1000.f;
	float carspeed = 3;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	static const float CAMERA_SPEED = 0.2f;
	if (Application::IsKeyPressed('R')) // RESET
	{
		Reset();
	}
	target.x = Car.getTarget().x;
	target.z = Car.getTarget().z;
	position.x = Car.getPosition().x + 10 * (Car.getPosition().x - Car.getTarget().x);
	position.z = Car.getPosition().z + 10 * (Car.getPosition().z - Car.getTarget().z);
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}