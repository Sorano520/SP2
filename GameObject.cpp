#include "GameObject.h"

void GameObject::setHitBox(float tempX[2], float tempY[2], float tempZ[2])
{
	for (int NumofTimes = 0; NumofTimes < 2; NumofTimes++)
	{
		CoordX[NumofTimes] = tempX[NumofTimes];
		CoordY[NumofTimes] = tempY[NumofTimes];
		CoordZ[NumofTimes] = tempZ[NumofTimes];
	}
	XDist = abs(CoordX[0] - CoordX[1])/2;
	YDist = abs(CoordY[0] - CoordY[1])/2;
	ZDist = abs(CoordZ[0] - CoordZ[1])/2;
}

float GameObject::getXDist()
{
	return XDist;
}

float GameObject::getYDist()
{
	return YDist;
}

float GameObject::getZDist()
{
	return ZDist;
}

Vector3 GameObject::getPosition()
{
	return Position;
}

void GameObject::setPosition(Vector3 Pos)
{
	Position = Pos;
}

void GameObject::addPosition(Vector3 Pos)
{
	Position += Pos;
}

void GameObject::setPosition(float X, float Y, float Z)
{
	Position.x = X;
	Position.y = Y;
	Position.z = Z;
}