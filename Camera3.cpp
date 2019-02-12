#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	verticalvalue = 0;
	horizontalvalue = 0;
	Shoot = false;
	OtherCam = false;
	speed = speedright = 0;
}

void Camera3::Update(double dt, Vehicle& Car)
{
	float SKYBOXSIZE = 1000.f;
	float carspeed = 3;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	static const float CAMERA_SPEED = 0.2f;
	if (position.x < (SKYBOXSIZE - 1.f) / 2.f && position.x > -(SKYBOXSIZE - 1.f) / 2.f &&
		position.y < (SKYBOXSIZE - 1.f) / 2.f && position.y > -(SKYBOXSIZE - 1.f) / 2 &&
		position.z < (SKYBOXSIZE - 1.f) / 2.f && position.z > -(SKYBOXSIZE - 1.f) / 2.f)
	{
		if (Shoot && !OtherCam) // SHOOTING OF BALL
		{
			if (Application::IsKeyPressed(VK_UP)) // LOOK UP
			{
				Mtx44 rotation;
				float pitch = (float)(-CAMERA_SPEED * dt);
				if (verticalvalue >= -50)
				{
					verticalvalue = verticalvalue + pitch;
					rotation.SetToRotation(pitch, 1, 0, 0);
					view = rotation * view;
					target = position + view;
				}
			}
			if (Application::IsKeyPressed(VK_DOWN)) // LOOK DOWN
			{
				float pitch = (float)(CAMERA_SPEED * dt);
				Mtx44 rotation;
				if (verticalvalue <= 50)
				{
					verticalvalue = verticalvalue + pitch;
					rotation.SetToRotation(pitch, 1, 0, 0);
					view = rotation * view;
					target = position + view;
				}
			}
			if (Application::IsKeyPressed(VK_LEFT)) // LOOK LEFT
			{
				float yaw = (float)(CAMERA_SPEED * dt);
				Mtx44 rotation;
				if (horizontalvalue <= 50)
				{
					horizontalvalue = horizontalvalue + yaw * 25.f;
					rotation.SetToRotation(yaw, 0, 1, 0);
					view = rotation * view;
					target = position + view;
				}
			}
			if (Application::IsKeyPressed(VK_RIGHT)) // LOOK RIGHT
			{
				float yaw = (float)(-CAMERA_SPEED * dt);
				Mtx44 rotation;
				if (horizontalvalue >= -50)
				{
					horizontalvalue = horizontalvalue + yaw * 25.f;
					rotation.SetToRotation(yaw, 0, 1, 0);
					view = rotation * view;
					target = position + view;
				}
			}
		}
		else if (OtherCam) // DIFFERENT CAMERA
		{
			if (Application::IsKeyPressed(VK_LEFT)) // LOOK LEFT
			{
				float yaw = (float)(CAMERA_SPEED * dt)* 25.f;
				Mtx44 rotation;
				rotation.SetToRotation(yaw, 0, 1, 0);
				view = rotation * view;
				target = position + view;
			}
			if (Application::IsKeyPressed(VK_RIGHT)) // LOOK RIGHT
			{
				float yaw = (float)(-CAMERA_SPEED * dt)* 25.f;
				Mtx44 rotation;
				rotation.SetToRotation(yaw, 0, 1, 0);
				view = rotation * view;
				target = position + view;
			}
		}
		else
		{
			horizontalvalue = verticalvalue = 0.f;
			if (Application::IsKeyPressed('A')) // MOVE LEFT
			{
				if (speedright >= -3)
				{
					speedright -= (CAMERA_SPEED * dt);
				}
			}
			if (Application::IsKeyPressed('D')) // MORE RIGHT
			{
				if (speedright <= carspeed)
				{
					speedright += (CAMERA_SPEED * dt);
				}
			}
			if (Application::IsKeyPressed('W')) // MOVE UP
			{
				if (speed <= carspeed)
				{
					speed += (CAMERA_SPEED * dt);
				}
			}
			if (Application::IsKeyPressed('S')) // MOVE BACK
			{
				if (speed >= -carspeed)
				{
					speed -= (CAMERA_SPEED * dt);
				}
			}
			if (Application::IsKeyPressed('Z')) // MOVE UP
			{
				position = position + up * (CAMERA_SPEED * dt);
				target = position + view;
			}
			if (Application::IsKeyPressed('X')) // MOVE DOWN
			{
				position = position - up * (CAMERA_SPEED * dt);
				target = position + view;
			}
			//if (Application::IsKeyPressed(VK_LEFT)) // TURN LEFT
			//{
			//	float yaw = (float)(CAMERA_SPEED * dt)* 25.f;
			//	Mtx44 rotation;
			//	rotation.SetToRotation(yaw, 0, 1, 0);
			//	view = rotation * view;
			//	target = position + view;
			//	if (speed > 0)
			//	{
			//		speed -= (CAMERA_SPEED * dt) / 25.f;
			//	}
			//}
			//if (Application::IsKeyPressed(VK_RIGHT)) // TURN RIGHT
			//{
			//	float yaw = (float)(-CAMERA_SPEED * dt)* 25.f ;
			//	Mtx44 rotation;
			//	rotation.SetToRotation(yaw, 0, 1, 0);
			//	view = rotation * view;
			//	target = position + view;
			//	if (speed > 0)
			//	{
			//		speed -= (CAMERA_SPEED * dt) / 25.f;
			//	}
			//}
			if (Application::IsKeyPressed('R')) // RESET
			{
				Reset();
			}
			position = position + right * speedright;
			if (speed > 0)
			{
				speed -= (CAMERA_SPEED * dt) / 25.f;
			}
			position = position + view * speed;
			target = position + view;
		}
	}
	else
	{
		Reset();
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}