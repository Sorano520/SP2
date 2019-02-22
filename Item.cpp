#include "Item.h"

item::item()
{
	item_no = 0;
}

item::~item()
{

}

void item::purpose(int no)
{
	switch (no)
	{
	case 0:
		//speed up
		Vehicle::SpeedZCoefficientUp = 1.1;
		break;
	case 1:
		//slow down
		AIKart::ReduceSpeedCar();
		break;
	case 2:
		//stop
		AIKart::StopSpeedCar();
		break;
	//case 3:
	//	//teleport
	//	Vehicle::teleportation = true;
	//	break;
	default:
		break;
	}
}

void item::useitem()
{
	item_no = rand() % 4;
	cout << item_no;
}

void item::getitems()
{
	purpose(item_no);
}

int item::get_item_no()
{
	return item_no;
}