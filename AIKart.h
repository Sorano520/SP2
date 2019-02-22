#ifndef AIKART_H
#define AIKART_H

#include "Vehicle.h"

class AIKart : public Vehicle
{
public:
	AIKart();
	~AIKart();
	int CheckCar();
	void Update(double);
	static void ReduceSpeedCar();
	static void StopSpeedCar();
	static void RegainSpeedCar();
};

#endif // !AIKART_H