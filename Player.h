#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Vehicle.h"
#include "Item.h"

class Player : public Vehicle
{
public:
	Player();
	int CheckCar();
	void Update(double);
	void use_item_effect();
	void reduce_item_effect();
	//void teleport(Vehicle& Object);
	void get_item_powerups();
	item storage;
private:
	bool Tutorial[10];
	bool SpeedZUP;
	
};

#endif // !AIKART_H