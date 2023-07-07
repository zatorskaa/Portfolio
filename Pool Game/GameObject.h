#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <map>

#include "RigidBody.h"
#include "Model.h"
#include "SphereCollider.h"
#include "AABBCollider.h"

class GameObject
{
protected:
	//movement speed
	float speed;

	//current camera view
	int cameraNumber;

public:
	//key maps for movement
	static std::map<char, bool> keys;
	static std::map<int, bool> specialKeys;

	//model pointer
	Model* model;
	//rigidbody pointer
	RigidBody* rigidBody;
	//collider pointer
	Collider* collider;


	//draw object in scene
	virtual void Draw() = 0;

	//update gameobject position using rigidbody
	virtual void Update(float);

	//get and set functions for variables values
	virtual void SetCamera(int);

	//cube gameobject constructor
	GameObject(float, glm::vec3, float, float, float, float, const char*, int);
	//sphere gameobject constructor
	GameObject(float, glm::vec3, float, float, const char*);
	//virtual destructor
	virtual ~GameObject();
};

