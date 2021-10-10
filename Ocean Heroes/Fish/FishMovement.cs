using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FishMovement : MonoBehaviour
{
    #region Variables
    [SerializeField]
    private Transform[] waypoints; //store waypoints
    private int targetWaypoint; //store which waypoint to move to next


    private Vector3 distance; //store distance between fish and next waypoint
    [SerializeField]
    private float speed; //store speed of fish
    #endregion


    void Start()
    {
        targetWaypoint = 0; //initialize target waypoint to 0
        transform.position = new Vector3(waypoints[targetWaypoint].position.x, waypoints[targetWaypoint].position.y, waypoints[targetWaypoint].position.z); //move fish to first waypoint
    }


    void Update()
    {
        CalculateDistance();

        MoveFish();

        ChangeWaypoint();
    }


    void MoveFish()
    {
        transform.Translate(distance.normalized * speed * Time.deltaTime, Space.World); //move fish
        transform.rotation = Quaternion.LookRotation(distance.normalized); //rotate fish in direction of movement
    }

    void ChangeWaypoint()
    {
        if (Vector3.Distance(transform.position, waypoints[targetWaypoint].position) <= 0.1f) //chech if fish is close to next waypoint
        {
            if (targetWaypoint == waypoints.Length - 1)
            {
                targetWaypoint = 0; //if fish is at last waypoint, resest waypoint to 0
            }
            else
            {
                targetWaypoint++; //increase waypoint by 1
            }
        }
    }

    void CalculateDistance()
    {
        distance = waypoints[targetWaypoint].position - transform.position; //calculate distance between fish and next waypoint
    }
}
