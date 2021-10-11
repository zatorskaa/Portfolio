using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PressurePlate : MonoBehaviour
{
    [HideInInspector]
    public bool isPressed; //stores if pressure plate is pressed
    public Material screenMaterial; //stores the material to show up on screen if pressure plate is pressed

    private void Start()
    {
        isPressed = false;
    }

    private void OnCollisionStay(Collision collision)
    {
        if (collision.collider.CompareTag("Player") || collision.collider.CompareTag("PickUp")) //check if player is standing on or an object is on the pressure plate
        {
            isPressed = true;
        }
    }

    private void OnCollisionExit(Collision collision)
    {
        isPressed = false; //set to false when not colliding with object
    }
}
