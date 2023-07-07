#include "Sphere.h"

void Sphere::Draw()
{
	//draw model on screen
	model->Draw();
}

Sphere::Sphere(float _mass, glm::vec3 _pos, float _speed, float _radius, const char* _name) : GameObject(_mass, _pos, _speed, _radius, _name)
{

}

Sphere::~Sphere()
{

}