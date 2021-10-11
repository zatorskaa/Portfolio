using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/*
 The ‘InventorySystem’ class is used to store all the ‘inventorySlot’ components of the slot child objects of the inventory system.
 */


public class InventorySystem : MonoBehaviour
{
    /*
     The array stores all the ‘InventorySlot’ components of the child objects.
     */
    [HideInInspector]
    public InventorySlot[] inventorySlots; //stores inventory slots in inventory system

    /*
     The ‘Start()’ function gets all the ‘InventorySlot’ components of the child objects of the inventory system.
     */
    private void Start()
    {
        inventorySlots = GetComponentsInChildren<InventorySlot>(); //set array to inventory slot objects in inventory system child objects
    }
}
