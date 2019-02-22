#ifndef TRACKMAKER_H
#define TRACKMAKER_H

#include <string>
#include <fstream>
#include <iostream>
#include "Vector3.h"
#include "TrackObject.h"

using namespace std;

class TrackMaker
{
public:
	TrackMaker();
	~TrackMaker();
	void Init(string);
	string* getMapInfo();
	float* getRotateValue();
	TrackObject* getTrackObject();
	int getNumofPiece();
	int getType(int);
private:
	string* MapInfo;
	float* RotateValue;
	TrackObject* Object;
	int NumofPiece;
};

#endif // !TRACKMAKER_H