#include "RigidBody.h"

//calculations for linear velocity and position
void RigidBody::LinearCalculations(float _deltaTime)
{
	//semi-implicit euler's method
	linearAcceleration = totalLinearForce / mass; //a = F/m - calculate acceleration

	nextLinearVelocity = linearVelocity + linearAcceleration * _deltaTime; //v(t+dt) = v(t) + a(t)*dt - calculate velocity
	linearVelocity = nextLinearVelocity;

	linearVelocity *= pow(friction, _deltaTime); //add friction/drag

	nextPosition = position + linearVelocity * _deltaTime; //s(t+dt) = s(t) + v(dt)*dt - calculate position
	position = nextPosition;
}

//calculations for angular velocity and orientation
void RigidBody::AngularCalculations(float _deltaTime)
{
	//semi-implicit euler's method
	angularAcceleration = inverseInertiaMat * totalTorque; //a = I^-1 * t - calculate acceleration (inverse of inertia is calculated in constructor)

	nextAngularVelocity = angularVelocity + angularAcceleration * _deltaTime; //w(t+dt) = w(t) + a(t)*dt - calculate velocity
	angularVelocity = nextAngularVelocity;

	angularVelocity *= pow(friction, _deltaTime); //add friction/drag

	nextOrientation = orientation + angularVelocity * _deltaTime; //0(t+dt) = 0(t) + v(dt)*dt - calculate angles for orientation
	orientation = glm::vec3(fmod(nextOrientation.x, 360), fmod(nextOrientation.y, 360), fmod(nextOrientation.z, 360));
}

void RigidBody::Update(float _deltaTime)
{
	//calculate linear and angular object movement per frame
	LinearCalculations(_deltaTime);
	AngularCalculations(_deltaTime);
}

void RigidBody::ResetObject(glm::vec3 _pos)
{
	//reset all variables for object
	position = _pos;
	
	linearAcceleration = glm::vec3(0, 0, 0);
	linearVelocity = glm::vec3(0, 0, 0);
	totalLinearForce = glm::vec3(0, 0, 0);

	angularAcceleration = glm::vec3(0, 0, 0);
	angularVelocity = glm::vec3(0, 0, 0);
	orientation = glm::vec3(0, 0, 0);
}

void RigidBody::ResetForces()
{
	//set all forces to 0
	totalLinearForce = { 0, 0, 0 };
	totalTorque = { 0, 0, 0 };
}

void RigidBody::AddForce(glm::vec3 _force, glm::vec3 _forcePosition)
{
	//calculate linear force and torque
	totalLinearForce += _force;
	totalTorque += glm::cross(_force, _forcePosition);
}

void RigidBody::AddTorque(glm::vec3 _force, glm::vec3 _forcePosition)
{
	//add rotation without movement (for cue stick)
	totalTorque += glm::cross(_force, _forcePosition);
}


float RigidBody::GetMass()
{
	return mass;
}

glm::mat3 RigidBody::GetInverseInertia()
{
	return inverseInertiaMat;
}

glm::vec3 RigidBody::GetPosition()
{
	return position;
}

glm::vec3 RigidBody::GetLinearVelocity()
{
	return linearVelocity;
}

glm::vec3 RigidBody::GetLinearAcceleration()
{
	return linearAcceleration;
}

glm::vec3 RigidBody::GetOrientation()
{
	return orientation;
}

glm::vec3 RigidBody::GetAngularVelocity()
{
	return angularVelocity;
}

glm::vec3 RigidBody::GetAngularAcceleration()
{
	return angularAcceleration;
}


void RigidBody::SetPosition(glm::vec3 _pos)
{
	position = _pos; //set position of object (for animation)
}

void RigidBody::SetLinearVelocity(float _impulse, glm::vec3 _normal)
{
	//add impulse velocity
	nextLinearVelocity = linearVelocity + ((_impulse / mass) * _normal); //v+ = v- + (J/m * N)
	linearVelocity = nextLinearVelocity;
}

void RigidBody::SetAngularVelocity(float _impulse, glm::vec3 _normal, glm::vec3 _distance)
{
	//add angualr impulse velocity
	nextAngularVelocity = angularVelocity + (inverseInertiaMat * glm::cross(_distance, _impulse * _normal)); //w+ = w- + (I^-1 * (r x JN))
	angularVelocity = nextAngularVelocity;
}


//cube rigidbody constructor
RigidBody::RigidBody(float _mass, glm::vec3 _pos, float _length, float _height, float _width)
{
	//initialise variables
	mass = _mass;
	position = _pos;
	friction = 0.1f;

	linearAcceleration = glm::vec3(0, 0, 0);
	linearVelocity = glm::vec3(0, 0, 0);
	totalLinearForce = glm::vec3(0, 0, 0);

	angularAcceleration = glm::vec3(0, 0, 0);
	angularVelocity = glm::vec3(0, 0, 0);
	orientation = glm::vec3(0, 0, 0);

	//calculate inverse inertia
	inertiaMat = 
	{
		_mass * ((_height * _height) + (_width * _width)) / 12, 0, 0,
		0, _mass * ((_length * _length) + (_width * _width)) / 12, 0,
		0, 0, _mass * ((_height * _height) + (_length * _length)) / 12
	};

	inverseInertiaMat = glm::inverse(inertiaMat);
}

//sphere rigidbody constructor
RigidBody::RigidBody(float _mass, glm::vec3 _pos, float _radius)
{
	//initialise variables
	mass = _mass;
	position = _pos;
	friction = 0.7f;

	linearAcceleration = glm::vec3(0, 0, 0);
	linearVelocity = glm::vec3(0, 0, 0);
	totalLinearForce = glm::vec3(0, 0, 0);

	angularAcceleration = glm::vec3(0, 0, 0);
	angularVelocity = glm::vec3(0, 0, 0);
	orientation = glm::vec3(0, 0, 0);

	//calculate inverse inertia
	inertiaMat =
	{
		0.4 * _mass * (_radius * _radius), 0, 0,
		0, 0.4 * _mass * (_radius * _radius), 0,
		0, 0, 0.4 * _mass * (_radius * _radius)
	};

	inverseInertiaMat = glm::inverse(inertiaMat);
}

RigidBody::~RigidBody()
{
}
