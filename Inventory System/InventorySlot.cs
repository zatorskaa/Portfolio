using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


/*
 The ‘InventorySlots’ class defines the properties of an inventory slot: whether it contains an item, what item type it contains and how many items it contains. 
It also contains the min/max x and y positions of the sprite of the slot, as well as the image component of the child object to display the sprite of the item being stored there. Each slot object also stores the text component of its child object to show how many items are stored in that slot.
 */


public class InventorySlot : MonoBehaviour
{
    #region Variables
    /*
     These variables store whether the slot contains an item, what type of item it contains and the number of items it contains.
     */
    [HideInInspector]
    public bool isOccupied; //variable to check if each item slot is occupied by an item
    [HideInInspector]
    public string containsItemType; //variable to check what item is stored in the slot
    [HideInInspector]
    public int numberOfItemsInSlot; //variable to check how many items are stored in the slot

    /*
     These variables store the components of the slot and its child objects. It stores the rectTransform and sprite of the slot, which are used to calculate the min/max x and y positions of the slot sprite to detect whether the mouse is hovering over the slot. 
    The image and text components of the child objects are also stored to display the type of item and number of items being stored in that slot.
     */
    [HideInInspector]
    public Image slotItemSprite; //stores image component to change item sprite stored in slot
    [HideInInspector]
    public Text slotText; //stores text component to change number of items stored in slot
    private RectTransform rectTransform; //stores rect transform component of inventory slot
    private Sprite slotSprite; //stores sprite from the image component of inventory slot

    /*
     These variables store the float values of the positions of the four corners of the slot sprite.
     */
    [HideInInspector]
    public float xMinPositionSlot; //stores the position where the sprite starts on the left
    [HideInInspector]
    public float xMaxPositionSlot; //stores the position where the sprite ends on the right
    [HideInInspector]
    public float yMinPositionSlot; //stores the position where the sprite starts on the bottom
    [HideInInspector]
    public float yMaxPositionSlot; //stores the position where the sprite ends at the bottom
    #endregion

    /*
     The ‘Start()’ function calls three functions: ‘GetSlotComponents()’, ‘GetSlotPositions()’ and ‘ResetSlot()’.
     */
    private void Start()
    {
        GetSlotComponents();

        GetSlotPositions();

        ResetSlot(); //calls function to set default values of variables when game is loaded
    }

    /*
     This function is called by the ‘Start()’ function when the game loads to store the sprite, image and text components of the slot and its child objects.
     */
    private void GetSlotComponents()
    {
        slotItemSprite = transform.GetChild(0).GetComponent<Image>(); //gets the image component of the child object

        slotText = transform.GetChild(1).GetComponent<Text>(); //gets the text component of child object

        rectTransform = GetComponent<RectTransform>(); //gets the rect transform of inventory slot
        slotSprite = GetComponent<Image>().sprite; //gets the sprite of inventory slot
    }

    /*
     This function is called by the ‘Start()’ function to calculate the min/max x and y positions of the slot sprite. The ‘slotSprite’ variable is used to get the width/height of the slot sprite (divided by 2 since the ‘rectTransform’ returns the pivot point at the centre of the sprite, 
     multiplied by the scale on the x/y axis of the object) plus the position of the ‘rectTransform’ in world space coordinates (the ‘ScreenToWorldPosition()’ function converts the ‘rectTransform’ position on screen/canvas to world space coordinates). 
     */
    private void GetSlotPositions()
    {
        //calculates positions of sprite
        xMinPositionSlot = Camera.main.ScreenToWorldPoint(rectTransform.position).x - (slotSprite.bounds.size.x / 2 * transform.localScale.x); //calculates the minimum x position of the slot by taking its transform in the centre and minus half the width of the slot sprite
        xMaxPositionSlot = Camera.main.ScreenToWorldPoint(rectTransform.position).x + (slotSprite.bounds.size.x / 2 * transform.localScale.x); //calculates the maximum x position of the slot by taking its transform in the centre and add half the width of the slot sprite
        yMinPositionSlot = Camera.main.ScreenToWorldPoint(rectTransform.position).y - (slotSprite.bounds.size.y / 2 * transform.localScale.y); //calculates the minimum y position of the slot by taking its transform in the centre and minus half the height of the slot sprite
        yMaxPositionSlot = Camera.main.ScreenToWorldPoint(rectTransform.position).y + (slotSprite.bounds.size.y / 2 * transform.localScale.y); //calculates the maximum y position of the slot by taking its transform in the centre and add half the height of the slot sprite
    }

    /*
     This public function defaults all the slot variables that store values about the item in the inventory slot. It is called by the ‘Start()’ function to default all slots to empty at the start of the game, and from the ‘MainScript’ class when an item is removed from that inventory slot.
     */
    public void ResetSlot()
    {
        isOccupied = false; //default each slot to unoccupied
        containsItemType = ""; //default each slot to no item type
        numberOfItemsInSlot = 0; //default each slot to 0 items

        slotItemSprite.sprite = null; //sets image (item sprite) to none
        slotText.text = "0"; //sets text to 0
    }
}
