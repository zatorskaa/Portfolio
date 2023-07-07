#include "CueStick.h"

//update object's rigidbody and collider
void CueStick::Update(float _deltaTime)
{
	//check for key inputs
	CheckForInput();

	//call update function in rigidbody class
	rigidBody->Update(_deltaTime);
	//update collider position
	collider->SetPosition(rigidBody->GetPosition());
}

//check for key inputs to move cue stick
void CueStick::CheckForInput()
{
	//change cue stick speed
	if (GameObject::keys['t'] == true)
	{
		speed = 0.5f;
	}
	if (GameObject::keys['y'] == true)
	{
		speed = 1.0f;
	}

	if (cameraNumber == 1 || cameraNumber == 3 || cameraNumber == 4) //front/top/cue ball camera controls
	{
		if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		{
			//move backwards
			rigidBody->AddForce(glm::vec3(0.0f, 0.0f, -20.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		{
			//move forwards
			rigidBody->AddForce(glm::vec3(0.0f, 0.0f, 20.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		{
			//move left
			rigidBody->AddForce(glm::vec3(-20.0f, 0.0f, 0.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		{
			//move right
			rigidBody->AddForce(glm::vec3(20.0f, 0.0f, 0.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::keys['w'] == true)
		{
			//move up
			rigidBody->AddForce(glm::vec3(0.0f, 20.0f, 0.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::keys['s'] == true)
		{
			//move down
			rigidBody->AddForce(glm::vec3(0.0f, -20.0f, 0.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::keys['a'] == true)
		{
			//rotate around y axis
			rigidBody->AddTorque(glm::vec3(0.0f, 0.0f, 40.0f) * rigidBody->GetMass() * speed, glm::vec3(1.2f * 5, 0.0f, 0.0f));
		}
		if (GameObject::keys['d'] == true)
		{
			//rotate around y axis
			rigidBody->AddTorque(glm::vec3(0.0f, 0.0f, -40.0f) * rigidBody->GetMass() * speed, glm::vec3(1.2f * 5, 0.0f, 0.0f));
		}
	}
	else if (cameraNumber == 2) //back camera controls
	{
		if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		{
			//move forwards
			rigidBody->AddForce(glm::vec3(0.0f, 0.0f, 20.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		{
			//move backwards
			rigidBody->AddForce(glm::vec3(0.0f, 0.0f, -20.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		{
			//move right
			rigidBody->AddForce(glm::vec3(20.0f, 0.0f, 0.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		{
			//move left
			rigidBody->AddForce(glm::vec3(-20.0f, 0.0f, 0.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::keys['w'] == true)
		{
			//move up
			rigidBody->AddForce(glm::vec3(0.0f, 20.0f, 0.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::keys['s'] == true)
		{
			//move down
			rigidBody->AddForce(glm::vec3(0.0f, -20.0f, 0.0f) * rigidBody->GetMass() * speed);
		}
		if (GameObject::keys['a'] == true)
		{
			//rotate around y axis
			rigidBody->AddTorque(glm::vec3(0.0f, 0.0f, 40.0f) * rigidBody->GetMass() * speed, glm::vec3(1.2f * 5, 0.0f, 0.0f));
		}
		if (GameObject::keys['d'] == true)
		{
			//rotate around y axis
			rigidBody->AddTorque(glm::vec3(0.0f, 0.0f, -40.0f) * rigidBody->GetMass() * speed, glm::vec3(1.2f * 5, 0.0f, 0.0f));
		}
	}
}


CueStick::CueStick(float _mass, glm::vec3 _pos, float _speed, float _length, float _height, float _width, const char* _name, int _id) : Cube(_mass, _pos, _speed, _length, _height, _width, _name, _id)
{

}

CueStick::~CueStick()
{
}
