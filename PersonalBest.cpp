#include "PersonalBest.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

PersonalBest::PersonalBest()
{
	BestTime = SecondTime = ThirdTime = 0.0f;
	Time[0] = Time[1] = Time[2] = 0.0f;
}

PersonalBest::~PersonalBest()
{
}

void PersonalBest::Update(double dt)
{
	BestTime = dt;
	SecondTime = dt;
	ThirdTime = dt;
}

void PersonalBest::Print()
{
	string score;
	ifstream myfile("PersonalBest.txt");
	int index = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, score))
		{
			Time[index] = stof(score);
			index++;
		}
		myfile.close();
	}
	else
	{
		cout << "Cant open" << endl;
	}
}

void PersonalBest::TimeCheck()
{
	if (Time[0] < Time[1] && Time[0] < Time[2])
	{
		BestTime = Time[0];
		if (Time[1] < Time[2])
		{
			SecondTime = Time[1];
			ThirdTime = Time[2];
		}
		else
		{
			SecondTime = Time[2];
			ThirdTime = Time[1];
		}
	}
	else if (Time[1] < Time[0] && Time[1] < Time[2])
	{
		BestTime = Time[1];
		if (Time[0] < Time[2])
		{
			SecondTime = Time[0];
			ThirdTime = Time[2];
		}
		else
		{
			SecondTime = Time[2];
			ThirdTime = Time[0];
		}
	}
	else
	{
		BestTime = Time[2];
		if (Time[0] < Time[1])
		{
			SecondTime = Time[0];
			ThirdTime = Time[1];
		}
		else
		{
			SecondTime = Time[1];
			ThirdTime = Time[0];
		}
	}
}