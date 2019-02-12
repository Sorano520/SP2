#include "Vehicle.h"

Vehicle::Vehicle()
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::Init(const Vector3& Position, const Vector3& Target, const Vector3& Up)
{
	this->Position = DefaultPosition = Position;
	this->Target = DefaultTarget = Target;
	Vector3 View = (Target - Position).Normalized();
	Vector3 Right = View.Cross(Up);
	Right.y = 0;
	Right.Normalize();
	this->Up = DefaultUp = Right.Cross(View).Normalized();
	SpeedXAxis = SpeedZAxis = 0;
	RotateValue = 0.f;
}

void Vehicle::Update(double dt)
{
	float SKYBOXSIZE = 1000.f;
	float carspeed = 3;
	Vector3 view = (Target - Position).Normalized();
	Vector3 right = view.Cross(Up);
	static const float CAMERA_SPEED = 0.2f;
	if (Application::IsKeyPressed('A')) // MOVE LEFT
	{
		if (SpeedXAxis >= -3)
		{
			SpeedXAxis -= (CAMERA_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed('D')) // MORE RIGHT
	{
		if (SpeedXAxis <= carspeed)
		{
			SpeedXAxis += (CAMERA_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed('W')) // MOVE UP
	{
		if (SpeedZAxis <= carspeed)
		{
			SpeedZAxis += (CAMERA_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed('S')) // MOVE BACK
	{
		if (SpeedZAxis >= -carspeed)
		{
			SpeedZAxis -= (CAMERA_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed(VK_LEFT)) // TURN LEFT
	{
		float yaw = (float)(CAMERA_SPEED * dt)* 250.f;
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		Target = Position + view;
		RotateValue += (float)(CAMERA_SPEED * dt)* 250.f;
		
		if (SpeedZAxis > 0)
		{
			SpeedZAxis -= (CAMERA_SPEED * dt) / 25.f;
		}
		
	}
	if (Application::IsKeyPressed(VK_RIGHT)) // TURN RIGHT
	{
		float yaw = (float)(-CAMERA_SPEED * dt)* 250.f;
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		Target = Position + view;
		RotateValue -= (float)(CAMERA_SPEED * dt)* 250.f;
		//RotateValue = ((Target.z - Position.z) - 1) * 90;// +((Target.x - Position.x)) * 90;
		if (SpeedZAxis > 0)
		{
			SpeedZAxis -= (CAMERA_SPEED * dt) / 25.f;
		}
	}
	Position = Position + right * SpeedXAxis;
	if (SpeedZAxis > 0)
	{
		SpeedZAxis -= (CAMERA_SPEED * dt) / 25.f;
	}
	Position = Position + view * SpeedZAxis;
	Target = Position + view;
}

float Vehicle::getX()
{
	return Position.x;
}

float Vehicle::getY()
{
	return Position.y;
}

float Vehicle::getZ()
{
	return Position.z;
}

float Vehicle::getTargetX()
{
	return Target.x;
}

float Vehicle::getTargetY()
{
	return Target.y;
}

float Vehicle::getTargetZ()
{
	return Target.z;
}

float Vehicle::getRotateValue()
{
	return RotateValue;
}