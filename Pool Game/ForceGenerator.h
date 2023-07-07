#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

#include "GameObject.h"

//class to add constant forces to objects
class ForceGenerator
{
private:
	//vector for objects that have gravity
	std::vector<GameObject*> gravityObjects;

public:
	//function to add forces to objects
	void Update();

	//function to add gameobjects to vector for gravity
	void AddGravityObject(GameObject*);

	//constructor
	ForceGenerator();
	//destructor
	~ForceGenerator();
};

