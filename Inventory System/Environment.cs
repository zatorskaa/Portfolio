using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/*
 The ‘Environment’ class stores arrays of ‘Item’ class objects and ‘ItemLocation’ class objects to set the positions of items to specific locations in the environment to keep everything organised.
 */


public class Environment : MonoBehaviour
{
    /*
     The ‘itemLocations’ array stores all the ‘ItemLocation’ script components of the item location child objects of the environment. The ‘items’ array stores all the ‘Item’ script components of the item child objects of the environment.
     */
    [HideInInspector]
    public ItemLocation[] itemLocations; //array stores all item location scripts in environment
    [HideInInspector]
    public Item[] items; //array stores all items in environment

    /*
     The ‘Start()’ function sets the ‘itemLocations’ array to the script components of the item location child objects of the environment. It also calls the ‘ResetItemPositions()’ and ‘UpdateItems()’ functions.
     */
    private void Start()
    {
        itemLocations = GetComponentsInChildren<ItemLocation>(); //gets all the ItemLocation scripts in child objects of environment

        ResetItemPositions(); //calls function when game is loaded to move items to correct positions

        UpdateItems(); //calls function to get positions of each item's sprite when game is loaded
    }

    /*
     This public function sets the ‘items’ array to the script components of the item child objects of the environment, and sets the position of each item to an item location in the environment. 
     If an item position is set to an item location the ‘containsItem’ bool for that ‘itemLocation’ object is set to true, and the rest of the ‘itemLocation’ objects have the bool set to false. This is to check whether an item’s position can be set to each location in the environment.
     */
    public void ResetItemPositions()
    {
        items = GetComponentsInChildren<Item>(); //gets all the Item scripts in child objects of environment

        for (int i = 0; i < items.Length; i++)
        {
            //sets all item positions to a location in the environment and sets containsItem for those locations to true
            items[i].transform.position = new Vector3(itemLocations[i].location.x, itemLocations[i].location.y, transform.position.z);
            itemLocations[i].containsItem = true;
        }
        for(int i = items.Length; i < itemLocations.Length; i++)
        {
            //sets all the other item locations containsItem to false
            itemLocations[i].containsItem = false;
        }
    }

    /*
     This public function gets the ‘Item’ scripts from the child item objects in the environment when it is called to check if any items have been moved to/from the inventory. 
     It then calls the ‘UpdateItemLocation()’ function from the ‘Item’ script for each item in the array to set the sprite positions if the items have moved in the environment.
     */
    public void UpdateItems()
    {
        items = GetComponentsInChildren<Item>(); //sets the array to the items currently stored in the environment

        for (int x = 0; x < items.Length; x++)
        {
            items[x].UpdateItemLocation(); //sets the variables storing the item sprite positions to new positions if items have moved in the environment
        }
    }
}
