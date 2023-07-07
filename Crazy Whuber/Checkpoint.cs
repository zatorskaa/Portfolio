using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Checkpoint : MonoBehaviour
{
    [SerializeField]
    RaceCheckpoints raceCheckpoints;

    bool isHit;

    private void Start()
    {
        isHit = false;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.CompareTag("Player") && !isHit)
        {
            isHit = true;

            //disable current checkpoint when player reaches it and enable next checkpoint
            gameObject.GetComponent<BoxCollider2D>().enabled = false;
            gameObject.GetComponent<SpriteRenderer>().enabled = false;

            raceCheckpoints.currentCheckpoint++;

            if (raceCheckpoints.currentCheckpoint < raceCheckpoints.checkpoints.Length)
            {
                raceCheckpoints.checkpoints[raceCheckpoints.currentCheckpoint].GetComponent<BoxCollider2D>().enabled = true;
                raceCheckpoints.checkpoints[raceCheckpoints.currentCheckpoint].GetComponent<SpriteRenderer>().enabled = true;
            }
        }
    }
}
