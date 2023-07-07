#include "PhysicsComponent.h"

PhysicsComponent& PhysicsComponent::operator=(const PhysicsComponent& _other)
{
	if (this == &_other)
		return *this;

	PhysicsComponent a(_other);
	return a;
}

Vector2 PhysicsComponent::GetPosition()
{
	//get the current position of the physics body in box2d
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;
	return position;
}

float PhysicsComponent::GetRotation()
{
	//get the current rotation of the physics body in box2d
	rotation = body->GetAngle() * (180 / pi);
	return rotation;
}

void PhysicsComponent::SetTransform(Vector2 _position, float _rotation)
{
	//set the position and rotation of the physics body
	body->SetTransform(b2Vec2(_position.x, _position.y), _rotation);
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;
	rotation = body->GetAngle() * (180 / pi);
}

void PhysicsComponent::Update()
{
	//reset the velocity of the object in box2d
	body->SetLinearVelocity(b2Vec2(0, 0));
}

void PhysicsComponent::Move(Vector2 _vel)
{
	//set the velocity of the object in box2d
	body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x + _vel.x, body->GetLinearVelocity().y + _vel.y));
}
