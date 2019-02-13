#include "Vehicle.h"

Vehicle::Vehicle()
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::Init(const Vector3& Position, const Vector3& Target, const Vector3& Up, float SpeedZAxis)
{
	setPosition(Position);
	DefaultPosition = Position;
	this->Target = DefaultTarget = Target;
	Vector3 View = (Target - Position).Normalized();
	Vector3 Right = View.Cross(Up);
	Right.y = 0;
	Right.Normalize();
	this->Up = DefaultUp = Right.Cross(View).Normalized();
	SpeedXAxis = 0;
	this->SpeedZAxis = SpeedZAxis;
	RotateValue = 0.f;
}

//void Vehicle::Update(double dt)
//{
//	float SKYBOXSIZE = 1000.f;
//	float carspeed = 3;
//	Vector3 view = (Target - getPosition()).Normalized();
//	Vector3 right = view.Cross(Up);
//	static const float CAMERA_SPEED = 0.2f;
//	if (Application::IsKeyPressed('A')) // MOVE LEFT
//	{
//		if (SpeedXAxis >= -3)
//		{
//			SpeedXAxis -= (CAMERA_SPEED * dt);
//		}
//	}
//	if (Application::IsKeyPressed('D')) // MORE RIGHT
//	{
//		if (SpeedXAxis <= carspeed)
//		{
//			SpeedXAxis += (CAMERA_SPEED * dt);
//		}
//	}
//	if (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) // MOVE UP
//	{
//		if (SpeedZAxis <= carspeed)
//		{
//			SpeedZAxis += (CAMERA_SPEED * dt);
//		}
//	}
//	if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) // MOVE BACK
//	{
//		if (SpeedZAxis >= -carspeed)
//		{
//			SpeedZAxis -= (CAMERA_SPEED * dt);
//		}
//	}
//	if (Application::IsKeyPressed(VK_LEFT)) // TURN LEFT
//	{
//		float yaw = (float)(CAMERA_SPEED * dt)* 250.f;
//		Mtx44 rotation;
//		rotation.SetToRotation(yaw, 0, 1, 0);
//		view = rotation * view;
//		Target = getPosition() + view;
//		RotateValue += (float)(CAMERA_SPEED * dt)* 250.f;
//		if (SpeedZAxis > 0)
//		{
//			SpeedZAxis -= (CAMERA_SPEED * dt) / 10.f;
//		}
//		
//	}
//	if (Application::IsKeyPressed(VK_RIGHT)) // TURN RIGHT
//	{
//		float yaw = (float)(-CAMERA_SPEED * dt)* 250.f;
//		Mtx44 rotation;
//		rotation.SetToRotation(yaw, 0, 1, 0);
//		view = rotation * view;
//		Target = getPosition() + view;
//		RotateValue -= (float)(CAMERA_SPEED * dt)* 250.f;
//		//RotateValue = ((Target.z - Position.z) - 1) * 90;// +((Target.x - Position.x)) * 90;
//		if (SpeedZAxis > 0)
//		{
//			SpeedZAxis -= (CAMERA_SPEED * dt) / 10.f;
//		}
//	}
//	setPosition(getPosition() + right * SpeedXAxis);
//	if (SpeedZAxis > 0)
//	{
//		SpeedZAxis -= (CAMERA_SPEED * dt) / 5.f;
//	}
//	setPosition(getPosition() + view * SpeedZAxis);
//	Target = getPosition() + view;
//}

Vector3 Vehicle::getTarget()
{
	return Target;
}

float Vehicle::getRotateValue()
{
	return RotateValue;
}

bool Vehicle::Collision(Environment& Object)
{
	dist = sqrt(pow(getPosition().x - Object.getPosition().x, 2) + 
		//pow(Position.y - Object.getPosition().y, 2) + 
		pow(getPosition().z - Object.getPosition().z, 2));
	float angle = atan(abs(getPosition().z - Object.getPosition().z)/abs(getXDist() + Object.getXDist()));
	if (angle >= atan(abs(Object.getZDist() / Object.getXDist())))
	{
		distcheck = getZDist() + Object.getZDist();
	}
	else
	{
		distcheck = ((getXDist() + Object.getXDist()) / cos(angle));
	}
	if (dist >= distcheck)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Vehicle::Collision(Vehicle& Object)
{
	dist = sqrt(pow(getPosition().x - Object.getPosition().x, 2) +
		//pow(Position.y - Object.getPosition().y, 2) + 
		pow(getPosition().z - Object.getPosition().z, 2));
	float angle = atan(abs(getPosition().z - Object.getPosition().z) / abs(getXDist() + Object.getXDist()));
	if (angle >= atan(abs(Object.getZDist() / Object.getXDist())))
	{
		distcheck = getZDist() + Object.getZDist();
	}
	else
	{
		distcheck = ((getXDist() + Object.getXDist()) / cos(angle));
	}
	if (dist >= distcheck)
	{
		return false;
	}
	else
	{
		if (SpeedZAxis >= Object.SpeedZAxis)
		{
			float temp = SpeedZAxis;
			SpeedZAxis = Object.SpeedZAxis;
			Object.SpeedZAxis = temp * 0.7;
			temp = SpeedXAxis;
			SpeedXAxis = Object.SpeedXAxis;
			Object.SpeedXAxis = temp * 0.7;
		}
		else if (SpeedZAxis <= Object.SpeedZAxis)
		{

			float temp = SpeedZAxis;
			SpeedZAxis = Object.SpeedZAxis * 1.3;
			Object.SpeedZAxis = temp;
			temp = SpeedXAxis;
			SpeedXAxis = Object.SpeedXAxis * 1.3;
			Object.SpeedXAxis = temp;
		}
		return true;
	}
}

void Vehicle::ReverseSpeed()
{
	SpeedXAxis *= -1;
	SpeedZAxis *= -0.5;
}