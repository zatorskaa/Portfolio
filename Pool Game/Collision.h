#pragma once

#include <glm/glm.hpp>

//struct for collision information
struct Collision
{
	glm::vec3 collisionNormal;
	glm::vec3 collisionPoint;
	float penetrationDepth;
};