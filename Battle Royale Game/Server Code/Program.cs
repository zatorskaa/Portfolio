using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace NetworkServer
{
    class Server
    {
        static Dictionary<int, byte[]> gameState = new Dictionary<int, byte[]>(); //stores the data sent from each client
        static int lastAssignedGlobalID = 12; //global id that was assigned to the last client that connected
        static List<IPEndPoint> connectedClients = new List<IPEndPoint>(); //list of all clienta connected to the server

        string AssignUID(string message)
        {
            Console.WriteLine(message.Substring(message.IndexOf(':')));

            int localObjectNumber = Int32.Parse(message.Substring(message.IndexOf(':') + 1)); //get local id of client object
            string returnVal = ("Assigned UID:" + localObjectNumber + ";" + lastAssignedGlobalID++); //assign a global id to the client object

            Console.WriteLine(returnVal);

            return returnVal;
        }

        void UpdateGameState(string message, byte[] data)
        {
            Console.WriteLine(message);

            string globalId = message.Split(";")[1]; //get global id of client object
            int intId = Int32.Parse(globalId); //convert global id to an int

            if (gameState.ContainsKey(intId)) //check if this global id is already stored in the game state
            {
                gameState[intId] = data; //update the game state if the global id already exists
            }
            else
            {
                gameState.Add(intId, data); //add the global id to the game state if it doesn't already exist
            }
        }

        static void Main(string[] args)
        {
            Server server = new Server();

            //socket setup
            //IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("10.0.74.149"), 9050); //assign the ip and port number of the server
            IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("192.168.1.174"), 9050); //assign the ip and port number of the server
            Socket newsock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp); //create the socket for the server to send and recieve data
            newsock.Bind(ipep); //bind the socket to the ip

            Console.WriteLine("Socket open...");

            while(true)
            {
                int recv; //used to store the number of bytes recieved
                byte[]  data = new byte[2048]; //create a new array of bytes for each loop

                IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0); 
                EndPoint Remote = (EndPoint)(sender); //get the ip of the client that sent data to ther server

                recv = newsock.ReceiveFrom(data, ref Remote); //store data from client in array
                string messageRecieved = Encoding.ASCII.GetString(data, 0, recv); //convert byte array to string

                Console.WriteLine("Message recieved from " + Remote.ToString());
                Console.WriteLine(Encoding.ASCII.GetString(data, 0, recv));


                if (messageRecieved.Contains("I need a UID for local object:")) //check if the packet recieved is a UID request
                {
                    string returnVal = server.AssignUID(messageRecieved);

                    newsock.SendTo(Encoding.ASCII.GetBytes(returnVal), Encoding.ASCII.GetBytes(returnVal).Length, SocketFlags.None, Remote); //send the global id back to the client
                }
                else if (messageRecieved.Contains("Object Data")) //check if the packet recieved is object data
                {
                    server.UpdateGameState(messageRecieved, data);
                }


                bool IPisInList = false;
                IPEndPoint senderIPEndPoint = (IPEndPoint)Remote;
                foreach (IPEndPoint ep in connectedClients)
                {
                    if (senderIPEndPoint.ToString().Equals(ep.ToString())) IPisInList = true; //check if the client ip already exists in the server's ip list

                    Console.WriteLine("Sending gamestate to " + ep.ToString());

                    if (ep.Port != 0)
                    {
                        foreach (KeyValuePair<int, byte[]> kvp in gameState)
                        {
                            newsock.SendTo(kvp.Value, kvp.Value.Length, SocketFlags.None, ep); //send the game state to each client

                            Console.WriteLine("Data Sent");
                        }
                    }

                }

                if (!IPisInList)
                {
                    connectedClients.Add(senderIPEndPoint); //if the client does not exist in the server's ip list add it to the list

                    Console.WriteLine("A new client just connected. There are now " + connectedClients.Count + " clients.");
                }
            }

        }
    }

}

