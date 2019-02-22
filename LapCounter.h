#ifndef LAPCOUNTER_H
#define LAPCOUNTER_H

#include "Range.h"
#include "TrackMaker.h"

class LapCounter
{
public:
	LapCounter();
	~LapCounter();

	int getCurrentLap();
	int getCurrentCheckPoint();

	void setCurrentCheckPoint(int);
	void setTotalCheckPoint(int);
	void addCurrentCheckPoint(int);
	void addCurrentLap();

	static void SetRange(TrackMaker&);
	static int getLapNumber();
	static int getTotalCheckPoint();
	static Range* getRange();

private:
	int CurrentLap;
	int CurrentCheckPoint;

	static int LapNumber;
	static int TotalCheckPoint;
	static Range* CheckPoint;
};

#endif // !LAPCOUNTER_H