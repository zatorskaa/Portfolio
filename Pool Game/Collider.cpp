#include "Collider.h"

float Collider::CalculateLinearImpulse(glm::vec3 _vel1, glm::vec3 _vel2, float _ceor, glm::vec3 _normal, float _mass1, float _mass2)
{
	//J = -((v(1-) - v(2-)) . n) * (1 + E)
	//	/ n . n * (1/m(1) + 1/m(2))
	linearImpulse = (-(glm::dot((_vel1 - _vel2), _normal)) * (1 + _ceor))
		/ (glm::dot(_normal, _normal) * ((1 / _mass1) + (1 / _mass2)));

	return linearImpulse;
}

float Collider::CalculateAngularImpulse(glm::vec3 _vel1, glm::vec3 _vel2, float _ceor, glm::vec3 _normal, float _mass1, float _mass2, glm::mat3 _inertia1, glm::mat3 _inertia2, glm::vec3 _distance1, glm::vec3 _distance2)
{
	//J = -((v(1-) - v(2-)) . n) * (1 + E)
	//  / (1/m(1) + 1/m(2)) + (n . ((I(1)^-1 * (r(1) * x n)) x r(1))) + (n . ((I(2)^-1 * (r(2) * x n)) x r(2)))
	angularImpluse = (-(glm::dot((_vel1 - _vel2), _normal)) * (1 + _ceor))
		/ ((1 / _mass1) + (1 / _mass2) +
			glm::dot(_normal, glm::cross(_inertia1 * (glm::cross(_distance1, _normal)), _distance1)) +
			glm::dot(_normal, glm::cross(_inertia2 * (glm::cross(_distance2, _normal)), _distance2)));

	return angularImpluse;
}


int Collider::GetID()
{
	return colliderID;
}

float Collider::GetRadius()
{
	return radius;
}

glm::vec3 Collider::GetPosition()
{
	return position;
}

void Collider::SetPosition(glm::vec3 _pos)
{
	position = _pos;
}

glm::vec3 Collider::GetMinPos()
{
	return minPos;
}

glm::vec3 Collider::GetMaxPos()
{
	return maxPos;
}

glm::vec3 Collider::GetPointOnBox()
{
	return pointOnBox;
}


Collider::Collider(glm::vec3 _pos, int _id, float _radius)
{
	//initialise variables
	position = _pos;
	colliderID = _id;
	radius = _radius;
	height = 0;
	width = 0;
	length = 0;

	linearImpulse = 0;
	angularImpluse = 0;

	collisionInfo.collisionNormal = glm::vec3(0);
	collisionInfo.collisionPoint = glm::vec3(0);
	collisionInfo.penetrationDepth = 0;
}

Collider::Collider(glm::vec3 _pos, int _id, float _length, float _height, float _width)
{
	//initialise variables
	position = _pos;
	colliderID = _id;
	radius = 0;
	height = _height;
	width = _width;
	length = _length;

	//calculate min and max positions of box (y position is min position, not center because the object origin is at the bottom of the model)
	minPos = glm::vec3(position.x - (length / 2), position.y, position.z - (width / 2));
	maxPos = glm::vec3(position.x + (length / 2), position.y + height, position.z + (width / 2));

	linearImpulse = 0;
	angularImpluse = 0;

	collisionInfo.collisionNormal = glm::vec3(0);
	collisionInfo.collisionPoint = glm::vec3(0);
	collisionInfo.penetrationDepth = 0;
}

Collider::~Collider()
{
}