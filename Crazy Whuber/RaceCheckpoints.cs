using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RaceCheckpoints : MonoBehaviour
{
    public Transform[] checkpoints;

    [HideInInspector]
    public int currentCheckpoint;

    [Header("this variable is not mandatory to be filled, only if its a race against ai")]
    [SerializeField]
    //this will get the player car
    CarController playerCar = null;

    [SerializeField]
    ScoringSystem scoringSystem;

    public bool raceFinished;


    private void Start()
    {
        currentCheckpoint = 0;
        raceFinished = false;

        //enable first checkpoint and disable the others
        for(int i = 0; i < checkpoints.Length; i++)
        {
            checkpoints[i].GetComponent<BoxCollider2D>().enabled = false;
            checkpoints[i].GetComponent<SpriteRenderer>().enabled = false;
        }


        checkpoints[currentCheckpoint].GetComponent<BoxCollider2D>().enabled = true;
        checkpoints[currentCheckpoint].GetComponent<SpriteRenderer>().enabled = true;
    }

    private void Update()
    {
        if(!raceFinished)
        {
            //check if at last checkpoint
            if (currentCheckpoint == checkpoints.Length)
            {
                scoringSystem.CalculateRaceScore();
                raceFinished = true;
            }
        }
    }

    public float ReturnPlayerDistanceFromCheckPoint() {
        return Vector2.Distance(checkpoints[currentCheckpoint].position, playerCar.transform.position); 
    }

}
