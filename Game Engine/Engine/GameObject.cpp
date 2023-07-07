#include "GameObject.h"
#include "Component.h"

int GameObject::objectCount = 0;

GameObject::GameObject()
{
	name = new std::string();
	objectID = objectCount;
	objectCount++;
}

GameObject::GameObject(std::string _name)
{
	name = new std::string();
	objectID = objectCount;
	*name = _name;
	objectCount++;
}

GameObject::GameObject(std::string _name, std::unordered_map<ComponentType, Component*> _components)
{
	objectID = objectCount;
	*name = _name;
	components = _components;
	objectCount++;
}

GameObject::GameObject(const GameObject& _other) : 
	objectID(_other.objectID), name(_other.name), components(_other.components) {};

GameObject::~GameObject()
{
	delete name;
}

GameObject& GameObject::operator=(const GameObject& _other)
{
	if (this == &_other)
		return *this;

	GameObject a(_other);
	return a;
}

void GameObject::AddComponent(Component* _component)
{
	components.insert({ _component->GetComponentType(), _component });
}

Component* GameObject::GetComponentType(ComponentType _componentType)
{
	auto it = components.find(_componentType);
	return it->second;
}