#include "NetworkSubsystem.h"
#include "EventQueue.h"
#include "GameObject.h"

int NetworkSubsystem::lastAssignedLocalID = 1;
bool NetworkSubsystem::spawnNetObject = false;

Component* NetworkSubsystem::AddComponent(Component* _component)
{
	if (_component->GetComponentType() == ComponentType::Network)
	{
		NetworkComponent* temp = static_cast<NetworkComponent*>(_component);

		//if the object is local assign a local id
		if (temp->GetIsLocallyOwned())
		{
			temp->SetLocalID(lastAssignedLocalID);
			lastAssignedLocalID++;
		}

		//send a request to the server to assign a global id to the object
		RequestUIDs(temp);

		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Not a network component" << std::endl;
		return nullptr;
	}
}

void NetworkSubsystem::RemoveComponent(int _i)
{
	components->erase(components->begin() + _i);
}

void NetworkSubsystem::Update()
{
	//update each game object
	for (int i = 0; i < components->size(); i++)
	{
		if (components->at(i).GetGameObject()->GetName() == "NetObject")
		{
			//check if the network object (player 2) is enabled and call its update if it is
			if (spawnNetObject)
			{
				components->at(i).Update();
				if (components->at(i).GetGlobalID() == 0)
				{
					components->at(i).SetGlobalID(assignGlobalID);
				}
			}
		}
		else
		{
			components->at(i).Update();
			SendObjectData(&components->at(i));
		}
	}

	//check the event queue for network events
	int eQsize = eventQueue->events.size();

	if (eQsize > 0)
	{
		Event* temp;

		for (int i = 0; i < eQsize; i++)
		{
			temp = eventQueue->events[i];

			for (int j = 0; j < temp->subsystemTypes.size(); j++)
			{
				if (temp->subsystemTypes[j] == subsystemType)
				{
					//check the event type and call the matching function in the event queue function map
					auto it = eventQueue->functionMap.find(subsystemType);

					auto it2 = it->second->find(temp->eventType);

					it2->second(temp);

					//after calling the function, delete the current subsystem type from the event
					try
					{
						temp->subsystemTypes.erase(temp->subsystemTypes.begin() + j);
					}
					catch (const std::exception& e)
					{
						std::cout << "Network Error" << std::endl;
					}

					//if there are no more subsystem types in the event, delete the event fromt the event queue
					if (temp->subsystemTypes.size() == 0)
					{
						delete eventQueue->events[i];
						eventQueue->events.erase(eventQueue->events.begin() + i);
						eQsize = eventQueue->events.size();
					}
				}
			}
		}
	}

	//check if any messages have been recieved from the server
	Listen();
}

void NetworkSubsystem::RequestUIDs(NetworkComponent* _component)
{
	//if the object is locally owned and doesn't have a global id yet
	if (_component->GetIsLocallyOwned() && _component->GetGlobalID() == 0)
	{
		//send a UID request to the server
		std::string message = "Get UID:" + std::to_string(_component->GetLocalID()) + ";";

		SendMessage(message);
	}
}

void NetworkSubsystem::SendMessage(std::string _message)
{
	//convert the string into a char array and send the message to the server
	if (socket.send(_message.c_str(), _message.length() + 1, sendIP, sendPort) != sf::Socket::Done)
	{
		//std::cout << "Error" << std::endl;
	}
	else
	{
		//std::cout << _message.c_str() << std::endl;
	}
}

void NetworkSubsystem::Listen()
{
	std::size_t received;
	sf::IpAddress receiveIP;
	unsigned short receivePort;

	char buffer[2048];
	std::vector<std::string> values;

	//check if the socket has recieved data and store it in the char array
	sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received, receiveIP, receivePort);

	//if the socket has recieved data
	if (status == sf::Socket::Done)
	{
		std::string temp = "";

		//create a vector of strings from the char array (each string in the array is an object data value from a client)
		for (int i = 0; i < sizeof(buffer); i++)
		{
			//use ; and : to find where each data value ends
			if (buffer[i] == ';' || buffer[i] == ':')
			{
				//if the loop is at the end of a value add it to the vector and clear the temp string
				values.push_back(temp);
				temp = "";
			}
			else
			{
				//add the char to the string if the loop has not reached the end of a value
				temp.push_back(buffer[i]);
			}
		}

		//check how many values are in the vector
		if (values.size() > 1)
		{
			if (values[0] == "Assigned UID")
			{
				//if an object UID has been recieved call the function to assign it to the object
				AssignUID(std::stoi(values[1]), std::stoi(values[2]));
			}
		}
		if (values.size() > 5)
		{
			if (values[0] == "Game State")
			{
				//if object data has been recieved call the function to update that object's data
				UpdateObjectData(std::stoi(values[1]), std::stof(values[2]), std::stof(values[3]), std::stof(values[4]), std::stoi(values[5]));
			}
		}
	}
}

void NetworkSubsystem::AssignUID(int _localId, int _globalID)
{
	for (int i = 0; i < components->size(); i++)
	{
		//find the object with the correct local id
		if (components->at(i).GetLocalID() == _localId)
		{
			//assign the global id
			components->at(i).SetGlobalID(_globalID);

			//std::cout << "Set Global ID: " << components->at(i).GetGlobalID() << std::endl;
		}
	}
}

void NetworkSubsystem::SendObjectData(NetworkComponent* _component)
{
	//convert the object's data (id, position, rotation & score) into a string with ; between each value
	std::string message = "Object Data:" +
		std::to_string(_component->GetGlobalID()) + ";" +
		std::to_string(_component->GetPosition().x) + ";" +
		std::to_string(_component->GetPosition().y) + ";" +
		std::to_string(_component->GetRotation()) + ";" +
		std::to_string(_component->GetScore()) + ";";

	SendMessage(message);
}

void NetworkSubsystem::UpdateObjectData(int _globalId, float _posX, float _posY, float _rot, int _score)
{
	bool idExists = false;

	for (int i = 0; i < components->size(); i++)
	{
		//find the network object for which data was recieved
		if (_globalId == components->at(i).GetGlobalID() && !components->at(i).GetIsLocallyOwned())
		{
			//set its position, rotation and score and call function to create event to update this for all components
			components->at(i).SetPosition(Vector2(_posX, _posY));
			components->at(i).SetRotation(_rot);
			components->at(i).SetScore(_score);
			components->at(i).UpdateNetPosition();
			idExists = true;
		}
		if (_globalId == components->at(i).GetGlobalID() && components->at(i).GetIsLocallyOwned())
		{
			idExists = true;
		}
	}

	//if the object hasn't been 'spawned' yet create an event to 'spawn' the object (start updating its components and move it to the visible part of the game level)
	if (!idExists)
	{
		assignGlobalID = _globalId;
		spawnNetObject = true;

		std::vector<GameObject*> gameObjects;
		std::vector<SubsystemType> subsystemType;
		int i;

		Event* eventE = new Event();

		for (i = 0; i < GetGameObjects()->size(); i++)
		{
			gameObjects.push_back(GetGameObjects()->at(i));
		}

		subsystemType.push_back(SubsystemType::Network);

		eventE->AssignObjects(gameObjects);
		eventE->AssignSubsystemType(subsystemType);
		eventE->AssignEventType(EventType::SpawnNetObject);
		GetEventQueue()->events.push_back(eventE);
	}
}
