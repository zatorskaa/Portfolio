using System.Collections;
using System.Collections.Generic;
using UnityEditor.PackageManager;
using UnityEngine;
using static UnityEditor.Experimental.GraphView.GraphView;
using UnityEngine.UI;
using TMPro;

public class GameManager : MonoBehaviour
{
    static int numberOfPlayers;
    static int numberOfPlayersAlive;
    int roundsWon;
    public TMPro.TextMeshProUGUI roundsWonText;

    // Start is called before the first frame update
    void Start()
    {
        roundsWon = 0;
        roundsWonText.text = "Rounds Won: " + roundsWon;
    }

    // Update is called once per frame
    void Update()
    {
        //check if any new players have joined the game and add them to the list
        NetworkManager.players = FindObjectsOfType<Player>();
        NetworkManager.clients = new List<Player>();
        NetworkManager.player = NetworkManager.players[0];

        if (NetworkManager.players.Length != 0)
        {
            for (int i = 0; i < NetworkManager.players.Length; i++)
            {
                if (NetworkManager.players[i].transform.GetComponent<NetworkGameObject>().GetIsLocallyOwned())
                {
                    NetworkManager.player = NetworkManager.players[i];
                }
                else
                {
                    NetworkManager.clients.Add(NetworkManager.players[i]);
                }
            }
        }

        //check how many players are still alive
        numberOfPlayers = NetworkManager.players.Length;
        numberOfPlayersAlive = 0;

        for(int i = 0; i < numberOfPlayers; i++)
        {
            if (!NetworkManager.players[i].GetIsDead())
            {
                numberOfPlayersAlive++;
            }
        }
        Debug.Log("Number of players:" + numberOfPlayers);
        Debug.Log("Number of players alive:" + numberOfPlayersAlive);


        if (numberOfPlayers > 1)
        {
            if(numberOfPlayersAlive == 1)
            {
                //if the local player is the last one alive increase the number of rounds won
                if(!NetworkManager.player.GetIsDead())
                {
                    roundsWon++;
                    roundsWonText.text = "Rounds Won: " + roundsWon;
                }

                RestartLevel(); //start a new round
            }
        }
    }

    void RestartLevel()
    {
        //reset variable values for all players when a new round starts
        for (int i = 0; i < numberOfPlayers; i++)
        {
            NetworkManager.players[i].SetIsDead(false);
            NetworkManager.players[i].ResetHealth();
        }

        NetworkManager.player.Respawn();
    }
}
