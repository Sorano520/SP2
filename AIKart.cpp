#include "AIKart.h"

float ni = 0;

AIKart::AIKart()
{
	SpeedZCoefficientDown = 1;
}

AIKart::~AIKart()
{

}

void AIKart::Update(double dt)
{
	
	float SKYBOXSIZE = 1500.f;
	float carspeed = 3;
	//Vector3 view = (Target - getPosition()).Normalized();
	//Vector3 right = view.Cross(Up);
	static const float CAMERA_SPEED = 0.2f;
	if (getPosition().x <= SKYBOXSIZE / 2 - 1.f && getPosition().x >= -SKYBOXSIZE / 2 + 1.f &&
		getPosition().y <= SKYBOXSIZE / 2 - 1.f && getPosition().y >= -SKYBOXSIZE / 2 + 1.f &&
		getPosition().z <= SKYBOXSIZE / 2 - 1.f && getPosition().z >= -SKYBOXSIZE / 2 + 1.f)
	{
		float dist = sqrt(pow(getPosition().x - LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].Center.x, 2) +
			pow(getPosition().z - LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].Center.z, 2));
		Vector3 direction = LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].Center - getPosition();
		Vector3 idk;
		idk.Set(1, 0, 1);
		/*RotateValue = Math::RadianToDegree(asin(idk.Length() / (Target.Length() * direction.Length())));*/
		Mtx44 Rotating;
		Rotating.SetToRotation(LapCheck.getRange()[LapCheck.getCurrentCheckPoint()].RotateValue, 0, 1, 0);
		idk = Rotating * idk;
		RotateValue = LapCheck.getRange()[LapCheck.getCurrentCheckPoint()].RotateValue;
		SpeedZAxis = DefaultSpeedZAxis * SpeedZCoefficientDown;
		if (ni == 500)
		{
			cout << direction.x << " " << direction.y << " " << direction.z << endl;
			ni = 0;
		}
		else
		{
			ni++;
		}
		if (SpeedZAxis > 0)
		{
			SpeedZAxis -= (CAMERA_SPEED * dt) / 5.f;
		}
		//setPosition(getPosition() + right * SpeedXAxis);
		addPosition(((direction.Dot(idk) / direction.LengthSquared())* direction) * SpeedZAxis);
		//setPosition(getPosition() + direction * SpeedZAxis);
		Target = getPosition() + direction;
		//Target = getPosition() + view;
	}
	else
	{
		Reset();
	}
}

int AIKart::CheckCar()
{
	switch (LapCheck.getCurrentLap())
	{
	case 1:
		LapCheck.setTotalCheckPoint(38);
		break;
	case 2:
		LapCheck.setTotalCheckPoint(78);
		if (LapCheck.getCurrentCheckPoint() == 3)
		{
			LapCheck.setCurrentCheckPoint(38);
			break;
		}
	case 3:
		if (LapCheck.getCurrentCheckPoint() == 3)
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
		break;
	default:
	{
		LapCheck.setCurrentCheckPoint(0);
		LapCheck.setTotalCheckPoint(78);
		break;
	}
	}
	if (getPosition().x <= LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].RangeX[0] && getPosition().x >= LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].RangeX[1]
		&& getPosition().z <= LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].RangeZ[0] && getPosition().z >= LapCounter::getRange()[LapCheck.getCurrentCheckPoint()].RangeZ[1])
	{
		LapCheck.addCurrentCheckPoint(1);
		if (LapCheck.getCurrentCheckPoint() == LapCounter::getTotalCheckPoint())
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

void AIKart::ReduceSpeedCar()
{
	SpeedZCoefficientDown = 0.5;
}

void AIKart::StopSpeedCar()
{
	SpeedZCoefficientDown = 0;
}

void AIKart::RegainSpeedCar()
{
	SpeedZCoefficientDown = 1;
}