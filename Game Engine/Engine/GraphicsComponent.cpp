#include "GraphicsComponent.h"
#include "GameObject.h"

GraphicsComponent& GraphicsComponent::operator=(const GraphicsComponent& _other)
{
	if (this == &_other)
		return *this;

	GraphicsComponent a(_other);
	return a;
}

void GraphicsComponent::Update()
{
	Draw();
}

void GraphicsComponent::Draw()
{
	//set up the texture, size, rotation and position of the rectangle object and draw it on screen
	rectangleShape.setTexture(&texture);
	rectangleShape.setSize(size);
	rectangleShape.setRotation(-rotation);
	rectangleShape.setPosition(position);

	window->draw(rectangleShape);
}

void GraphicsComponent::Move(Vector2 _position, float _rotation)
{
	//scale the physics position by the scaling factor and flip the y direction to match physics
	position.x = _position.x * scalingFactor;
	position.y = _position.y * scalingFactor * -1;

	rotation = _rotation;
}

void GraphicsComponent::DrawText()
{
	//set up the font, size, colour and position of text and draw it on screen to show each player's score
	if (gameObject->GetName() == "Player")
	{
		text.setString("Player Score: " + std::to_string(score));
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Green);
		text.setPosition(sf::Vector2f(100, 0));
	}
	else if(gameObject->GetName() == "NetObject")
	{
		text.setString("Player 2 Score: " + std::to_string(score));
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Cyan);
		text.setPosition(sf::Vector2f(600, 0));
	}

	window->draw(text);
}