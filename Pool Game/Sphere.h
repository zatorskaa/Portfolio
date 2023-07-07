#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "SphereCollider.h"

//sphere class inherits from game object class
class Sphere : public GameObject
{
public:
	//draw model on screen
	void Draw();

	//constructor
	Sphere(float, glm::vec3, float, float, const char*);
	//destructor
	~Sphere();
};

