using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/*
The ‘Item’ class defines the properties of each item: what type of object it is, whether it is stackable, the maximum number that a stack can contain and the number of items in the current stack in the environment.
It also contains the min/max x and ypositions of the sprite (as well as the sprite itself to find the positions) for that item object as float values, which are used by the main function to detect whether the mouse is hovering and being clicked on the item.
If the item is stackable the class will also store the text component in the child object to display the number of items in the stack. Each item object has its own ‘Item’ script attached to it, to store the values for that specific item.
 */


public class Item : MonoBehaviour
{
    #region Variables

    /*
     These variables store values that define the type of item, whether it is stackable, and the number of items in the stack as well as the maximum stack number for that item type. These are used in the ‘MainScript’ class to check the properties of an item when it is moved to/from the inventory/environment.
     */
    public string itemType; //stores the type of item
    public bool isStackable; //stores if the item can be stacked
    public int maxNumberInStack; //stores the maximum number of items in a stack
    public int numberOfItemsInStack; //stores the number of items in current stack in environment

    /*
     These variables store the float values of the min/max x and y positions of the sprite for that item. They are used by the ‘MainScript’ class to check whether the mouse is hovering over an item when the LMB/RMB are pressed.
     */
    [HideInInspector]
    public float xMinPositionSprite; //stores the position where the sprite starts on the left
    [HideInInspector]
    public float xMaxPositionSprite; //stores the position where the sprite ends on the right
    [HideInInspector]
    public float yMinPositionSprite; //stores the position where the sprite starts at the bottom
    [HideInInspector]
    public float yMaxPositionSprite; //stores the position where the sprite ends at the top

    /*
     These variables store the components of the item objects/child objects. The ‘numberInStackText’ stores the text component of the item’s text child object, which is used to display the number of items in the current stack if the object is stackable. 
     The ‘itemSprite’ variable stores the sprite component of the item object, which is used to calculate the four boundary corner points for detecting mouse clicks hovering over the item, as well as storing the sprite for that item to add the sprite to an inventory slot when the item is added to inventory.
     */
    [HideInInspector]
    public Text numberInStackText; //stores text component
    [HideInInspector]
    public Sprite itemSprite; //stores item sprite
    #endregion


    /*
     The ‘Start()’ function is called when the game is loaded. In this function the ‘StackableCheck()’ function is called, and the ‘itemSprite’ is set to the sprite stored in the sprite renderer of the item object.
     */
    private void Start()
    {
        itemSprite = GetComponent<SpriteRenderer>().sprite; //set variable to the sprite in sprite renderer

        StackableCheck(); //calls function to check if item is stackable

        UpdateItemLocation(); //call function to get sprite positions of item
    }


    /*
     This public function calculates the min/max x and y values of the sprite by getting the size of the sprite on the x and y axis (divided by 2 since the transform.position returns the pivot point at the centre of the sprite, 
     multiplied by the scale on the x/y axis of the object since not all objects have a scale of 1 so the size of the sprite will change with the scale) and add/minus this to the current transform.position of the item object. 
     It is called in the ‘Start()’ function of the ‘Item’ class to get the positions for each item when the game is loaded, and it is called from the ‘MainScript’ class when an object is instantiated into the environment from the inventory.
     */
    public void UpdateItemLocation()
    {
        //calculates min/max x and y positions of item sprite

        xMinPositionSprite = transform.position.x - (itemSprite.bounds.size.x / 2 * transform.localScale.x); //set min x position to the pivot point on the centre of the sprite minus half the width
        xMaxPositionSprite = transform.position.x + (itemSprite.bounds.size.x / 2 * transform.localScale.x); //set max x position to the pivot point on the centre of the sprite plus half the width
        yMinPositionSprite = transform.position.y - (itemSprite.bounds.size.y / 2 * transform.localScale.y); //set min y position to the pivot point on the centre of the sprite minus half the height
        yMaxPositionSprite = transform.position.y + (itemSprite.bounds.size.y / 2 * transform.localScale.y); //set max y position to the pivot point on the centre of the sprite plus half the height
    }

    /*
     This public function updates the number of items in the current stack in the environment and the text object to that number if the item is stackable. 
     It is called by the ‘MainScript’ class when an item is instantiated into the environment from the inventory, where an integer argument is passed to set the number of items in the stack.
     */
    public void UpdateItemInfo(int numberOfItems)
    {
        //sets values of item

        numberOfItemsInStack = numberOfItems; //sets the number of items in stack to the number of items passed into the function from the main script

        if (isStackable) //if item is stackable
        {
            numberInStackText = GetComponentInChildren<Text>(); //get the text component of the item's child object
            numberInStackText.text = Convert.ToString(numberOfItemsInStack); //set the numberInStackText text to the number of items in the current stack
        }
    }

    /*
     This private function is called by the ‘Start()’ function in the ‘Item’ class when the game is loaded to check if an item is stackable, if yes it gets the text component of the item’s child object and sets it to the number of items in the stack, if not it defaults the values to 1.
     */
    private void StackableCheck()
    {

        if (isStackable) //if item is stackable
        {
            numberInStackText = GetComponentInChildren<Text>(); //get the text component of the item's child object
            numberInStackText.text = Convert.ToString(numberOfItemsInStack); //set the numberInStackText text to the number of items in the current stack
        }
        else
        {
            //if item is not stackable default values to 1
            numberOfItemsInStack = 1;
            maxNumberInStack = 1;
        }
    }

    /*
     This public function is called from the ‘MainScript’ class, which passes two float arguments (the x and y positions of the mouse on screen), when the LMB on the mouse is pressed over the item. 
     It sets the item’s transform.position to the arguments passed so the item follows the mouse position while the LMB is being pressed from the ‘MainScript’ class.
     */
    public void FollowMouse(float x, float y)
    {
        transform.position = new Vector3(x, y, transform.position.z); //move item to mouse position from passed parameters
    }
}
