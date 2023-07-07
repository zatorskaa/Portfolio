#include "Cube.h"

void Cube::Draw()
{
	//draw model on screen
	model->Draw();
}

Cube::Cube(float _mass, glm::vec3 _pos, float _speed, float _length, float _height, float _width, const char* _name, int _id) : GameObject(_mass, _pos, _speed, _length, _height, _width, _name, _id)
{
	
}

Cube::~Cube()
{
	
}
