//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "Application.h"

#include "SceneStadium.h"
#include "IN_GAME.h"
#include "Mainmenu.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

										   //Define an error callback


static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
	scene[0] = new Mainmenu;
	scene[1] = new Mainmenu;
	scene[2] = new SceneText;
	screen_no = 0;
}

Application::~Application()
{
}

// New to Scene 2
void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

void Application::Init()
{

	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
												   //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


																   //Create a window and create its OpenGL context
	m_window = glfwCreateWindow(1000, 1000, "Assignment 2", NULL, NULL);

	//New to scene 2
	glfwSetWindowSizeCallback(m_window, resize_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
							 //Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

}

void Application::Run()
{
	//Main Loop
	bool quit_game = false;
	bool next = false;
	Music(screen_no);

	scene[screen_no]->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		scene[screen_no]->Update(m_timer.getElapsedTime());
		scene[screen_no]->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);// Frame rate limiter. Limits each frame to a specified time in ms.
		quit_game = scene[screen_no]->prev_state();
		next = scene[screen_no]->next_state();
		if (IsKeyPressed(VK_NUMPAD1) == true)
		{
			screen_no = 0;
			Run();
		}
		else if (IsKeyPressed(VK_NUMPAD2) == true)
		{
			screen_no = 1;
			Run();
		}
		else if (next == true)
		{
			screen_no = 2;
			Run();
		}
		if (quit_game == true)
		{
			break;
		}
	} //Check if the ESC key had been pressed or if the window had been closed
	scene[screen_no]->Exit();
	/*delete[] scene;*/
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

void Application::Music(int game_state)
{
	switch (game_state)
	{
	case (0):
		mciSendString("play Music/mainmenu.wav", NULL, 0, NULL);
		mciSendString("stop Music/in_game_selection.wav", NULL, 0, NULL);
		mciSendString("stop Music/game.wav", NULL, 0, NULL);
		mciSendString("stop Music/car_sound.wav", NULL, 0, NULL);
		break;
	case (1):
		mciSendString("play Music/in_game_selection.wav", NULL, 0, NULL);
		mciSendString("stop Music/mainmenu.wav", NULL, 0, NULL);
		mciSendString("stop Music/game.wav", NULL, 0, NULL);
		mciSendString("stop Music/car_sound.wav", NULL, 0, NULL);
		break;
	case (2):
		mciSendString("play Music/game.wav", NULL, 0, NULL);
		mciSendString("stop Music/mainmenu.wav", NULL, 0, NULL);
		mciSendString("stop Music/in_game_selection.wav", NULL, 0, NULL);
		break;
	default:
		mciSendString("play Music/game.wav", NULL, 0, NULL);
		break;
	}
}