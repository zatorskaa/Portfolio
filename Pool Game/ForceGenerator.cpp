#include "ForceGenerator.h"

void ForceGenerator::Update()
{
	for (int i = 0; i < gravityObjects.size(); i++)
	{
		//add gravity force to objects in vector
		gravityObjects[i]->rigidBody->AddForce(glm::vec3(0.0f, -9.8f, 0.0f) * gravityObjects[i]->rigidBody->GetMass());
	}
}

void ForceGenerator::AddGravityObject(GameObject* _object)
{
	//add objects to vector for gravity
	gravityObjects.push_back(_object);
}

ForceGenerator::ForceGenerator()
{
}

ForceGenerator::~ForceGenerator()
{
}