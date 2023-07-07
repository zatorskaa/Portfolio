#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <iostream>

#include "Collider.h"

//sphere collider class inherits from collider class
class SphereCollider : public Collider
{
public:
	//collision check function
	bool CollideCheck(Collider*);
	//collision check for sphere collider with sphere collider function
	bool SphereCollision(Collider*);
	//collision check for sphere collider with AABB collider function
	bool AABBCollision(Collider*);

	//constructor
	SphereCollider(glm::vec3, int, float);
	//destructor
	~SphereCollider();
};

