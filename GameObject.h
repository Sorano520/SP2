#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"

class GameObject
{
public:
	void setHitBox(float tempX[2], float tempY[2], float tempZ[2]);
	Vector3 getPosition();
	float getXDist();
	float getYDist();
	float getZDist();
private:
	Vector3 Position;
	Vector3 Hitbox[8];
	float XDist, YDist, ZDist;
	float CoordX[2];
	float CoordY[2];
	float CoordZ[2];
protected:
	void setPosition(Vector3);
	void setPosition(float, float, float);
	void addPosition(Vector3);
};

#endif // !GAMEOBJECT_H
