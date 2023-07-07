#include "UIComponent.h"
#include "UISubsystem.h"
#include "GameObject.h"
#include "EventQueue.h"

UIComponent& UIComponent::operator=(const UIComponent& _other)
{
	if (this == &_other)
		return *this;

	UIComponent a(_other);
	return a;
}

void UIComponent::Update()
{
		if (gameObject->GetName() == "Player")
		{
			sf::Event e;

			//check for sfml events in the window
			while (window->pollEvent(e))
			{
				if (e.type == sf::Event::KeyPressed)
				{
					//if a movement key is pressed set its state to true
					if (e.key.code == upKey)
					{
						moveUp = true;
					}
					if (e.key.code == downKey)
					{
						moveDown = true;
					}

					if (e.key.code == leftKey)
					{
						moveLeft = true;
					}
					if (e.key.code == rightKey)
					{
						moveRight = true;
					}

					//if the pause key is pressed create an event to pause/unpause the music
					if (e.key.code == pauseMusicKey)
					{
						std::vector<GameObject*> gameObjects;
						std::vector<SubsystemType> subsystemType;
						int i;

						Event* eventE = new Event();

						for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
						{
							gameObjects.push_back(subsystem->GetGameObjects()->at(i));
						}

						subsystemType.push_back(SubsystemType::Audio);

						eventE->AssignObjects(gameObjects);
						eventE->AssignSubsystemType(subsystemType);
						eventE->AssignEventType(EventType::PlayMusic);
						subsystem->GetEventQueue()->events.push_back(eventE);
					}

					//if the exit key is pressed create event to exit the game
					if (e.key.code == exitGameKey)
					{
						window->close();

						std::vector<GameObject*> gameObjects;
						std::vector<SubsystemType> subsystemType;
						int i;

						Event* eventE = new Event();

						for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
						{
							gameObjects.push_back(subsystem->GetGameObjects()->at(i));
						}
#
						eventE->AssignObjects(gameObjects);
						eventE->AssignSubsystemType(subsystemType);
						eventE->AssignEventType(EventType::Exit);
						subsystem->GetEventQueue()->events.push_back(eventE);
					}
						
				}
				if (e.type == sf::Event::KeyReleased)
				{
					//if a movement key is released set its state to false
					if (e.key.code == upKey)
					{
						moveUp = false;
					}
					if (e.key.code == downKey)
					{
						moveDown = false;
					}
					if (e.key.code == leftKey)
					{
						moveLeft = false;
					}
					if (e.key.code == rightKey)
					{
						moveRight = false;
					}
				}

				if (e.type == sf::Event::MouseButtonPressed)
				{
					//if the shoot mouse button is pressed create a shoot event
					if (e.mouseButton.button == shootButton)
					{
						std::vector<GameObject*> gameObjects;
						std::vector<SubsystemType> subsystemType;
						int i;

						Event* eventE = new Event();

						mousePos = Vector2(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

						for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
						{
							gameObjects.push_back(subsystem->GetGameObjects()->at(i));
						}

						subsystemType.push_back(SubsystemType::Gameplay);

						eventE->AssignObjects(gameObjects);
						eventE->AssignSubsystemType(subsystemType);
						eventE->AssignEventType(EventType::Shoot);
						subsystem->GetEventQueue()->events.push_back(eventE);
					}
				}
			}


			//if a movement state is true, create an event for that movement direction to move the physics and graphics of the object
			if (moveUp)
			{
				std::vector<GameObject*> gameObjects;
				std::vector<SubsystemType> subsystemType;
				int i;

				Event* eventE = new Event();

				for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
				{
					gameObjects.push_back(subsystem->GetGameObjects()->at(i));
				}

				subsystemType.push_back(SubsystemType::Physics);
				subsystemType.push_back(SubsystemType::Graphics);

				eventE->AssignObjects(gameObjects);
				eventE->AssignSubsystemType(subsystemType);
				eventE->AssignEventType(EventType::MoveUp);
				subsystem->GetEventQueue()->events.push_back(eventE);
			}
			if (moveDown)
			{
				std::vector<GameObject*> gameObjects;
				std::vector<SubsystemType> subsystemType;
				int i;

				Event* eventE = new Event();

				for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
				{
					gameObjects.push_back(subsystem->GetGameObjects()->at(i));
				}

				subsystemType.push_back(SubsystemType::Physics);
				subsystemType.push_back(SubsystemType::Graphics);

				eventE->AssignObjects(gameObjects);
				eventE->AssignSubsystemType(subsystemType);
				eventE->AssignEventType(EventType::MoveDown);
				subsystem->GetEventQueue()->events.push_back(eventE);
			}
			if (moveLeft)
			{
				std::vector<GameObject*> gameObjects;
				std::vector<SubsystemType> subsystemType;
				int i;

				Event* eventE = new Event();

				for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
				{
					gameObjects.push_back(subsystem->GetGameObjects()->at(i));
				}

				subsystemType.push_back(SubsystemType::Physics);
				subsystemType.push_back(SubsystemType::Graphics);

				eventE->AssignObjects(gameObjects);
				eventE->AssignSubsystemType(subsystemType);
				eventE->AssignEventType(EventType::MoveLeft);
				subsystem->GetEventQueue()->events.push_back(eventE);
			}
			if (moveRight)
			{
				std::vector<GameObject*> gameObjects;
				std::vector<SubsystemType> subsystemType;
				int i;

				Event* eventE = new Event();

				for (i = 0; i < subsystem->GetGameObjects()->size(); i++)
				{
					gameObjects.push_back(subsystem->GetGameObjects()->at(i));
				}

				subsystemType.push_back(SubsystemType::Physics);
				subsystemType.push_back(SubsystemType::Graphics);

				eventE->AssignObjects(gameObjects);
				eventE->AssignSubsystemType(subsystemType);
				eventE->AssignEventType(EventType::MoveRight);
				subsystem->GetEventQueue()->events.push_back(eventE);
			}

		}
}