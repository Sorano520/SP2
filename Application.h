#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include <windows.h>
#include <mmsystem.h>
#include "Scene.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	void Music(int);
	static bool IsKeyPressed(unsigned short key);

	Scene *scene[3];
private:

	//Declare a window object
	StopWatch m_timer;
	int screen_no;
};


#endif