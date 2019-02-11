#ifndef POSITION_CAMERA_H
#define POSITION_CAMERA_H

class PositionCameraOBJ
{
public:
	PositionCameraOBJ();
	void Set(float, float, float, float, float, float);
	float getX();
	float getY();
	float getZ();
	float getrotateX();
	float getrotateY();
	float getrotateZ();
	~PositionCameraOBJ();
private:
	float X, Y, Z;
	float rotateX, rotateY, rotateZ;
};

#endif