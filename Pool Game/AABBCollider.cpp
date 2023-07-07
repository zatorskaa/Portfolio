#include "AABBCollider.h"

//collision check for AABB collider with sphere collider
bool AABBCollider::CollideCheck(Collider* _sphereCollider)
{
	// set the collision point on the box to the position of the sphere collider
	pointOnBox = _sphereCollider->GetPosition();

	//if the sphere's x position is smaller/bigger than the min/max x position of the AABB then set the collision point on the box to its min/max x value
	if (_sphereCollider->GetPosition().x < minPos.x)
	{
		//if sphere is to the left of the box, set the x value of the point on box to the AABB's min x position
		pointOnBox = glm::vec3(minPos.x, pointOnBox.y, pointOnBox.z);
	}
	if (_sphereCollider->GetPosition().x > maxPos.x)
	{
		//if sphere is to the right of the box, set the x value of the point on box to the AABB's max x position
		pointOnBox = glm::vec3(maxPos.x, pointOnBox.y, pointOnBox.z);
	}

	//if the sphere's y position is smaller/bigger than the min/max y position of the AABB then set the collision point on the box to its min/max y value
	if (_sphereCollider->GetPosition().y < minPos.y)
	{
		//if sphere is below the box, set the y value of the point on box to the AABB's min y position
		pointOnBox = glm::vec3(pointOnBox.x, minPos.y, pointOnBox.z);
	}
	if (_sphereCollider->GetPosition().y > maxPos.y)
	{
		//if sphere is above the box, set the y value of the point on box to the AABB's max y position
		pointOnBox = glm::vec3(pointOnBox.x, maxPos.y, pointOnBox.z);
	}

	//if the sphere's z position is smaller/bigger than the min/max z position of the AABB then set the collision point on the box to its min/max z value
	if (_sphereCollider->GetPosition().z < minPos.z)
	{
		//if sphere is in front of the box, set the z value of the point on box to the AABB's min z position
		pointOnBox = glm::vec3(pointOnBox.x, pointOnBox.y, minPos.z);
	}
	if (_sphereCollider->GetPosition().z > maxPos.z)
	{
		//if sphere is behind the box, set the z value of the point on box to the AABB's max z position
		pointOnBox = glm::vec3(pointOnBox.x, pointOnBox.y, maxPos.z);
	}


	//calculate the square values for the radius and distance
	float distance = glm::distance(pointOnBox, _sphereCollider->GetPosition());
	glm::vec3 distanceSquare = glm::vec3((_sphereCollider->GetPosition().x - pointOnBox.x) * (_sphereCollider->GetPosition().x - pointOnBox.x),
		(_sphereCollider->GetPosition().y - pointOnBox.y) * (_sphereCollider->GetPosition().y - pointOnBox.y),
		(_sphereCollider->GetPosition().z - pointOnBox.z) * (_sphereCollider->GetPosition().z - pointOnBox.z));

	float distanceAdded = distanceSquare.x + distanceSquare.y + distanceSquare.z;

	//if the radius square value is bigger than the distance square value there is a collision
	if (_sphereCollider->GetRadius() * _sphereCollider->GetRadius() > distanceAdded)
	{
		//calculate collision normal, point and penetration depth
		collisionInfo.collisionNormal = glm::normalize(pointOnBox - _sphereCollider->GetPosition()); //normalise(position - position2)
		collisionInfo.collisionPoint = pointOnBox; //(position2 + radius) x normal 
		collisionInfo.penetrationDepth = _sphereCollider->GetRadius() - distance; //radius + radius - distance

		return true;
	}
	else
	{
		return false;
	}
}

AABBCollider::AABBCollider(glm::vec3 _pos, int _id, float _length, float _height, float _width) : Collider(_pos, _id, _length, _height, _width)
{

}

AABBCollider::~AABBCollider()
{
}