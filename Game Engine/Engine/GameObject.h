#pragma once

#include "Common.h"

class Component;

class GameObject
{
public:
	static int objectCount;

	//contructors
	GameObject();
	GameObject(std::string _name);
	GameObject(std::string _name, std::unordered_map<ComponentType, Component*> _components);
	GameObject(const GameObject& _other);

	~GameObject();

	GameObject& operator=(const GameObject& _other);

	//get and set functions
	void AddComponent(Component* _component);
	Component* GetComponentType(ComponentType _componentType);

	std::string GetName() { return *name; };
	void SetName(std::string _name) { *name = _name; }
	int GetObjectID() { return objectID; };

private:
	int objectID; //unique id of object
	std::string* name; //name of object
	std::unordered_map<ComponentType, Component*> components; //map of the object's components and their types
};

