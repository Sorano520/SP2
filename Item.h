#pragma once
#include<iostream>
#include <stdlib.h>
#include <time.h>
#include "Vehicle.h"
#include "AIKart.h"

using namespace std;

class item
{
public:
	item();
	~item();
	void purpose(int);
	void getitems();
	void useitem();
	int get_item_no();
private:
	int item_no;
};