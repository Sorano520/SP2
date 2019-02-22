#include "Vehicle.h"

float Vehicle::SpeedZCoefficientUp;
float Vehicle::SpeedZCoefficientDown;
bool Vehicle::teleportation;

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
	this->SpeedZAxis = DefaultSpeedZAxis = SpeedZAxis;
	RotateValue = RotateSpeed = 0.f;
	RotateSpeedCoefficient = 0;
	DefaultRotateSpeedCoefficient = 0.05f;
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
		setPosition((Target - getPosition()) * 0.2f + getPosition());
		ReverseSpeed();
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
			Vector3 view = Target - getPosition();
			Object.Target = Object.getPosition() + view;
			Object.setPosition((Object.Target - Object.getPosition()) * 0.1 + Object.getPosition());
			setPosition(-view * 0.1 + getPosition());
			Object.RotateValue = RotateValue;
		}
		else if (SpeedZAxis <= Object.SpeedZAxis)
		{
			float temp = SpeedZAxis;
			SpeedZAxis = Object.SpeedZAxis * 1.3;
			Object.SpeedZAxis = temp;
			Vector3 view = Object.Target - Object.getPosition();
			//Target = getPosition() + view;
			Object.setPosition(-view * 0.2 + Object.getPosition());
			setPosition((Target - getPosition()) * 0.2 + getPosition());
			if (getPosition().x < Object.getPosition().x)
			{
				RotateSpeedCoefficient = 2;
			}
			else if (getPosition().x > Object.getPosition().x)
			{
				RotateSpeedCoefficient = -2;
			}
			//RotateValue = Object.RotateValue;
		}
		return true;
	}
}

bool Vehicle::Collision(TrackObject& Object)
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
	if (dist <= distcheck)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Vehicle::ReverseSpeed()
{
	SpeedZAxis *= -1;
}


void Vehicle::Reset()
{
	setPosition(DefaultPosition);
	Target = DefaultTarget;
	Up = DefaultUp;
	RotateValue = 0.f;
	SpeedZAxis = 0.f;
}