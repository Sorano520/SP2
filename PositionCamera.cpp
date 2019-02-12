#include "PositionCamera.h"

PositionCameraOBJ::PositionCameraOBJ()
{
	X = Y = Z = rotateX = rotateZ = rotateY = 0.f;
}

PositionCameraOBJ::~PositionCameraOBJ()
{
}

void PositionCameraOBJ::Set(float X, float Y, float Z, float rotateX, float rotateY, float rotateZ)
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
	this->rotateX = rotateX;
	this->rotateY = rotateY;
	this->rotateZ = rotateZ;
}

float PositionCameraOBJ::getX()
{
	return X;
}
float PositionCameraOBJ::getY()
{
	return Y;
}
float PositionCameraOBJ::getZ()
{
	return Z;
}
float PositionCameraOBJ::getrotateX()
{
	return rotateX;
}
float PositionCameraOBJ::getrotateY()
{
	return rotateY;
}
float PositionCameraOBJ::getrotateZ()
{
	return rotateZ;
}