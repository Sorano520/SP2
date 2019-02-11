#include "CameraFPS.h"
#include "Application.h"
#include "Mtx44.h"

CameraFPS::CameraFPS()
{
	Reset();
}

CameraFPS::~CameraFPS()
{
}

void CameraFPS::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->forward = pos;
	this->up = target;
	this->right = up;
}

void CameraFPS::Reset()
{
	forward.Set(1, 0, 0);
	up.Set(0, 0, 0);
	right.Set(0, 1, 0);
}

void CameraFPS::Update(double dt)
{
	static const float CAMERA_SPEED = 20.f;
	if (Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A'))
	{
		forward.x -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if (Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D'))
	{
		forward.x += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W'))
	{
		forward.y += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S'))
	{
		forward.y -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
}