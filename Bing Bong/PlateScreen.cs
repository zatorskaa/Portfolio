using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlateScreen : MonoBehaviour
{
    //store materials for empty screen and screen showing tile
    [SerializeField]
    Material emptyScreen;
    [SerializeField]
    Material tileScreen;

    MeshRenderer meshRenderer;

    //store pressure plate scripts
    [SerializeField]
    PressurePlate[] pressurePlates = new PressurePlate[4];

    int platesPressed; //stores number of plates pressed


    private void Start()
    {
        meshRenderer = GetComponent<MeshRenderer>();
        meshRenderer.material = emptyScreen; //change screen material to empty screen

        platesPressed = 0;
    }

    private void Update()
    {
        CountPlatesPressed();

        CheckPlatesPressed();
    }

    
    void CountPlatesPressed()
    {
        for (int i = 0; i < pressurePlates.Length; i++)
        {
            if (pressurePlates[i].isPressed) //check if each pressure plate is currently pressed
            {
                platesPressed++; //increase the number of plates pressed
            }
        }
    }

    void CheckPlatesPressed()
    {
        if(platesPressed == pressurePlates.Length) //check if all four pressure plates are currently pressed
        {
            meshRenderer.material = tileScreen; //change the screen material to show the tile symbol
        }
        else if(platesPressed == 0) //check if no objects are on any pressure plates
        {
            meshRenderer.material = emptyScreen; //change screen material to empty screen
        }
        else
        {
            for(int i = 0; i < pressurePlates.Length; i++)
            {
                if(pressurePlates[i].isPressed) //check if any pressure plates are currently pressed
                {
                    meshRenderer.material = pressurePlates[i].screenMaterial; //change the screen material to show the grid symbol corresponding to that plate
                }
            }
        }

        platesPressed = 0; //reset count number of plates pressed
    }
}
