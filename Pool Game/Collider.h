#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <iostream>

#include "Collision.h"

class Collider
{
protected:
	//collider position
	glm::vec3 position;

	//sphere collider radius
	float radius;

	//AABB collider size
	float length;
	float height;
	float width;

	//AABB collider min and max positions, and collision point on box
	glm::vec3 minPos;
	glm::vec3 maxPos;
	glm::vec3 pointOnBox;

	//linear and angular impulse
	float linearImpulse;
	float angularImpluse;

	//id number to identify collideer type
	int colliderID; //0 = sphere, 1 = AABB

public:
	//struct coaintaining collision info (normal, collision point, penetration depth)
	Collision collisionInfo;
	
	//function to check for collision with other objects
	virtual bool CollideCheck(Collider*) = 0;

	//functions to calculate linear & angular impulse
	float CalculateLinearImpulse(glm::vec3, glm::vec3, float, glm::vec3, float, float);
	float CalculateAngularImpulse(glm::vec3, glm::vec3, float, glm::vec3, float, float, glm::mat3, glm::mat3, glm::vec3, glm::vec3);

	//get and set functions for variables
	int GetID();
	float GetRadius();

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3);

	glm::vec3 GetMinPos();
	glm::vec3 GetMaxPos();
	glm::vec3 GetPointOnBox();

	//sphere collider constructor
	Collider(glm::vec3, int, float);
	//AABB collider constructor
	Collider(glm::vec3, int, float, float, float);
	//destructor
	~Collider();
};

