#include "GameObject.h"

//key maps
std::map<char, bool> GameObject::keys;
std::map<int, bool> GameObject::specialKeys;

//update object's rigidbody and collider
void GameObject::Update(float _deltaTime)
{
	//call update function in rigidbody class
	rigidBody->Update(_deltaTime);
	//update collider position
	collider->SetPosition(rigidBody->GetPosition());
}

void GameObject::SetCamera(int _camNum)
{
	cameraNumber = _camNum;
}

//cube object constructor
GameObject::GameObject(float _mass, glm::vec3 _pos, float _speed, float _length, float _height, float _width, const char* _name, int _id)
{
	//set variable value
	speed = _speed;
	cameraNumber = 1;

	//pass values to rigidbody constructor
	rigidBody = new RigidBody(_mass, _pos, _length, _height, _width);

	//pass values to model constructor
	model = new Model(_name, _pos);

	if (_id == 0)
	{
		//pass values to sphere collider constructor
		collider = new SphereCollider(_pos, _id, 0.06f); //sphere collider for end of cue
	}
	else
	{
		//pass values to AABB collider constructor
		collider = new AABBCollider(_pos, 1, _length, _height, _width); //rest of cube objects have AABB colliders
	}

}

//sphere object constructor
GameObject::GameObject(float _mass, glm::vec3 _pos, float _speed, float _radius, const char* _name)
{
	//set variable value
	speed = _speed;
	cameraNumber = 1;

	//pass values to rigidbody constructor
	rigidBody = new RigidBody(_mass, _pos, _radius);

	//pass values to model constructor
	model = new Model(_name, _pos);

	//pass values to sphere collider constructor
	collider = new SphereCollider(_pos, 0, _radius);
}

GameObject::~GameObject()
{
	//delete pointers when game objects is deleted
	delete rigidBody;
	delete model;
	delete collider;
}