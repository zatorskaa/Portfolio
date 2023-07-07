using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/*
    call the CalculateTime() function after calling the functions in RandomLocation class
 */

public class TimeSystem : MonoBehaviour
{
    [SerializeField]
    RandomLocation randomLocation; //store random locations script

    //store pick up and drop off locations for calculating distance
    Transform pickUpLocation;
    Transform dropOffLocation;

    //store the distance between locations and the time for the player to get between them
    float distance;
    float time;
    [SerializeField]
    float timePerDistance;
    [HideInInspector]
    public float timeLeft;

    public Text timeText; //store text component to show time left

    [Header("Race")]
    [SerializeField]
    bool race;

    public float raceTime;

    private void Start()
    {
        if(!race)
        {
            timeText.gameObject.SetActive(false);
        }
        else
        {
            timeText.gameObject.SetActive(true);
            timeText.text = raceTime.ToString();
        }
    }

    void CalculateDistance()
    {
        //call functions to get current pick up and drop off locations
        pickUpLocation = randomLocation.ReturnPickUpLocation();
        dropOffLocation = randomLocation.ReturnDropOffLocation();

        //calculate distnace between pick up and drop off points
        Vector3 distanceVector = new Vector3(pickUpLocation.position.x, pickUpLocation.position.y, 0f) - new Vector3(dropOffLocation.position.x, dropOffLocation.position.y, 0f);
        distance = distanceVector.magnitude;
    }

    public float CalculateTime()
    {
        CalculateDistance();

        //calculate how much time the player has to get between the two locations
        time = distance * timePerDistance;
        timeLeft = time; //reset timeLeft to the calculated time

        return time;
    }

    private void Update() 
    {
        if(!race)
        {
            //decrease time left
            timeLeft -= Time.deltaTime;

            if (timeText.gameObject.activeSelf)
            {
                timeText.text = "Time Left: " + ((int)timeLeft).ToString(); //show time left on screen
            }
        }
        else
        {
            raceTime -= Time.deltaTime;

            timeText.text = "Time Left: " + ((int)raceTime).ToString();
        }
    }
}
