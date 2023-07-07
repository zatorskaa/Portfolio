using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;


public class NetworkManager : MonoBehaviour
{
    //network variables
    public struct UdpState
    {
        public UdpClient u;
        public IPEndPoint e;
    }

    static UdpClient client;
    static IPEndPoint ep;
    static UdpState state;
    public static List<NetworkGameObject> netObjects; //stores all the connected net objects
    public List<NetworkGameObject> worldState;
    string receiveString = "";

   [SerializeField] GameObject networkAvatar; //object to spawn for connected clients

    //stores all the connected players
    static public Player[] players;
    static public List<Player> clients;
    static public Player player;

    static public int packetID; //a unique packet id for each packet to check if a client has recieved the same packet more than once

    private void Awake()
    {
        //find all the players currently in the game
        players = FindObjectsOfType<Player>();
        clients = new List<Player>();
        player = players[0];

        if (players.Length != 0)
        {
            for (int i = 0; i < players.Length; i++)
            {
                if (players[i].transform.GetComponent<NetworkGameObject>().GetIsLocallyOwned())
                {
                    player = players[i];
                }
                else
                {
                    clients.Add(players[i]);
                }
            }
        }

        packetID = 0;
    }

    void Start()
    {
        //find all network objects currentl in the game
        netObjects = new List<NetworkGameObject>();
        netObjects.AddRange(GameObject.FindObjectsOfType<NetworkGameObject>());

        worldState = new List<NetworkGameObject>();
        worldState.AddRange(GameObject.FindObjectsOfType<NetworkGameObject>());


        client = new UdpClient();
        //ep = new IPEndPoint(IPAddress.Parse("10.0.74.149"), 9050); //assign the ip and socket number of the server
        ep = new IPEndPoint(IPAddress.Parse("192.168.1.174"), 9050); //assign the ip and socket number of the server
        client.Connect(ep);

        //send connction message to the server
        string myMessage = "I'm a Unity client - Hi!";
        byte[] array = Encoding.ASCII.GetBytes(myMessage);
        client.Send(array, array.Length);


        //start all the functions and coroutines to send/recieve data to/from the server
        client.BeginReceive(ReceiveAsyncCallback, state);

        RequestUIDs();
        StartCoroutine(SendNetworkUpdates());
        StartCoroutine(updateWorldState());
    }

    void Update()
    {

    }

    void ReceiveAsyncCallback(IAsyncResult result)
    {
        //recieve packets from the server
        byte[] receiveBytes = client.EndReceive(result, ref ep); //get the packet
        receiveString = Encoding.ASCII.GetString(receiveBytes); //decode the packet
        //Debug.Log("Received " + receiveString + " from " + ep.ToString()); //display the packet

        //check if the packet contains a UID to assign to a local object
        if (receiveString.Contains("Assigned UID:"))
        {
            int parseFrom = receiveString.IndexOf(':');
            int parseTo = receiveString.LastIndexOf(';');

            //get the local and global ids from the packet
            int localID = Int32.Parse(betweenStrings(receiveString, ":", ";"));
            int globalID = Int32.Parse(receiveString.Substring(receiveString.IndexOf(";") + 1));

            //Debug.Log("Got assignment: " + localID + " local to: " + globalID + " global");

            foreach (NetworkGameObject netObject in netObjects)
            {
                //if the local ID sent by the server matches this game object
                if (netObject.localID == localID)
                {
                    //Debug.Log(localID + " : " + globalID);
                    //the global ID becomes the server-provided value
                    netObject.SetUID(globalID);
                }
            }
        }

        client.BeginReceive(ReceiveAsyncCallback, state); //self-callback, meaning this loops infinitely
    }

    void RequestUIDs()
    {
        //send messages to the server to request UIDs for each local object
        netObjects = new List<NetworkGameObject>();
        netObjects.AddRange(GameObject.FindObjectsOfType<NetworkGameObject>());

        foreach (NetworkGameObject netObject in netObjects)
        {
            if (netObject.GetIsLocallyOwned() && netObject.GetUID() == 0)
            {
                string myMessage = "I need a UID for local object:" + netObject.localID;
                byte[] array = Encoding.ASCII.GetBytes(myMessage);
                client.Send(array, array.Length);
            }
        }
    }

    public static String betweenStrings(String text, String start, String end)
    {
        int p1 = text.IndexOf(start) + start.Length;
        int p2 = text.IndexOf(end, p1);

        if (end == "") return (text.Substring(p1));
        else return text.Substring(p1, p2 - p1);
    }

    IEnumerator SendNetworkUpdates()
    {
        //coroutine sends packets to the server with the current data of each object
        while (true)
        {
            List<NetworkGameObject> netObjects = new List<NetworkGameObject>();
            netObjects.AddRange(GameObject.FindObjectsOfType<NetworkGameObject>());

            foreach (NetworkGameObject netObject in netObjects)
            {
                if (netObject.GetIsLocallyOwned() && netObject.GetUID() != 0)
                {
                    client.Send(netObject.toPacket(), netObject.toPacket().Length);
                }
            }

            //reset isShot for all clients after a packet with the event has been sent
            if (NetworkManager.clients != null && NetworkManager.clients.Count > 0)
            {
                for (int i = 0; i < NetworkManager.clients.Count; i++)
                {
                    NetworkManager.clients[i].SetIsShot(false);
                }
            }

            //increase the packet id (resets back to 0 so it does not go above the max value of an int)
            if (NetworkManager.packetID < 300)
            {
                NetworkManager.packetID++;
            }
            else
            {
                NetworkManager.packetID = 0;
            }


            yield return new WaitForSeconds(0.1f);
        }
    }

    int GetGlobalIDFromPacket(String packet)
    {
        return Int32.Parse(packet.Split(';')[1]);
    }

    IEnumerator updateWorldState()
    {
        while (true)
        {
            //find all the netwrok game objects in the world
            worldState = new List<NetworkGameObject>();
            worldState.AddRange(GameObject.FindObjectsOfType<NetworkGameObject>());

            //cache the recieved packet string - we'll use that later to suspend the couroutine until it changes
            string previousRecieveString = receiveString;

            //check if the recieved string is object data
            if (receiveString.Contains("Object Data;"))
            {
                //we'll want to know if an object with this global id is already in the game world
                bool objectIsAlreadyInWorld = false;

                //we'll also want to exclude any invalid packets with a bad global id
                if (GetGlobalIDFromPacket(receiveString) != 0)
                {
                    //for every networked gameobject in the world
                    foreach (NetworkGameObject ngo in worldState)
                    {
                        //if it's unique ID matches the packet, update it's position from the packet
                        if (ngo.GetUID() == GetGlobalIDFromPacket(receiveString))
                        {
                            //only update it if we don't own it - you might want to try disabling and seeing the effect
                            if (!ngo.GetIsLocallyOwned())
                            {
                                ngo.fromPacket(receiveString);

                            }
                            //if we have any uniqueID matches, our object is in the world
                            objectIsAlreadyInWorld = true;
                        }

                    }


                    //if it's not in the world, we need to spawn it
                    if (!objectIsAlreadyInWorld)
                    {
                        int newObjectID = GetGlobalIDFromPacket(receiveString);
                        bool isObjectAlreadyInstantiated = false;
                        for (int i = 0; i < worldState.Count; i++)
                        {
                            //check if an object with that global id already exists
                            if (worldState[i].GetUID() == newObjectID)
                            {
                                isObjectAlreadyInstantiated = true;
                            }
                        }

                        //if no object exists with that global id then spawn a new object
                        if (!isObjectAlreadyInstantiated)
                        {
                            GameObject otherPlayerAvatar = Instantiate(networkAvatar);

                            //update its component properties from the packet
                            otherPlayerAvatar.GetComponent<NetworkGameObject>().SetUID(GetGlobalIDFromPacket(receiveString));
                            otherPlayerAvatar.GetComponent<NetworkGameObject>().fromPacket(receiveString);
                        }
                    }
                }

            }

            //wait until the incoming string with packet data changes then iterate again

            yield return new WaitUntil(() => !receiveString.Equals(previousRecieveString));
        }
    }

}
