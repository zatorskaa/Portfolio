#include "Animation.h"

void Animation::AnimateUpMovement(GameObject* _gameObject, float _maxYPos)
{
	//animation for triangle to move upwards
	if (_gameObject->rigidBody->GetPosition().y < _maxYPos)
	{
		_gameObject->rigidBody->SetPosition(glm::vec3(_gameObject->rigidBody->GetPosition().x, _gameObject->rigidBody->GetPosition().y + 0.1, _gameObject->rigidBody->GetPosition().z));
	}
}
