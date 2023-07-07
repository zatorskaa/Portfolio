#include "Server.h"

int Server::lastAssignedGlobalID = 12;
std::unordered_map<int, std::string> Server::gameState = {};

void Server::Update()
{
	Listen(); //check constantly for recieved messages from clients
}

void Server::Listen()
{
	std::size_t received;
	sf::IpAddress receiveIP;
	unsigned short receivePort;

	char buffer[2048];
	std::vector<std::string> values;

	//check if the socket has recieved data and store it in the char array
	sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received, receiveIP, receivePort);

	//set the send ip and port number to the ones recieved from the client
	sendIP = receiveIP;
	sendPort = receivePort;

	//if the socket has recieved data
	if (status == sf::Socket::Done)
	{
		std::string temp = "";

		//create a vector of strings from the char array (each string in the array is an object data value from the client)
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

		//check if the vector is not empty
		if (values.size() > 1)
		{
			if (values[0] == "Get UID")
			{
				//if the client sent a UID request call the function to assign a UID to that client (passing the local ID of the object)
				AssignUID(std::stoi(values[1]));
			}
			else if (values[0] == "Object Data")
			{
				//if the client sent object data, update the game state in the server and then send the game state back to the client
				UpdateGameState(values);
				SendGameState(std::stoi(values[1]));
			}
		}
	}
}

void Server::SendMessage(std::string _message)
{
	//convert the string into a char array and send the message to a client using the recieved ip and port number
	if (socket.send(_message.c_str(), _message.length() + 1, sendIP, sendPort) != sf::Socket::Done)
	{
		//std::cout << "Error" << std::endl;
	}
	else
	{
		//std::cout << _message.c_str() << std::endl;
	}
}

void Server::AssignUID(int _localID)
{
	//add the new unique global ID to the game state
	gameState.insert({ lastAssignedGlobalID, "" });

	//create a message to send to the client with the new global ID
	std::string message = "Assigned UID:" + std::to_string(_localID) + ";" + std::to_string(lastAssignedGlobalID) + ";";
	lastAssignedGlobalID++;

	SendMessage(message);
}

void Server::SendGameState(int _globalID)
{
	//create a message with object data to send to the client
	std::string message = "Game State:";

	if (gameState.size() > 0)
	{
		//go through all the clients stored in the game state
		for (auto i = gameState.begin(); i != gameState.end(); i++)
		{
			//check if it is not the client's own object data
			if (i->first != _globalID)
			{
				//create a message with the other client ID and object data to send to the current client
				message = "Game State:" + std::to_string(i->first) + ";" + i->second + ";";
				//std::cout << message << std::endl;

				//send each client's data as a separate message
				SendMessage(message);
			}
		}
	}
}

void Server::UpdateGameState(std::vector<std::string> _values)
{
	if (gameState.size() > 0)
	{
		for (auto i = gameState.begin(); i != gameState.end(); i++)
		{
			//find the recieved global ID in the game state
			if (std::to_string(i->first) == _values[1])
			{
				//update the client's object data
				i->second = _values[2] + ";" + _values[3] + ";" + _values[4] + ";" + _values[5];
			}
		}
	}
}
