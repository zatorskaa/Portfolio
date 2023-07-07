#pragma once

#include <unordered_map>
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

enum class EventType { MoveUp, MoveDown, MoveLeft, MoveRight, Exit, PatrolUp, PatrolDown, PatrolLeft, PatrolRight, Shoot, NetworkUpdate, NetworkUpdateRecieved, SpawnNetObject, PlayMusic, Unassigned };
enum class SubsystemType { Physics, Graphics, UI, Gameplay, Network, Audio, Unassigned };
enum class ComponentType { Physics, Graphics, UI, Gameplay, Network, Audio, Unassigned };

#define MAX_ENTITIES 20

struct Vector2
{
	float x;
	float y;

	Vector2() { x = 0; y = 0; };
	Vector2(float _x, float _y) { x = _x; y = _y; }
};

const float pi = 3.14;