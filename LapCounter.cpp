#include "LapCounter.h"
#include "Vehicle.h"

int LapCounter::LapNumber = 3;
int LapCounter::TotalCheckPoint = 0;
Range* LapCounter::CheckPoint = nullptr;

LapCounter::LapCounter()
{
	CurrentLap = 1;
	CurrentCheckPoint = 1;
}

LapCounter::~LapCounter()
{
}

void LapCounter::SetRange(TrackMaker& Check)
{
	TotalCheckPoint = Check.getNumofPiece();
	CheckPoint = new Range[TotalCheckPoint];
	for (int i = 0; i < TotalCheckPoint; i++)
	{
		CheckPoint[i].Center = Check.getTrackObject()[i].getPosition();
		CheckPoint[i].RangeX[0] = Check.getTrackObject()[i].getPosition().x + Check.getTrackObject()[i].getXDist();
		CheckPoint[i].RangeX[1] = Check.getTrackObject()[i].getPosition().x - Check.getTrackObject()[i].getXDist();
		CheckPoint[i].RangeZ[0] = Check.getTrackObject()[i].getPosition().z + Check.getTrackObject()[i].getZDist();
		CheckPoint[i].RangeZ[1] = Check.getTrackObject()[i].getPosition().z - Check.getTrackObject()[i].getZDist();
		CheckPoint[i].RotateValue = Check.getRotateValue()[i];
		cout << "LAP CHECK" << endl;
		cout << "Index " << i << endl;
		cout << "X0: " << CheckPoint[i].RangeX[0] << " X1: " << CheckPoint[i].RangeX[1] << endl;
		cout << "Z0: " << CheckPoint[i].RangeZ[0] << " Z1: " << CheckPoint[i].RangeZ[1] << endl;
	}
}

Range* LapCounter::getRange()
{
	return CheckPoint;
}

int LapCounter::getCurrentCheckPoint()
{
	return CurrentCheckPoint;
}

int LapCounter::getCurrentLap()
{
	return CurrentLap;
}

int LapCounter::getLapNumber()
{
	return LapNumber;
}

int LapCounter::getTotalCheckPoint()
{
	return TotalCheckPoint;
}

void LapCounter::setCurrentCheckPoint(int Num)
{
	CurrentCheckPoint = Num;
}

void LapCounter::addCurrentCheckPoint(int Num)
{
	CurrentCheckPoint += Num;
}

void LapCounter::addCurrentLap()
{
	CurrentLap++;
}

void LapCounter::setTotalCheckPoint(int Num)
{
	TotalCheckPoint = Num;
}