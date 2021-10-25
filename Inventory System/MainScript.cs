using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;


/*
 The ‘MainScript’ class contains the functions for detecting mouse clicks to add/remove items to/from the inventory.
 */


public class MainScript : MonoBehaviour
{
    #region Variables

    /*
     The ‘environment’ variable stores the environment game object in the scene (this is set in the inspector). The ‘environmentScript’ variable stores the ‘Environment’ component of the environment object. 
    The ‘inventorySystem’ variable stores the ‘InventorySystem’ component of the inventory system object (set in the inspector).
     */
    [SerializeField]
    private GameObject environment; //stores the environment game object containing all items
    private Environment environmentScript; //stores the environment script component of the environment object
    [SerializeField]
    private InventorySystem inventorySystem; //stores the inventory system object

    [SerializeField]
    private Text inventoryContentsText; //stores text component to show invenotry contents

    /*
     The ‘currentItemSelected’ stores the item that was right clicked by the mouse or that is being dragged by left clicking the mouse. The ‘currentSlotSelected’ stores the slot that was right clicked by the mouse or left clicked and dragged by the mouse. 
    The ‘currentItemInSlot’ variable stores the item in the slot currently selected by right clicking the mouse or left clicking and dragging.
     */
    private Item currentItemSelected; //stores the item currently selected
    private InventorySlot currentSlotSelected; //stores the slot currently selected
    private string currentItemInSlot; //stores the name of the item stored in the current slot selected

    /*
     These variable store prefabs of items in the environment so they can be instantiated into the environment when an item is removed from the inventory.
     */
    [SerializeField]
    private GameObject arrowPrefab;
    [SerializeField]
    private GameObject bluePotionPrefab;
    [SerializeField]
    private GameObject purplePotionPrefab;
    [SerializeField]
    private GameObject torchPrefab;
    [SerializeField]
    private GameObject swordPrefab;
    [SerializeField]
    private GameObject bowPrefab;
    [SerializeField]
    private GameObject shieldPrefab;
    [SerializeField]
    private GameObject helmetPrefab;
    [SerializeField]
    private GameObject chestplatePrefab;
    #endregion

    /*
     The ‘Start()’ function gets the ‘Environment’ script component from the environment object.
     */
    private void Start()
    {
        environmentScript = environment.GetComponent<Environment>(); //gets the environment script component from the game objects
        inventoryContentsText.text = ""; //resets text
    }

    /*
     The ‘Update()’ function calls the ‘UpdateItems()’ function from the ‘Environment’ class to check if items have been added/removed to/from the environment, so their sprite positions can be updated. 
    If no mouse buttons are being clicked or held down it calls the ‘ResetItemPositions()’ function from the ‘Environment’ class to move item to the first empty locations in the environment. 
    ‘Update()’ calls two functions: ‘ItemClickedCheck()’ to check if the RMB or LMB was pressed on an item, and ‘SlotClickedCheck()’ to check if the RMB or LMB was pressed on a slot.
     */
    private void Update()
    {
        environmentScript.UpdateItems(); //calls functoin to get items in environment

        if(!Input.GetMouseButtonDown(0) && !Input.GetMouseButtonDown(1) && !Input.GetMouseButton(0)) //checks if left or right mouse buttons are being pressed
        {
            environmentScript.ResetItemPositions(); //resets item positions to a location in the environment if items have been removed
        }

        ItemClickedCheck();

        SlotClickedCheck();

    }


    /*
     This function checks if the mouse is hovering over an item sprite and if the RMB is pressed or the LMB is held down.
     It checks if the world coordinate mouse position is between the min/max positions on the x and y axis of the sprite for each item. If yes, it checks if the RMB is pressed and there is no other item selected (dragged), and if yes call ‘MoveItemToInventory()’ function to add item to the inventory. 
    Otherwise check if the LMB is pressed, if yes set the ‘currentItemSelected’ to that item. In the next frame, while the LMB is held down on that item call the ‘FollowMouse()’ function from the ‘Item’ class passing the x and y positions of the mouse as arguments to make the item follow the mouse. 
    In the frame where the LMB is released check if the mouse is hovering over a slot (if it is between the min/max x and y sprite positions), if yes call the ‘DropItemInInventory()’ function to add item to that slot.
     */
    private void ItemClickedCheck()
    {
        for (int i = 0; i < environmentScript.items.Length; i++) //for each item in the environment
        {
            if (
                Camera.main.ScreenToWorldPoint(Input.mousePosition).x > environmentScript.items[i].xMinPositionSprite && Camera.main.ScreenToWorldPoint(Input.mousePosition).x < environmentScript.items[i].xMaxPositionSprite
                &&
                Camera.main.ScreenToWorldPoint(Input.mousePosition).y > environmentScript.items[i].yMinPositionSprite && Camera.main.ScreenToWorldPoint(Input.mousePosition).y < environmentScript.items[i].yMaxPositionSprite
                ) //check if mouse is between the two x values for the item sprite and between the two y values for the item sprite
            {
                if (Input.GetMouseButtonDown(1) && currentItemSelected == null) //check if right mouse button is pressed
                {
                    currentItemSelected = environmentScript.items[i]; //stores the item that the mouse hovered over when RMB was pressed

                    MoveItemToInventory(); //call function to move item to inventory slot

                    currentItemSelected = null; //reset to empty value
                }
                else if (Input.GetMouseButtonDown(0)) //check if left mouse button is pressed
                {
                    currentItemSelected = environmentScript.items[i]; //set the selected item to the item where the mouse was left clicked
                }
                else if (Input.GetMouseButton(0) && currentItemSelected != null) //check if left mouse button is held down
                {
                    currentItemSelected.FollowMouse(Camera.main.ScreenToWorldPoint(Input.mousePosition).x, Camera.main.ScreenToWorldPoint(Input.mousePosition).y); //call function to move item and pass mouse positions as parameters
                }
                else if (Input.GetMouseButtonUp(0) && currentItemSelected != null) //check if left mouse button is released
                {
                    for (int x = 0; x < inventorySystem.inventorySlots.Length; x++) //for each slot sprite
                    {
                        if (
                            Camera.main.ScreenToWorldPoint(Input.mousePosition).x > inventorySystem.inventorySlots[x].xMinPositionSlot && Camera.main.ScreenToWorldPoint(Input.mousePosition).x < inventorySystem.inventorySlots[x].xMaxPositionSlot
                            &&
                            Camera.main.ScreenToWorldPoint(Input.mousePosition).y > inventorySystem.inventorySlots[x].yMinPositionSlot && Camera.main.ScreenToWorldPoint(Input.mousePosition).y < inventorySystem.inventorySlots[x].yMaxPositionSlot
                            ) //check if mouse is between the two x values for the slot sprite and between the two y values for the slot sprite
                        {
                            currentSlotSelected = inventorySystem.inventorySlots[x]; //stores the slot that the mouse hovered over when LMB was released

                            DropItemInInventory(); //call function to drag and drop item in inventory
                        }
                    }

                    currentItemSelected = null; //reset to empty value
                }
            }
        }
    }

    /*
     This function checks if the mouse is hovering over a slot and if the RMB is pressed or the LMB is held down.
     It checks if the world coordinate mouse position is between the min/max positions on the x and y axis of the sprite for each slot. 
     If yes, it checks if the RMB is pressed and there is no item selected (being dragged), and if yes call ‘RemoveItemFromInventory()’ function to remove the item from inventory and instantiate it into the environment. 
     Otherwise, check if the LMB is pressed, if yes call the ‘DragItemFromInventory()’ passing the x and y positions of the mouse as arguments to instantiate the items into the environment at the mouse position, and store the returned instantiated object in ‘currentItemSelected’. 
     The ‘currentItemSelected is then used when the ‘Update()’ function calls the ‘ItemClickedCheck’ in the next frame to make the item follow the mouse while the LMB is held down by calling the ‘FollowMouse()’ function.
     */
    private void SlotClickedCheck()
    {
        for (int i = 0; i < inventorySystem.inventorySlots.Length; i++) //for each slot in the inventory
        {
            if (
                Camera.main.ScreenToWorldPoint(Input.mousePosition).x > inventorySystem.inventorySlots[i].xMinPositionSlot && Camera.main.ScreenToWorldPoint(Input.mousePosition).x < inventorySystem.inventorySlots[i].xMaxPositionSlot
                &&
                Camera.main.ScreenToWorldPoint(Input.mousePosition).y > inventorySystem.inventorySlots[i].yMinPositionSlot && Camera.main.ScreenToWorldPoint(Input.mousePosition).y < inventorySystem.inventorySlots[i].yMaxPositionSlot
                ) //check if mouse is between the two x values for the slot sprite and between the two y values for the slot sprite
            {
                if (Input.GetMouseButtonDown(1) && currentItemSelected == null) //check if right mouse button is pressed
                {
                    currentSlotSelected = inventorySystem.inventorySlots[i]; //stores the slot that the mouse hovered over when RMB was pressed
                    currentItemInSlot = currentSlotSelected.containsItemType; //stores the type of object in the current slot selected

                    RemoveItemFromInventory(); //call function to move item to environment

                    currentSlotSelected = null; //reset to empty value
                    currentItemInSlot = null; //reset to empty value
                }
                else if (Input.GetMouseButtonDown(0)) //check if left mouse button is pressed
                {
                    currentSlotSelected = inventorySystem.inventorySlots[i]; //stores the slot that the mouse hovered over when RMB was pressed
                    currentItemInSlot = currentSlotSelected.containsItemType; //stores the type of object in the current slot selected

                    currentItemSelected = DragItemFromInventory(Camera.main.ScreenToWorldPoint(Input.mousePosition).x, Camera.main.ScreenToWorldPoint(Input.mousePosition).y).GetComponent<Item>();
                    /*call function to drag item from inventory passing the mouse position as parameters
                     * store the returned instantiated item game object
                     */
                }
            }
        }
    }

    /*
     This function is called by the ‘ItemClickedCheck()’ function if the RMB is pressed on an item. It checks what the next available slot is to add the item that was right clicked to the inventory. 
    It checks if a slot already contains that item type and if the maximum stack number hasn’t been reached, if yes add items from the environment stack to the slot until the slot is full and set the ‘numberOfItemsLeft’ to the number of items left in the environment stack. 
    Otherwise, check if a slot is empty and there are items still left to add, if yes set the slot values to the item values and destroy the item object (remove it from the environment/scene).
     */
    private void MoveItemToInventory()
    {
        int numberOfItemsLeft = currentItemSelected.numberOfItemsInStack; //sets variable to the number of items in stack

        for (int i = 0; i < inventorySystem.inventorySlots.Length; i++) //for each inventory slot
        {
            if (inventorySystem.inventorySlots[i].containsItemType == currentItemSelected.itemType && currentItemSelected.isStackable == true) //check if current slot contains the same item type as selected and the item is stackable
            {
                if(inventorySystem.inventorySlots[i].numberOfItemsInSlot < currentItemSelected.maxNumberInStack) //chceck if the number of items in slot is less than the max number for a stack of that object
                {
                    for(int x = 1; x <= currentItemSelected.numberOfItemsInStack; x++) //sets condition of for loop to repeat for the number of items in the item stack
                    {
                        if (inventorySystem.inventorySlots[i].numberOfItemsInSlot < currentItemSelected.maxNumberInStack) //checks for each item added that the slot is not full
                        {
                            inventorySystem.inventorySlots[i].numberOfItemsInSlot++; //add one item of that type to the current slot
                            numberOfItemsLeft--; //minus one item from the number of items left
                        }

                        //repeat loop until slot is full or no more items left to add
                    }

                    inventorySystem.inventorySlots[i].slotText.text = Convert.ToString(inventorySystem.inventorySlots[i].numberOfItemsInSlot); //change the text of the slot to update number of items

                    if (numberOfItemsLeft == 0) //check if any items are left to add to slot
                    {
                        Destroy(currentItemSelected.gameObject); //remove the item from the environment

                        break;

                        /*if there are no more items left destroy the object and break from the for loop
                         * otherwise the code will continue to the else if statement in the next loop to add the remaining items to a new slot
                         */
                    }
                    else
                    {
                        currentItemSelected.numberOfItemsInStack = numberOfItemsLeft;
                        currentItemSelected.numberInStackText.text = Convert.ToString(numberOfItemsLeft);

                        /*if there are items left in the stack change the numberOfItemsInStack and text to the number of items left to add
                         * the code will continue to the else if statement to add the remaining items to a new slot
                         */
                    }
                }
            }
            else if (inventorySystem.inventorySlots[i].isOccupied == false && numberOfItemsLeft > 0) //checks if current slot in loop is empty
            {
                inventorySystem.inventorySlots[i].isOccupied = true; //set boolean to true so program knows slot is not empty
                inventorySystem.inventorySlots[i].containsItemType = currentItemSelected.itemType; //set the item type in slot
                inventorySystem.inventorySlots[i].numberOfItemsInSlot = numberOfItemsLeft; //set the number of items in slot to number of items left - this will be the full stack of items selected if no items were added to a previous slot

                inventorySystem.inventorySlots[i].slotItemSprite.sprite = currentItemSelected.itemSprite; //changes sprite in slot to show item stored
                inventorySystem.inventorySlots[i].slotText.text = Convert.ToString(inventorySystem.inventorySlots[i].numberOfItemsInSlot); //changes text in slot to show number of items stored

                Destroy(currentItemSelected.gameObject); //remove the item from the environment

                break; //break from for loop
            }
            /*if all slots in inventory are full the item will remain in the environment
             *if stack is partially full in inventory items from selected stack will be added until slot is full and the rest of the stack will remain in the environment
             */
        }
    }

    /*
     This function is called by the ‘SlotClickedCheck()’ function if the RMB is pressed on a slot. It checks what type of item is stored in that slot and instantiates that item into the environment. 
     It also calls the ‘ResetSlot()’ function from the ‘InventorySlot’ class to set the slot values to default when an item is removed.
     */
    private void RemoveItemFromInventory()
    {
        for(int i = 0; i < environmentScript.itemLocations.Length; i++) 
        {
            if(environmentScript.itemLocations[i].containsItem == false) //for each item location in the environment check if it doesn't contain an item
            {
                Vector3 location = new Vector3(environmentScript.itemLocations[i].location.x, environmentScript.itemLocations[i].location.y, 0f); //set the position of the item to the first empty location

                switch (currentItemInSlot)
                {
                    case "Arrow":
                        arrowPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(arrowPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    case "Blue Potion":
                        bluePotionPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(bluePotionPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    case "Purple Potion":
                        purplePotionPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(purplePotionPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    case "Torch":
                        torchPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(torchPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    case "Sword":
                        swordPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(swordPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    case "Bow":
                        bowPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(bowPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    case "Shield":
                        shieldPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(shieldPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    case "Helmet":
                        helmetPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(helmetPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    case "Chestplate":
                        chestplatePrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                        Instantiate(chestplatePrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the first empty location in environment as a child object of environment

                        currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                        break;

                    default:
                        break;
                }

                break;
            }
        }
    }

    /*
     This function is called by the ‘ItemClickedCheck()’ function when the LMB is pressed. It works similarly to the ‘MoveItemToInventory()’ but instead of finding the first empty slot in inventory it adds the dragged item to the slot where the LMB was released. 
    First it checks if that slot contains the same item type already, if yes add items to that slot until it is full and then call local ‘AddItems()’ function to add the rest of the items to the first empty slot. 
    This code is in a separate function within the function because it is called more than once in different if/else statements so it reduces the amount of repeating code, and it needs to have access to the local variable ‘numberOfItemsLeft’. 
    Otherwise, if the slot is empty add the item to that slot. If the slot is occupied, move the current item in the slot to the first empty slot (or remove from inventory to environment by calling the ‘RemoveFromInventory()’ function if all slots are full) and add the dragged item to that slot. 
    The local ‘AddItems()’ function checks each inventory slot if it contains that item type to add the environment stack to it, or find an empty slot and add the item to that slot.
     */
    private void DropItemInInventory()
    {
        int numberOfItemsLeft = currentItemSelected.numberOfItemsInStack; //sets variable to the number of items in stack


        void AddItems()
        {
            for (int i = 0; i < inventorySystem.inventorySlots.Length; i++) //for each inventory slot
            {
                if (inventorySystem.inventorySlots[i].containsItemType == currentItemSelected.itemType && currentItemSelected.isStackable == true) //check if current slot contains the same item type as selected and the item is stackable
                {
                    if (inventorySystem.inventorySlots[i].numberOfItemsInSlot < currentItemSelected.maxNumberInStack) //chceck if the number of items in slot is less than the max number for a stack of that object
                    {
                        for (int x = 1; x <= currentItemSelected.numberOfItemsInStack; x++) //sets condition of for loop to repeat for the number of items in the item stack
                        {
                            if (inventorySystem.inventorySlots[i].numberOfItemsInSlot < currentItemSelected.maxNumberInStack) //checks for each item added that the slot is not full
                            {
                                inventorySystem.inventorySlots[i].numberOfItemsInSlot++; //add one item of that type to the current slot
                                numberOfItemsLeft--; //minus one item from the number of items left
                            }

                            //repeat loop until slot is full or no more items left to add
                        }

                        inventorySystem.inventorySlots[i].slotText.text = Convert.ToString(inventorySystem.inventorySlots[i].numberOfItemsInSlot); //change the text of the slot to update number of items

                        if (numberOfItemsLeft == 0) //check if any items are left to add to slot
                        {
                            Destroy(currentItemSelected.gameObject); //remove the item from the environment

                            break;

                            /*if there are no more items left destroy the object and break from the for loop
                             * otherwise the code will continue to the else if statement in the next loop to add the remaining items to a new slot
                             */
                        }
                        else
                        {
                            currentItemSelected.numberOfItemsInStack = numberOfItemsLeft;
                            currentItemSelected.numberInStackText.text = Convert.ToString(numberOfItemsLeft);

                            /*if there are items left in the stack change the numberOfItemsInStack and text to the number of items left to add
                             * the code will continue to the else if statement to add the remaining items to a new slot
                             */
                        }
                    }
                }
                else if (inventorySystem.inventorySlots[i].isOccupied == false) //checks if current slot in loop is empty
                {
                    inventorySystem.inventorySlots[i].isOccupied = true; //set boolean to true so program knows slot is not empty
                    inventorySystem.inventorySlots[i].containsItemType = currentItemSelected.itemType; //set the item type in slot
                    inventorySystem.inventorySlots[i].numberOfItemsInSlot = numberOfItemsLeft; //set the number of items in slot to number of items left - this will be the full stack of items selected if no items were added to a previous slot

                    inventorySystem.inventorySlots[i].slotItemSprite.sprite = currentItemSelected.itemSprite; //changes sprite in slot to show item stored
                    inventorySystem.inventorySlots[i].slotText.text = Convert.ToString(inventorySystem.inventorySlots[i].numberOfItemsInSlot); //changes text in slot to show number of items stored

                    Destroy(currentItemSelected.gameObject); //remove the item from the environment

                    numberOfItemsLeft = 0; //sets the number of items left to 0

                    break; //break from for loop
                }
            }
        }



        if (currentSlotSelected.containsItemType == currentItemSelected.itemType && currentItemSelected.isStackable == true) //check if current slot contains the same item type as selected and the item is stackable
        {
            //drag item to slot with same item type
            if (currentSlotSelected.numberOfItemsInSlot < currentItemSelected.maxNumberInStack) //chceck if the number of items in slot is less than the max number for a stack of that object
            {
                for (int x = 1; x <= currentItemSelected.numberOfItemsInStack; x++) //sets condition of for loop to repeat for the number of items in the item stack
                {
                    if (currentSlotSelected.numberOfItemsInSlot < currentItemSelected.maxNumberInStack) //checks for each item added that the slot is not full
                    {
                        currentSlotSelected.numberOfItemsInSlot++; //add one item of that type to the current slot
                        numberOfItemsLeft--; //minus one item from the number of items left
                    }

                    //repeat loop until slot is full or no more items left to add
                }

                currentSlotSelected.slotText.text = Convert.ToString(currentSlotSelected.numberOfItemsInSlot); //change the text of the slot to update number of items


                if (numberOfItemsLeft == 0) //check if any items are left to add to slot
                {
                    Destroy(currentItemSelected.gameObject); //remove the item from the environment

                    /*if there are no more items left destroy the object and break from the for loop
                        * otherwise the code will continue to the else statement to add the remaining items to a new slot or to a slot with the same item type
                        */
                }
                else
                {
                    currentItemSelected.numberOfItemsInStack = numberOfItemsLeft;
                    currentItemSelected.numberInStackText.text = Convert.ToString(numberOfItemsLeft);

                    /*if there are items left in the stack change the numberOfItemsInStack and text to the number of items left to add
                         * the code will continue to the for loop to add the remaining items to a new slot
                    */


                    //add remaining items to next availiable slot
                    AddItems(); //call local function to add items to inventory
                }
            }
            else
            {
                //if current slot containing same item type is full add items to first available slot
                AddItems(); //call local function to add items to inventory
            }
        }
        else if (currentSlotSelected.isOccupied == false) //checks if current slot in loop is empty
        {
            //drag item to empty slot
            currentSlotSelected.isOccupied = true; //set boolean to true so program knows slot is not empty
            currentSlotSelected.containsItemType = currentItemSelected.itemType; //set the item type in slot
            currentSlotSelected.numberOfItemsInSlot = numberOfItemsLeft; //set the number of items in slot to number of items left - this will be the full stack of items selected if no items were added to a previous slot

            currentSlotSelected.slotItemSprite.sprite = currentItemSelected.itemSprite; //changes sprite in slot to show item stored
            currentSlotSelected.slotText.text = Convert.ToString(currentSlotSelected.numberOfItemsInSlot); //changes text in slot to show number of items stored

            Destroy(currentItemSelected.gameObject); //remove the item from the environment
        }
        else if(currentSlotSelected.isOccupied == true)
        {
            //drag item to occupied slot
            bool itemMoved = false; //sets variable to

            //move item from current slot to first available slot
            for(int i = 0; i < inventorySystem.inventorySlots.Length; i++)
            {
                if(inventorySystem.inventorySlots[i].isOccupied == false) //check if slot is available
                {
                    inventorySystem.inventorySlots[i].isOccupied = true; //set boolean to true so program knows new slot is not empty
                    inventorySystem.inventorySlots[i].containsItemType = currentSlotSelected.containsItemType; //set the item type in new slot
                    inventorySystem.inventorySlots[i].numberOfItemsInSlot = currentSlotSelected.numberOfItemsInSlot; //set the number of items in new slot from previous slot

                    inventorySystem.inventorySlots[i].slotItemSprite.sprite = currentSlotSelected.slotItemSprite.sprite; //changes sprite in new slot to show item stored
                    inventorySystem.inventorySlots[i].slotText.text = Convert.ToString(inventorySystem.inventorySlots[i].numberOfItemsInSlot); //changes text in slot to show number of items stored

                    itemMoved = true; //set itemMoved to true if item has been moved to new slot

                    break; //exit for loop
                }
                else
                {
                    itemMoved = false;
                }
            }

            if(itemMoved == false) //check if item has been moved to new slot
            {
                currentItemInSlot = currentSlotSelected.containsItemType; //stores the type of object in the current slot selected

                RemoveItemFromInventory(); //call function to remove item from current slot in inventory so new item can be added
            }

            currentSlotSelected.isOccupied = true;
            currentSlotSelected.containsItemType = currentItemSelected.itemType; //set the item type in slot
            currentSlotSelected.numberOfItemsInSlot = numberOfItemsLeft; //set the number of items in slot to number of items in stack

            currentSlotSelected.slotItemSprite.sprite = currentItemSelected.itemSprite; //changes sprite in slot to show item stored
            currentSlotSelected.slotText.text = Convert.ToString(currentSlotSelected.numberOfItemsInSlot); //changes text in slot to show number of items stored

            Destroy(currentItemSelected.gameObject); //remove the item from the environment
        }
    }

    /*
     This function is called by the ‘SlotClickedCheck’ when the LMB is pressed. It works similarly to the ‘RemoveItemFromInventory()’ function but instead of instantiating the item at a location in the environment, it instantiates the item at the position of the mouse so it can be dragged. 
     It takes the x an y positions of the mouse as parameters and instantiates the item at those positions. It also returns the instantiated object which is stored in ‘currentItemSelected’ so it can be dragged while the LMB is held down. 
     The function checks the type of item stored in that inventory slot and instantiates the prefab for that item type.
     */
    private GameObject DragItemFromInventory(float xMousePosition, float yMousePosition)
    {
        Vector3 location = new Vector3(xMousePosition, yMousePosition, 0f); //set the position of the item to mouse position when LMB was clicked on slot
        GameObject instantiatedItem; //stores item game object that is instantiated

        switch (currentItemInSlot)
        {
            case "Arrow":
                arrowPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(arrowPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            case "Blue Potion":
                bluePotionPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(bluePotionPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            case "Purple Potion":
                purplePotionPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(purplePotionPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            case "Torch":
                torchPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(torchPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            case "Sword":
                swordPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(swordPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            case "Bow":
                bowPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(bowPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            case "Shield":
                shieldPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(shieldPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            case "Helmet":
                helmetPrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(helmetPrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            case "Chestplate":
                chestplatePrefab.GetComponent<Item>().UpdateItemInfo(currentSlotSelected.numberOfItemsInSlot); //call function to change the numberOfItemsInStack to the number of items in the inventory slot

                instantiatedItem = Instantiate(chestplatePrefab, location, transform.rotation, environment.transform); //instantiate prefab of item in slot at the mouse position as a child object of environment

                currentSlotSelected.ResetSlot(); //call function to set variables of inventory slot to default

                return instantiatedItem; //return the instantiated game object to the update function

            default:
                break;
        }

        return null; //if there is no item game object returned return nothing
    }

    /*
     This function is called by the built-in ‘OnClick()’ function on the UI button. It is used to print the contents of the inventory to the console in Unity. A dictionary stores the item types as keys and the number of each item type in the inventory as the values for those keys. 
     It checks what item type is stored in each slot and adds the number of that item to the value stored in the dictionary for that item type. It then prints each item type and number (if there is at least one in the inventory) to the console.
     */
    public void PrintContents()
    {
        //function is called by OnClick() on the button

        Dictionary<string, int> numberOfItemTypes = new Dictionary<string, int>()
        {
            {"Arrow", 0 },
            {"Blue Potion", 0 },
            {"Purple Potion", 0 },
            {"Torch", 0 },
            {"Sword", 0},
            {"Bow", 0 },
            {"Shield", 0 },
            {"Helmet", 0 },
            {"Chestplate", 0 }
        };
        //dictionary stoes the number of items in inventory for each item type - item type is the key and number of items is the value


        for(int i = 0; i < inventorySystem.inventorySlots.Length; i++) //for each inventory slot
        {
            if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(0).Key) //checks if item in slot is equal to 1st key in dictionary - Arrow
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(0).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 1st key
            }
            else if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(1).Key) //checks if item in slot is equal to 2nd key in dictionary - Blue Potion
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 2nd key
            }
            else if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(2).Key) //checks if item in slot is equal to 3rd key in dictionary - Purple Potion
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(2).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 3rd key
            }
            else if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(3).Key) //checks if item in slot is equal to 4th key in dictionary - Torch
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(3).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 4th key
            }
            else if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(4).Key) //checks if item in slot is equal to 5th key in dictionary - Sword
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(4).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 5th key
            }
            else if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(5).Key) //checks if item in slot is equal to 6th key in dictionary - Bow
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(5).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 6th key
            }
            else if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(6).Key) //checks if item in slot is equal to 7th key in dictionary - Shield
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(6).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 7th key
            }
            else if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(7).Key) //checks if item in slot is equal to 8th key in dictionary - Helmet
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(7).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 8th key
            }
            else if (inventorySystem.inventorySlots[i].containsItemType == numberOfItemTypes.ElementAt(8).Key) //checks if item in slot is equal to 9th key in dictionary - Chestplate
            {
                numberOfItemTypes[numberOfItemTypes.ElementAt(8).Key] += inventorySystem.inventorySlots[i].numberOfItemsInSlot; //adds the number of items in that slot to dictionary value at the 9th key
            }
        }


        for(int i = 0; i < numberOfItemTypes.Count; i++)
        {
            if(numberOfItemTypes[numberOfItemTypes.ElementAt(i).Key] != 0) //if the number of items for that item type is not 0
            {
                Debug.Log(numberOfItemTypes.ElementAt(i).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(i).Key] + ")"); //print the number of each item to the debug log
            }
        }

        //show inventory contents on screen
        inventoryContentsText.text = numberOfItemTypes.ElementAt(0).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(0).Key] + ")" + "   " +
                                     numberOfItemTypes.ElementAt(1).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] + ")" + "   " +
                                     numberOfItemTypes.ElementAt(2).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] + ")" + "   " +
                                     numberOfItemTypes.ElementAt(3).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] + ")" + "   " +
                                     numberOfItemTypes.ElementAt(4).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] + ")" + "   " +
                                     numberOfItemTypes.ElementAt(5).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] + ")" + "   " +
                                     numberOfItemTypes.ElementAt(6).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] + ")" + "   " +
                                     numberOfItemTypes.ElementAt(7).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] + ")" + "   " +
                                     numberOfItemTypes.ElementAt(8).Key + " (" + numberOfItemTypes[numberOfItemTypes.ElementAt(1).Key] + ")";
    }
}