using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tile : MonoBehaviour
{
    [HideInInspector]
    public bool isCorrect; //used to check if the tile is in the correct place
    [HideInInspector]
    public int currentGridSquare; //used to check which grid square the tile is currently on

    [SerializeField] 
    int correctGridSquare; //stores which grid square the tile should be on the solve the puzzle

    private void Awake()
    {
        isCorrect = false; //initialize variable
    }

    private void Update()
    {
        CheckLocation();
    }

    public void MoveToLocation(GridSquare gridSquare) //function moves tile to the correct location
    {
        transform.position = new Vector3(gridSquare.location.x, gridSquare.location.y, gridSquare.location.z); //set the transform of the tile to the location values of the grid square
    }

    void CheckLocation() //function checks if tile is in the correct place
    {
        if(currentGridSquare == correctGridSquare) //checks if the grid square that the tile is currently on is the correct one for the puzzle solution
        {
            isCorrect = true; //set variable to true
            Debug.Log("Correct Location"); //temporary output to console to check function works
        }
        else
        {
            isCorrect = false;
        }
    }
}
