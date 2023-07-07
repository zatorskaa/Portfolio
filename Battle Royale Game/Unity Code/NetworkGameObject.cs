using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

public class NetworkGameObject : MonoBehaviour
{
    //network variables
    [SerializeField] bool isLocallyOwned;
    [SerializeField] int uniqueNetworkID = 0;
    [SerializeField] public int localID;
    static int lastAssignedLocalID = 0;

    string previousPacket;

    private void Awake()
    {
        //set the local id of each local object at the start of the game
        if (isLocallyOwned) localID = lastAssignedLocalID++;
    }

    public byte[] toPacket()
    {
        //create a string of data to send to other clients
        string objectData = ";" + NetworkManager.player.GetComponent<Gun>().GetDamage() + ";" + NetworkManager.packetID; //adds the gun damage and packet id to the packet

        if (NetworkManager.clients != null && NetworkManager.clients.Count > 0)
        {
            for (int i = 0; i < NetworkManager.clients.Count; i++)
            {
                //checks if a client has been shot
                if(NetworkManager.clients[i].GetIsShot())
                {
                    string temp = ";" + NetworkManager.clients[i].GetComponent<NetworkGameObject>().uniqueNetworkID.ToString(); //if a client has been shot add their id to the packet
                    temp += ";" + "1"; //add a shot event (1) to the packet
                    objectData += temp;
                }
            }
        }

        //add the client's position and rotation to the packet
        string returnVal = "Object Data;" + uniqueNetworkID + ";" +
                            (transform.position.x * 100) + ";" +
                            (-transform.position.z * 100) + ";" +
                            ((transform.position.y * 100) + 100) + ";" +
                            transform.rotation.x + ";" +
                            transform.rotation.z + ";" +
                            transform.rotation.y + ";" +
                            transform.rotation.w
                            ;

        //combine all the data into one string
       returnVal += objectData;

        return Encoding.ASCII.GetBytes(returnVal);
    }

    public void fromPacket(string packet)
    {
        //get packet data and split it into an array of strings
        string[] values = packet.Split(';');

        //assign the object's position and rotation values
        transform.position = new Vector3(
            float.Parse(values[2]) / 100, 
            (float.Parse(values[4]) - 100) / 100, 
            -float.Parse(values[3]) / 100
            );
        transform.rotation = new Quaternion(
            float.Parse(values[5]), 
            float.Parse(values[7]), 
            float.Parse(values[6]), 
            float.Parse(values[8])
            );

        //check if the same packet has not arrived multiple times by checking if all the values are the same, including the packet id
        if(previousPacket != packet)
        {
            if (values.Length > 10)
            {
                for (int i = 11; i < values.Length - 1; i++)
                {
                    //check if the packet has an event with the player's id
                    if (float.Parse(values[i]) == NetworkManager.player.GetComponent<NetworkGameObject>().uniqueNetworkID)
                    {
                        //check if the event is shot (1)
                        if (float.Parse(values[i + 1]) == 1)
                        {
                            NetworkManager.player.SetHealth(NetworkManager.player.GetHealth() - float.Parse(values[9])); //take away health from the player using the gun damage value from the packet
                        }
                    }
                }
            }
        }
        previousPacket = packet; //set the previous packet to the current packet to use to check the next packet
    }

    //get and set variables
    public bool GetIsLocallyOwned()
    {
        return isLocallyOwned;
    }

    public int GetUID()
    {
        return uniqueNetworkID;
    }

    public void SetUID(int uid)
    {
        uniqueNetworkID = uid;
    }

    public int GetLocalID()
    {
        return localID;
    }
}
