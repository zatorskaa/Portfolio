#pragma once

#include <SFML\Network.hpp>

#include "Common.h"
#include "Subsystem.h"
#include "NetworkComponent.h"

class NetworkSubsystem : public Subsystem
{
public:
	//constructors
	NetworkSubsystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects)
		: Subsystem(SubsystemType::Network, _eventQueue, _gameObjects)
	{
		components = new std::vector<NetworkComponent>;
		components->reserve(MAX_ENTITIES);

		//bind the client ip address and port number to a socket
		port = sf::Socket::AnyPort;
		ip = sendIP = sf::IpAddress("10.0.74.149");

		if (socket.bind(port, ip) != sf::Socket::Done)
		{
			std::cout << "Error binding socket" << std::endl;
		}
		else
		{
			std::cout << "Socket Bind Complete" << std::endl;
		}

		socket.setBlocking(false);

		//server's ip and port number
		sendPort = 9050;
		sendIP = sf::IpAddress("10.0.74.149");

		assignGlobalID = 0;
	};
	NetworkSubsystem(const NetworkSubsystem& _other)
		: Subsystem(_other)
	{
		components->reserve(MAX_ENTITIES);

		//bind the client ip address and port number to a socket
		port = sf::Socket::AnyPort;
		ip = sendIP = sf::IpAddress("10.0.74.149");

		if (socket.bind(port, ip) != sf::Socket::Done)
		{
			std::cout << "Error binding socket" << std::endl;
		}
		else
		{
			std::cout << "Socket Bind Complete" << std::endl;
		}

		socket.setBlocking(false);

		//server's ip and port number
		sendPort = 9050;
		sendIP = sf::IpAddress("10.0.74.149");

		assignGlobalID = 0;
	}

	//functions
	Component* AddComponent(Component* _component);
	void RemoveComponent(int _i);
	Component* GetComponent(int _i) { return &(components->at(_i)); }

	void Update();
	int GetNumOfComponents() { return components->size(); }

	void RequestUIDs(NetworkComponent* _component);
	void SendMessage(std::string _message);
	void Listen();
	void AssignUID(int _localId, int _globalID);
	void SendObjectData(NetworkComponent* _component);
	void UpdateObjectData(int _globalId, float _posX, float _posY, float _rot, int _score);

	static bool GetSpawnNetObject() { return spawnNetObject; }
	static void SetSpawnNetObject(bool _spawnNetObject) { spawnNetObject = _spawnNetObject; }
	int GetAssignGlobalID() { return assignGlobalID; }

private:
	std::vector<NetworkComponent>* components;
	static int lastAssignedLocalID;
	static bool spawnNetObject;
	int assignGlobalID;

	sf::UdpSocket socket;
	sf::IpAddress ip;
	unsigned short port;

	sf::IpAddress sendIP;
	unsigned short sendPort;
};

