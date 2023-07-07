#pragma once

#include <SFML/Network.hpp>
#include "Common.h"

class Server
{
public:
	Server()
	{
		//bind the server ip address and port number to a socket
		port = 9050;
		ip = sf::IpAddress("10.0.74.149"); 

		if (socket.bind(port, ip) != sf::Socket::Done)
		{
			std::cout << "Error binding socket" << std::endl;
		}
		else
		{
			std::cout << "Socket Bind Complete" << std::endl;
		}

		//set blocking to false so the socket functions will always return immediately
		socket.setBlocking(false);


		sendPort = sf::Socket::AnyPort;
		sendIP = sf::IpAddress("10.0.74.149");
	}

	void Update();

	void Listen();
	void SendMessage(std::string _message);
	void AssignUID(int _localID);
	void SendGameState(int _globalID);
	void UpdateGameState(std::vector<std::string> _values);

private:
	static int lastAssignedGlobalID;
	static std::unordered_map<int, std::string> gameState; //stores all the connected client object global IDs and their data

	sf::UdpSocket socket;
	sf::IpAddress ip;
	unsigned short port;

	sf::IpAddress sendIP;
	unsigned short sendPort;
};

