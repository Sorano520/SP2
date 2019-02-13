#include "Player.h"

void Player::Update(double dt)
{
	float SKYBOXSIZE = 1000.f;
	float carspeed = 3;
	Vector3 view = (Target - getPosition()).Normalized();
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
	if (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) // MOVE UP
	{
		if (SpeedZAxis <= carspeed)
		{
			SpeedZAxis += (CAMERA_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) // MOVE BACK
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
		Target = getPosition() + view;
		RotateValue += (float)(CAMERA_SPEED * dt)* 250.f;
		if (SpeedZAxis > 0)
		{
			SpeedZAxis -= (CAMERA_SPEED * dt) / 10.f;
		}

	}
	if (Application::IsKeyPressed(VK_RIGHT)) // TURN RIGHT
	{
		float yaw = (float)(-CAMERA_SPEED * dt)* 250.f;
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		Target = getPosition() + view;
		RotateValue -= (float)(CAMERA_SPEED * dt)* 250.f;
		//RotateValue = ((Target.z - Position.z) - 1) * 90;// +((Target.x - Position.x)) * 90;
		if (SpeedZAxis > 0)
		{
			SpeedZAxis -= (CAMERA_SPEED * dt) / 10.f;
		}
	}
	setPosition(getPosition() + right * SpeedXAxis);
	if (SpeedZAxis > 0)
	{
		SpeedZAxis -= (CAMERA_SPEED * dt) / 5.f;
	}
	setPosition(getPosition() + view * SpeedZAxis);
	Target = getPosition() + view;
}