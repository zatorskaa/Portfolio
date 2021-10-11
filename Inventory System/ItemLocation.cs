using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/*
 The ‘ItemLocation’ class stores the locations in the environment where the items should be placed and appear on screen to keep them organised and not overlapping each other. 
 Each empty item location object contains the ‘ItemLocation’ script to store its position and whether an item is in that location. Each item location is an empty game object that is used to set the positions for each item object in the environment.
 */


public class ItemLocation : MonoBehaviour
{
    /*
     The Vector2 variable stores the x and y position of the empty game object so it can be used to set the position for items in the environment. The z position is not stored and used since everything is in 2D so the z values do not need to be changed. 
     The bool variable is used to check whether an item is placed in that location.
     */
    [HideInInspector]
    public Vector2 location ; //stores the x and y position of the item location transform
    [HideInInspector]
    public bool containsItem; //bool stores whether there is an item at the current location in the enivornment

    /*
     The function sets the ‘location’ variable to the x and y positions of the empty game object and the ‘containsItem’ bool is set to false as default for all item locations. This is done in the ‘Awake()’ function so that the location values can be stored before any item positions are set in the ‘Start()’ functions.
     */
    private void Awake() //awake function is called before start when the game is loaded so the location positions will be stored before items are moved there
    {
        location = new Vector2(transform.position.x, transform.position.y); //gets the x and y position
        containsItem = false; //sets bool to false
    }
}
