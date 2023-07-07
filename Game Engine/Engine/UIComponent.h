#pragma once

#include <SFML\Graphics.hpp>

#include "Common.h"
#include "Component.h"

class UIComponent : public Component
{
public:
	//constructors
	UIComponent(GameObject* _gameObject, Subsystem* _subsystem, sf::RenderWindow* _window)
		: Component(ComponentType::UI, _gameObject, _subsystem), window(_window)
	{
		//assign keys and mouse buttons
		upKey = sf::Keyboard::W;
		downKey = sf::Keyboard::S;
		leftKey = sf::Keyboard::A;
		rightKey = sf::Keyboard::D;

		shootButton = sf::Mouse::Left;

		pauseMusicKey = sf::Keyboard::P;
		exitGameKey = sf::Keyboard::Escape;

		//set movement states to false
		moveUp = false;
		moveDown = false;
		moveLeft= false;
		moveRight = false;
	};

	UIComponent& operator=(const UIComponent& _other);

	//functions
	void Update();

	Vector2 GetMousePos() { return mousePos; }

private:
	sf::RenderWindow* window; //pointer to sfml window created in graphics subsystem
	Vector2 mousePos;

	//states of movement keys (pressing/holding a key is true, releasing a key is false)
	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;

	//key & mouse buttons for each action
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;

	sf::Mouse::Button shootButton;

	sf::Keyboard::Key pauseMusicKey;
	sf::Keyboard::Key exitGameKey;
};

