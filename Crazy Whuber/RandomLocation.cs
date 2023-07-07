using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RandomLocation : MonoBehaviour
{
    /*
     first call ChooseRandomLocations() function to pick random locations for the pick up and drop off points
     then call the ReturnPickUpLocation() and ReturnDropOffLocation() functions which return the transform components
     */

    public Transform[] locations; //array to store locations on map

    Transform pickUpLocation;
    Transform dropOffLocation;

    int pickUpLocationNumber;
    int dropOffLocationNumber;

    //this function needs to be called each time before calling the functions to return the pick up and drop off locations
    public void ChooseRandomLocations()
    {
        //choose random locations for pick up and drop off
        pickUpLocationNumber = Random.Range(0, locations.Length);
        dropOffLocationNumber = Random.Range(0, locations.Length);

        if(pickUpLocationNumber == dropOffLocationNumber)
        {
            //Debug.Log("Recall function");
            ChooseRandomLocations(); //if pick up and drop off location is the same call the function again
        }
    }

    //returns the random pick up location
    public Transform ReturnPickUpLocation()
    {
        pickUpLocation = locations[pickUpLocationNumber];
        return pickUpLocation;
    }

    //return the random drop off location
    public Transform ReturnDropOffLocation()
    {
        dropOffLocation = locations[dropOffLocationNumber];
        return dropOffLocation;
    }

    ////testing functions
    //private void Update()
    //{
    //   if(Input.GetKeyDown(KeyCode.Space))
    //   {
    //       ChooseRandomLocations();

    //       Debug.Log(ReturnPickUpLocation());
    //       Debug.Log(ReturnDropOffLocation());
    //   }
    //}
}
