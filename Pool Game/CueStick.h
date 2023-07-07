#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <string>
#include <iostream>

#include "Cube.h"

//cue stick class inherits from cube class
class CueStick : public Cube
{
public:
	//update physics
	void Update(float);
	//check for key inputs
	void CheckForInput();

	//constructor
	CueStick(float, glm::vec3, float, float, float, float, const char*, int);
	//destructor
	~CueStick();
};

