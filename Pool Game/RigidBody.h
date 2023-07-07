#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <string>
#include <cmath>

class RigidBody
{
private:
	float mass;
	float friction;

	glm::vec3 position;

	//linear movement variables
	glm::vec3 linearAcceleration;
	glm::vec3 linearVelocity;

	glm::vec3 nextPosition;
	glm::vec3 nextLinearVelocity;

	//force variables
	glm::vec3 totalLinearForce;
	glm::vec3 totalTorque;
	glm::vec3 forcePosition;

	//angular movement variables
	glm::vec3 angularAcceleration;
	glm::vec3 angularVelocity;
	glm::vec3 orientation;

	glm::mat3 inertiaMat;
	glm::mat3 inverseInertiaMat;

	glm::vec3 nextOrientation;
	glm::vec3 nextAngularVelocity;

	//movement calculation functions
	void LinearCalculations(float);
	void AngularCalculations(float);

public:
	//calculate object movement
	void Update(float);

	//reset object position, velocity etc (for resetting cue ball)
	void ResetObject(glm::vec3);

	//reset all forces
	void ResetForces();

	//add forces/torque to object
	void AddForce(glm::vec3 _force, glm::vec3 _forcePosition = glm::vec3(0,0,0));
	void AddTorque(glm::vec3, glm::vec3);

	//get and set functions for variable values
	float GetMass();
	glm::mat3 GetInverseInertia();
	glm::vec3 GetPosition();
	glm::vec3 GetLinearVelocity();
	glm::vec3 GetLinearAcceleration();
	glm::vec3 GetOrientation();
	glm::vec3 GetAngularVelocity();
	glm::vec3 GetAngularAcceleration();

	void SetPosition(glm::vec3);
	void SetLinearVelocity(float, glm::vec3);
	void SetAngularVelocity(float, glm::vec3, glm::vec3);

	//cube rigidbody constructor
	RigidBody(float, glm::vec3, float, float, float);
	//sphere rigidbody constructor
	RigidBody(float, glm::vec3, float);
	//destructor
	~RigidBody();
};

