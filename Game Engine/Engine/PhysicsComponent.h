#pragma once

#include <Box2D/Box2D.h>

#include "Common.h"
#include "Component.h"

class PhysicsComponent : public Component
{
public:
	//constructors
	PhysicsComponent(GameObject* _gameObject, Subsystem* _subsystem, Vector2 _position, b2World* _world, Vector2 _size, bool _isDynamic)
		: Component(ComponentType::Physics, _gameObject, _subsystem), world(_world)
	{
		//set up the position and height of the object
		position.x = _position.x;
		position.y = _position.y;
		rotation = 0.0f;

		halfWidth = _size.x * 0.5;
		halfHeight = _size.y * 0.5;
		box.SetAsBox(halfWidth, halfHeight);

		//set the body type to dynamic or static
		if (_isDynamic)
		{
			bodyDef.type = b2_dynamicBody;
		}
		else
		{
			bodyDef.type = b2_staticBody;
		}

		//create the body and fixture in box2d
		bodyDef.allowSleep = false;
		bodyDef.awake = true;
		bodyDef.position.Set(position.x, position.y);

		body = world->CreateBody(&bodyDef);

		fixtureDef.shape = &box;
		fixtureDef.density = 0.3f;
		fixtureDef.friction = 0.0f;

		body->CreateFixture(&fixtureDef);
	};

	PhysicsComponent& operator=(const PhysicsComponent& _other);

	//functions
	Vector2 GetPosition();
	void SetPosition(Vector2 _position) { position = _position; }
	float GetRotation();
	void SetRotation(float _rotation) { rotation = _rotation; }
	void SetTransform(Vector2 _position, float _rotation);

	b2BodyDef* GetB2BodyDef() { return &bodyDef; }
	b2FixtureDef* GetFixtureDef() { return &fixtureDef; }
	void SetBody(b2Body* _body) { body = _body; }

	void Update();
	void Move(Vector2 _position);

private:
	Vector2 position;
	float rotation;

	float halfWidth;
	float halfHeight;
	b2PolygonShape box;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2Body* body;

	b2World* world; //pointer to box2d world created in physics subsystem
};

