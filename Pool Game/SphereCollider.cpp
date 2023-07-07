#include "SphereCollider.h"

bool SphereCollider::CollideCheck(Collider* _collider)
{
	//check the collider id to call different functions for different collider types
	if (_collider->GetID() == 0)
	{
		return SphereCollision(_collider);
	}
	else if (_collider->GetID() == 1)
	{
		return AABBCollision(_collider);
	}
	else
	{
		return false;
	}
}

//collision check for sphere collider with sphere collider
bool SphereCollider::SphereCollision(Collider* _sphereCollider)
{
	//calculate the square values for the radius and distance
	float radiusSquare = (radius + _sphereCollider->GetRadius()) * (radius + _sphereCollider->GetRadius());

	glm::vec3 distanceSquare = glm::vec3((_sphereCollider->GetPosition().x - position.x) * (_sphereCollider->GetPosition().x - position.x),
		(_sphereCollider->GetPosition().y - position.y) * (_sphereCollider->GetPosition().y - position.y),
		(_sphereCollider->GetPosition().z - position.z) * (_sphereCollider->GetPosition().z - position.z));

	float distanceAdded = distanceSquare.x + distanceSquare.y + distanceSquare.z;

	//if the radius square value is bigger than the distance square value there is a collision
	if (radiusSquare > distanceAdded)
	{
		float distance = glm::distance(position, _sphereCollider->GetPosition());

		//calculate collision normal, point and penetration depth
		collisionInfo.collisionNormal = glm::normalize(position - _sphereCollider->GetPosition()); //normalise(position - position2)
		collisionInfo.collisionPoint = glm::cross((_sphereCollider->GetPosition() + radius), collisionInfo.collisionNormal); //(position2 + radius) x normal 
		collisionInfo.penetrationDepth = (radius + _sphereCollider->GetRadius() - distance) / 2; //radius + radius - distance

		return true;
	}
	else
	{
		return false;
	}
}

//collision check for sphere collider with AABB collider
bool SphereCollider::AABBCollision(Collider* _boxCollider)
{
	//set the collision point on the box to the position of the sphere collider
	pointOnBox = position;

	//if the sphere's x position is smaller/bigger than the min/max x position of the AABB then set the collision point on the box to its min/max x value
	if (position.x < _boxCollider->GetMinPos().x)
	{
		//if sphere is to the left of the box, set the x value of the point on box to the AABB's min x position
		pointOnBox = glm::vec3(_boxCollider->GetMinPos().x, pointOnBox.y, pointOnBox.z);
	}
	if (position.x > _boxCollider->GetMaxPos().x)
	{
		//if sphere is to the right of the box, set the x value of the point on box to the AABB's max x position
		pointOnBox = glm::vec3(_boxCollider->GetMaxPos().x, pointOnBox.y, pointOnBox.z);
	}

	//if the sphere's y position is smaller/bigger than the min/max y position of the AABB then set the collision point on the box to its min/max y value
	if (position.y < _boxCollider->GetMinPos().y)
	{
		//if sphere is below the box, set the y value of the point on box to the AABB's min y position
		pointOnBox = glm::vec3(pointOnBox.x, _boxCollider->GetMinPos().y, pointOnBox.z);
	}
	if (position.y > _boxCollider->GetMaxPos().y)
	{
		//if sphere is above the box, set the y value of the point on box to the AABB's max y position
		pointOnBox = glm::vec3(pointOnBox.x, _boxCollider->GetMaxPos().y, pointOnBox.z);
	}

	//if the sphere's z position is smaller/bigger than the min/max z position of the AABB then set the collision point on the box to its min/max z value
	if (position.z < _boxCollider->GetMinPos().z)
	{
		//if sphere is in front of the box, set the z value of the point on box to the AABB's min z position
		pointOnBox = glm::vec3(pointOnBox.x, pointOnBox.y, _boxCollider->GetMinPos().z);
	}
	if (position.z > _boxCollider->GetMaxPos().z)
	{
		//if sphere is behind the box, set the z value of the point on box to the AABB's max z position
		pointOnBox = glm::vec3(pointOnBox.x, pointOnBox.y, _boxCollider->GetMaxPos().z);
	}


	//calculate the square values for the radius and distance
	float radiusSquare = radius * radius;

	glm::vec3 distanceSquare = glm::vec3((pointOnBox.x - position.x) * (pointOnBox.x - position.x),
		(pointOnBox.y - position.y) * (pointOnBox.y - position.y),
		(pointOnBox.z - position.z) * (pointOnBox.z - position.z));

	float distanceAdded = distanceSquare.x + distanceSquare.y + distanceSquare.z;

	//if the radius square value is bigger than the distance square value there is a collision
	if (radiusSquare > distanceAdded)
	{
		float distance = glm::distance(position, pointOnBox);

		//calculate collision normal, point and penetration depth
		collisionInfo.collisionNormal = glm::normalize(position - pointOnBox); //normalise(position - position2)
		collisionInfo.collisionPoint = pointOnBox;
		collisionInfo.penetrationDepth = radius - distance; //radius + radius - distance

		return true;
	}
	else
	{
		return false;
	}
}


SphereCollider::SphereCollider(glm::vec3 _pos, int _id, float _radius) : Collider(_pos, _id, _radius)
{

}

SphereCollider::~SphereCollider()
{
}