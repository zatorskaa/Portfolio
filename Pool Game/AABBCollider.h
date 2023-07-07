#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <iostream>

#include "Collider.h"

//AABB collider class inherits from collider class
class AABBCollider : public Collider
{
public:
	//collision check function
	bool CollideCheck(Collider*);

	//constructor
	AABBCollider(glm::vec3, int, float, float, float);
	//destructor
	~AABBCollider();
};

