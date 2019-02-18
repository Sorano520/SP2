#ifndef PERSONALBEST_H
#define PERSONALBEST_H

#include "timer.h"
#include "Vector3.h"

class PersonalBest : public StopWatch
{
public:
	PersonalBest();
	~PersonalBest();

	void Print();
	void Update(double dt);
	void TimeCheck();
	double Time[3];
	double BestTime;
	double SecondTime;
	double ThirdTime;
private:

};

#endif // !PERSONALBEST_H