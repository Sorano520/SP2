#include "TrackMaker.h"

TrackMaker::TrackMaker()
{
	MapInfo = nullptr;
	RotateValue = nullptr;
	Object = nullptr;
	NumofPiece = 0;
};

TrackMaker::~TrackMaker()
{
	delete[] MapInfo;
	delete[] RotateValue;
	delete[] Object;
	MapInfo = nullptr;
	RotateValue = nullptr;
	Object = nullptr;
};

void TrackMaker::Init(string FileDirectory)
{
	fstream File(FileDirectory);

	string test;

	if (!File.is_open())
	{
		cout << "Map File not found" << endl;
	}
	while (getline(File, test))
	{
		NumofPiece++;
	}

	MapInfo = new string[NumofPiece];
	RotateValue = new float[NumofPiece];
	Object = new TrackObject[NumofPiece];
	NumofPiece = 0; 

	File.clear();
	File.seekg(0, ios::beg);
	while (!File.eof())
	{
		string temp;
		getline(File, temp);
		MapInfo[NumofPiece] = temp;
		NumofPiece++;
	}
	File.close();

	for (int Num = 0; Num < NumofPiece; Num++)
	{
		string temp[4];
		int Index = 0;
		for (int x = 3; x < (int)MapInfo[Num].size(); x++)
		{
			if (MapInfo[Num][x] != ' ')
			{
				temp[Index] += MapInfo[Num][x];
			}
			else if (Index >= 4)
			{
				break;
			}
			else
			{
				Index++;
			}
		}
		Object[Num].Init(stof(temp[0]), stof(temp[1]), stof(temp[2]));
		RotateValue[Num] = stof(temp[3]);
		cout << "TRACKMAKING" << endl;
		cout << "Index " << Num << endl;
		cout << "X: " << Object[Num].getPosition().x << endl;
		cout << "Y: " << Object[Num].getPosition().y << endl;
		cout << "Z: " << Object[Num].getPosition().z << endl;
		cout << endl;
	}
};

string* TrackMaker::getMapInfo()
{
	return MapInfo;
}

int TrackMaker::getNumofPiece()
{
	return NumofPiece;
};

float* TrackMaker::getRotateValue()
{
	return RotateValue;
}

TrackObject* TrackMaker::getTrackObject()
{
	return Object;
}

int TrackMaker::getType(int Index)
{
	switch (MapInfo[Index][0])
	{
	case 'B':
	{
		switch (MapInfo[Index][1])
		{
		case '0':
			return 0;
			break;
		case '1':
			return 1;
			break;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		}
		break;
	}
	case 'S':
	{
		switch (MapInfo[Index][1])
		{
		case '0':
			return 10;
			break;
		case '1':
			return 11;
			break;
		case '2':
			return 12;
			break;
		case '3':
			return 13;
			break;
		}
		break;
	}
	}
	return 20;
}