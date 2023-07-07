#include "Server.h"

void main()
{
	//create a server
	Server* server = new Server();

	//keep the server running constantly
	while (true)
	{
		server->Update();
	}
}