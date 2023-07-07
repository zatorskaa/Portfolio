#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <string>
#include <iostream>

#include "GameObject.h"

//cube class inherits from game object class
class Cube : public GameObject
{
public:
	//draw model on screen
	void Draw();

	//constructor
	Cube(float, glm::vec3, float, float, float, float, const char*, int);
	//destructor
	~Cube();
};

