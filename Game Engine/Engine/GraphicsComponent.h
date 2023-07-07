#pragma once

#include <SFML\Graphics.hpp>

#include "Common.h"
#include "Component.h"

class GraphicsComponent : public Component
{
public:
	//constructors
	GraphicsComponent(GameObject* _gameObject, Subsystem* _subsystem, Vector2 _position, sf::RenderWindow* _window, Vector2 _size, std::string _texture)
		: Component(ComponentType::Graphics, _gameObject, _subsystem), window(_window)
	{
		//scale up the size and positions of the object for the graphics component
		scalingFactor = 100;

		rotation = 0.0f;
		size = sf::Vector2f(_size.x * scalingFactor, _size.y * scalingFactor);
		rectangleShape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2)); //set the origin of the graphics to the middle of the object to match the physics
		position.x = _position.x * scalingFactor;
		position.y = _position.y * scalingFactor * -1;

		//load the texture and font files
		if (!texture.loadFromFile(_texture))
		{
			std::cout << "Texture did not load!" << "\n";
		}

		if (!font.loadFromFile("../Fonts/arial.ttf"))
		{
			std::cout << "Font did not load!" << "\n";
		}

		score = 0;
	};

	GraphicsComponent& operator=(const GraphicsComponent& _other);

	//functions
	sf::Texture GetTexture() { return texture; }
	void SetTexture(sf::Texture _texture) { texture = _texture; }
	void SetWindow(sf::RenderWindow* _window) { window = _window; }

	void Update();
	void Draw();

	void Move(Vector2 _position, float _rotation);

	Vector2 GetPosition() { return Vector2(position.x, position.y); }
	Vector2 GetHalfSize(){ return Vector2(size.x / 2, size.y / 2); }

	int GetScore() { return score; }
	void SetScore(int _score) { score = _score; }
	void DrawText();

private:
	//variables for drawing graphics object
	sf::Texture texture;
	sf::RectangleShape rectangleShape;
	sf::Vector2f position;
	sf::Vector2f size;
	float rotation;

	float scalingFactor; //the amount to scale by from physics to graphics

	int score; //score value (for players)
	//varaibles for drawing text (for players)
	sf::Text text;
	sf::Font font;

	sf::RenderWindow* window; //pointer to sfml window created in subsystem
};

