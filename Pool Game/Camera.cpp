#include "Camera.h"

std::map<char, bool> Camera::keys;
std::map<int, bool> Camera::specialKeys;


void Camera::MoveCamera()
{
	//change camera position based on key inputs
	if (Camera::keys['j'] == true)
	{
		if (cameraNumber == 1) //front cam
		{
			if (cameraPosition.x > -8)
			{
				//move front cam left
				cameraPosition.x -= 0.5; 
			}
		}
		else if (cameraNumber == 2) //back cam
		{
			if (cameraPosition.x < 8)
			{
				//move back cam left
				cameraPosition.x += 0.5; 
			}
		}
		else if (cameraNumber == 4) //cue ball cam
		{
			//rotate cue ball camera around the cue ball by 5 degrees
			cameraYaw -= 5;

			//update camera position based on rotation
			UpdateCamera();
		}
	}
	if (Camera::keys['l'] == true)
	{
		if (cameraNumber == 1) //front cam
		{
			if (cameraPosition.x < 8)
			{
				//move front cam right
				cameraPosition.x += 0.5;
			}
		}
		else if (cameraNumber == 2) //back cam
		{
			if (cameraPosition.x > -8)
			{
				//move back cam right
				cameraPosition.x -= 0.5;
			}
		}
		else if (cameraNumber == 4)
		{
			//rotate cue ball camera around the cue ball by 5 degrees
			cameraYaw += 5;

			//update camera position based on rotation
			UpdateCamera();
		}
	}
	if (Camera::keys['i'] == true)
	{
		if (cameraNumber == 1) //front cam
		{
			if (cameraPosition.z > -14)
			{
				//move front cam towards table
				cameraPosition.z -= 0.5;
			}
		}
		else if (cameraNumber == 2) //back cam
		{
			if (cameraPosition.z < 14)
			{
				//move back cam towards table
				cameraPosition.z += 0.5; 
			}
		}
	}
	if (Camera::keys['k'] == true)
	{
		if (cameraNumber == 1) //front cam
		{
			if (cameraPosition.z < 5)
			{
				//move front cam away from table
				cameraPosition.z += 0.5;
			}
		}
		else if (cameraNumber == 2) //back cam
		{
			if (cameraPosition.z > -5)
			{
				//move back cam away from table
				cameraPosition.z -= 0.5; 
			}
		}
	}
	if (Camera::keys['u'] == true)
	{
		if (cameraPosition.y > -5)
		{
			//move cam down
			cameraPosition.y -= 0.5;
		}
	}
	if (Camera::keys['o'] == true)
	{
		if (cameraPosition.y < 10)
		{
			//move cam up
			cameraPosition.y += 0.5;
		}
	}

	//change camera position (1 = front, 2 = back, 3 = top, 4 = cue ball)
	if (Camera::keys['1'] == true)
	{
		cameraNumber = 1;
		cameraPosition = glm::vec3(0, 0, 0);
	}
	if (Camera::keys['2'] == true)
	{
		cameraNumber = 2;
		cameraPosition = glm::vec3(0, 0, 0);
	}
	if (Camera::keys['3'] == true)
	{
		cameraNumber = 3;
		cameraPosition = glm::vec3(0, 0, 0);
	}
	if (Camera::keys['4'] == true)
	{
		cameraNumber = 4;
		cameraPosition = glm::vec3(0, 0, 0);
	}
}

void Camera::UpdateCamera()
{
	//calculate the rotations around the axis based on the camera pitch and yaw
	eye.x = glm::cos(glm::radians(cameraPitch)) * -glm::cos(glm::radians(cameraYaw));
	eye.y = glm::sin(glm::radians(cameraPitch));
	eye.z = glm::cos(glm::radians(cameraPitch)) * glm::sin(glm::radians(cameraYaw));

	//normalize eye vector to get a vector for forward direction of camera (direction vector with magnitude of 1)
	cameraForward = glm::normalize(eye);

	//update the camera position with the rotation, keeping the y position the same
	cameraPosition = glm::normalize(cross(cameraForward, glm::vec3(0, 1, 0))) + glm::vec3(0, cameraPosition.y, 0);
}


glm::vec3 Camera::GetPosition()
{
	return cameraPosition;
}

float Camera::GetNumber()
{
	return cameraNumber;
}


Camera::Camera()
{
	//initialise variables
	cameraNumber = 1;
	cameraPosition = glm::vec3(0, 0, 0);

	cameraYaw = 180;
	cameraPitch = 0;
	cameraForward = glm::vec3(0, 0, 0);
	eye = glm::vec3(0, 0, 0);
}

Camera::~Camera()
{
}
