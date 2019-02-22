#include "Player.h"

Player::Player()
{
	for (int a = 0; a < 10; a++)
	{
		Tutorial[a] = false;
	}
	SpeedZCoefficientUp = 1.f;
}

void Player::Update(double dt)
{
	float SKYBOXSIZE = 1500.f;
	float carspeed = 1.5;
	float yaw;
	Mtx44 rotation;
	Vector3 view = (Target - getPosition()).Normalized();
	Vector3 right = view.Cross(Up);
	static const float CAMERA_SPEED = 0.2f;
	if (getPosition().x <= SKYBOXSIZE / 2 - 1.f && getPosition().x >= -SKYBOXSIZE / 2 + 1.f &&
		getPosition().y <= SKYBOXSIZE / 2 - 1.f && getPosition().y >= -SKYBOXSIZE / 2 + 1.f &&
		getPosition().z <= SKYBOXSIZE / 2 - 1.f && getPosition().z >= -SKYBOXSIZE / 2 + 1.f)
	{
		if (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) // MOVE UP
		{
			if (SpeedZAxis <= carspeed)
			{
				if (SpeedZAxis < 0)
				{
					SpeedZAxis += (CAMERA_SPEED * dt) * 2.5f;
				}
				SpeedZAxis += (CAMERA_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) // MOVE BACK
		{
			if (SpeedZAxis >= -1.f)
			{
				SpeedZAxis -= (CAMERA_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_LEFT)) // TURN LEFT
		{
			RotateSpeedCoefficient = DefaultRotateSpeedCoefficient;
			if (RotateSpeed <= 1.f)
			{
				RotateSpeed += RotateSpeedCoefficient;
			}
			else
			{
				RotateSpeedCoefficient = DefaultRotateSpeedCoefficient;
			}
			if (SpeedZAxis > 0)
			{
				SpeedZAxis -= (CAMERA_SPEED * dt) / 10.f;
			}
		}
		else if (RotateSpeed > 0)
		{
			RotateSpeed -= RotateSpeedCoefficient;
		}
		if (Application::IsKeyPressed(VK_RIGHT)) // TURN RIGHT
		{
			RotateSpeedCoefficient = DefaultRotateSpeedCoefficient;
			if (RotateSpeed > -1)
			{
				RotateSpeed -= RotateSpeedCoefficient;
			}
			else
			{
				RotateSpeedCoefficient = DefaultRotateSpeedCoefficient;
			}
			if (SpeedZAxis > 0)
			{
				SpeedZAxis -= (CAMERA_SPEED * dt) / 10.f;
			}
		}
		else if (RotateSpeed < 0)
		{
			RotateSpeed += RotateSpeedCoefficient;
		}
		// Rotation
		if (SpeedZAxis < 0)
		{
			yaw = RotateSpeed * (float)(-CAMERA_SPEED * dt)* 250.f;
			RotateValue -= RotateSpeed * (float)(CAMERA_SPEED * dt)* 250.f;
		}
		else
		{
			yaw = RotateSpeed * (float)(CAMERA_SPEED * dt)* 250.f;
			RotateValue += RotateSpeed * (float)(CAMERA_SPEED * dt)* 250.f;
		}
		if (RotateSpeedCoefficient == 2.0f)
		{
			RotateSpeed = RotateSpeedCoefficient;
			yaw = RotateSpeed * (float)(CAMERA_SPEED * dt)* 250.f;
			RotateValue += RotateSpeed * (float)(CAMERA_SPEED * dt)* 250.f;
		}
		// Decrease Speed 
		if (SpeedZAxis > 0)
		{
			SpeedZAxis -= (CAMERA_SPEED * dt) / 5.f;
		}

		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		setPosition(getPosition() + view * SpeedZAxis);
		Target = getPosition() + view;
	}
	else
	{ 
		Reset();
	}
}

int Player::CheckCar()
{
	switch (LapCheck.getCurrentLap())
	{
	case 1:
		LapCheck.setTotalCheckPoint(38);
		break;
	case 2:
		LapCheck.setTotalCheckPoint(78);
		if (LapCheck.getCurrentCheckPoint() >= 4 && LapCheck.getCurrentCheckPoint() <= 10)
		{
			LapCheck.setCurrentCheckPoint(38);
			break;
		}
		else
		{
			break;
		}
	case 3:
		if (LapCheck.getCurrentCheckPoint() >= 3 && LapCheck.getCurrentCheckPoint() <= 10)
		{
			if (getPosition().x <= LapCheck.getRange()[LapCheck.getCurrentCheckPoint()].Center.x)
			{
				LapCheck.setCurrentCheckPoint(39);
				LapCheck.setTotalCheckPoint(78);
			}
			else
			{
				LapCheck.setCurrentCheckPoint(4);
				LapCheck.setTotalCheckPoint(38);
			}
		}
	}
	if (getPosition().x <= LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].RangeX[0] && getPosition().x >= LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].RangeX[1]
		&& getPosition().z <= LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].RangeZ[0] && getPosition().z >= LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].RangeZ[1])
	{
		LapCheck.addCurrentCheckPoint(2);
		if (LapCheck.getCurrentCheckPoint() >= LapCounter::getTotalCheckPoint())
		{
			LapCheck.setCurrentCheckPoint(0);
			LapCheck.addCurrentLap();
		}
		if (LapCheck.getCurrentLap() == LapCheck.getLapNumber())
		{
			std::cout << "U finish the game." << std::endl;
		}
	}
	return LapCheck.getCurrentLap();
}
void Player::use_item_effect()
{
	storage.getitems();
	SpeedZAxis *= SpeedZCoefficientUp;
}

void Player::get_item_powerups()
{
	storage.useitem();
}

void Player::reduce_item_effect()
{
	SpeedZCoefficientUp = 1;
	SpeedZAxis *= SpeedZCoefficientUp;
}

//void Player::teleport(Vehicle& Object)
//{
//	Vector3 view = (Target - getPosition()).Normalized();
//	Mtx44 rotation;
//	LapCheck.setCurrentCheckPoint(Object.LapCheck.getCurrentCheckPoint() - 2);
//	setPosition(LapCheck.getRange()[LapCheck.getCurrentCheckPoint()].Center);
//	rotation.SetToRotation(LapCheck.getRange()[LapCheck.getCurrentCheckPoint()].RotateValue, 0, 1, 0);
//	view = rotation * view;
//	Target = getPosition() + Object.getTarget()-Object.getPosition();
//	RotateValue = Object.RotateValue;
//}