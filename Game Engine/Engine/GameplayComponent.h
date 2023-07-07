#pragma once

#include "Common.h"
#include "Component.h"

class GameplayComponent : public Component
{
public:
	//constructors
	GameplayComponent(GameObject* _gameObject, Subsystem* _subsystem, Vector2 _position, int _health, bool _isAI, std::vector<Vector2> _waypoints)
		: Component(ComponentType::Gameplay, _gameObject, _subsystem), position(_position), health(_health), isAI(_isAI), waypoints(_waypoints) 
	{
		//if the passed waypoint vector is empty create a temporary vector so it is not empty
		if (waypoints.size() == 0)
		{
			waypoints = { Vector2(0, 0),  Vector2(0, 0) };
		}
		nextWaypoint = 0;
		score = 0;
	};
	GameplayComponent(GameObject* _gameObject, Subsystem* _subsystem, Vector2 _position, int _health)
		: Component(ComponentType::Gameplay, _gameObject, _subsystem), position(_position), health(_health), isAI(false)
	{
		//if the passed waypoint vector is empty create a temporary vector so it is not empty
		if (waypoints.size() == 0)
		{
			waypoints = { Vector2(0, 0),  Vector2(0, 0) };
		}
		nextWaypoint = 0;
		score = 0;
	};
	GameplayComponent(GameObject* _gameObject, Subsystem* _subsystem, Vector2 _position)
		: Component(ComponentType::Gameplay, _gameObject, _subsystem), position(_position), isAI(false)
	{
		//if the passed waypoint vector is empty create a temporary vector so it is not empty
		if (waypoints.size() == 0)
		{
			waypoints = { Vector2(0, 0),  Vector2(0, 0) };
		}
		nextWaypoint = 0;
		health = 0;
		score = 0;
	};
	GameplayComponent& operator=(const GameplayComponent& _other);

	//functions
	void Update();

	Vector2 GetPosition() { return position; }
	void SetPosition(Vector2 _position) { position = _position; }

	void Patrol();
	Vector2 GetNextWaypoint() { return waypoints[nextWaypoint]; }
	void SetWaypoints(std::vector<Vector2> _waypoints) { waypoints = _waypoints; }

	int GetHealth() { return health; }
	void SetHealth(int _health) { health = _health; }

	int GetScore() { return score; }
	void SetScore(int _score) { score = _score; }
	void AddScore(int _score) { score += _score; }

private:
	Vector2 position; //position of object
	bool isAI; //true if the object is an AI
	std::vector<Vector2> waypoints; //waypoints for an AI object
	int nextWaypoint; //the next waypoint destination of the AI object

	int health; //health value of the object (for player and AI objects)
	int score; //score value of the object (for player objects)

};

