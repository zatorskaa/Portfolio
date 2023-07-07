#pragma once

#include "Component.h"

class NetworkComponent : public Component
{
public:
	//constructors
	NetworkComponent(GameObject* _gameObject, Subsystem* _subsystem, Vector2 _position, bool _isLocallyOwned)
		: Component(ComponentType::Network, _gameObject, _subsystem), isLocallyOwned(_isLocallyOwned), position(_position)
	{
		uniqueNetworkID = 0;
		localID = 0;

		rotation = 0;
		score = 0;
	};
	NetworkComponent(GameObject* _gameObject, Subsystem* _subsystem, Vector2 _position, bool _isLocallyOwned, int _globalID)
		: Component(ComponentType::Network, _gameObject, _subsystem), isLocallyOwned(_isLocallyOwned), position(_position), uniqueNetworkID(_globalID)
	{
		localID = 0;

		rotation = 0;
		score = 0;
	};
	NetworkComponent& operator=(const NetworkComponent& _other);

	//functions
	bool GetIsLocallyOwned() { return isLocallyOwned; }
	void SetLocalID(int _localID) { localID = _localID; }
	int GetLocalID() { return localID; }
	void SetGlobalID(int _id) { uniqueNetworkID = _id; }
	int GetGlobalID() { return uniqueNetworkID; }

	Vector2 GetPosition() { return position; }
	void SetPosition(Vector2 _position) { position = _position; }
	float GetRotation() { return rotation; };
	void SetRotation(float _rotation) { rotation = _rotation; }

	void Update();
	void UpdateNetPosition();

	int GetScore() { return score; }
	void SetScore(int _score) { score = _score; }

private:
	bool isLocallyOwned;
	int uniqueNetworkID;
	int localID;

	Vector2 position;
	float rotation;

	int score;
};

