#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <map>

class Camera
{
private:
	//final camera position to pass to matrix
	glm::vec3 cameraPosition;
	//which camera is currently active
	int cameraNumber;

	//forward direction of camera after rotations
	glm::vec3 cameraForward;
	//eye position of camera after rotations
	glm::vec3 eye;

	//rotation around y axis
	float cameraYaw;
	//rotation around x axis
	float cameraPitch;

public:
	//key maps
	static std::map<char, bool> keys;
	static std::map<int, bool> specialKeys;

	//functions for moving the camera and updating its position based on key inputs
	void MoveCamera();
	void UpdateCamera();

	//get ans set functions for variables
	glm::vec3 GetPosition();
	float GetNumber();

	//constructor
	Camera();
	//destructor
	~Camera();
};

