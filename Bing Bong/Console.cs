using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Console : Grid
{
    bool isInRange; //used to check if player is standing in fron of the console

    [SerializeField]
    Material[] screenMaterial; //store materials for console screen to show which tile is selected and switch between them
    [SerializeField]
    GameObject screen; //store the console screen game object
    MeshRenderer meshRenderer; //store the mesh renderer component of the screen to change materials

    private void Start()
    {
        meshRenderer = screen.GetComponent<MeshRenderer>();
        meshRenderer.material = screenMaterial[0]; //set material of screen to first one in array (first tile)
        isInRange = false; //initialize variable
    }


    private void Update()
    {
        if (isInRange && !CheckPuzzleSolved()) //if the player is in front of the console call function to chek for input
        {
            CheckInput();
        }

        if(CheckPuzzleSolved() && !roomFinished) //if the puzzle has been solved and the code number is not shown
        {
            ShowCodeNumber(); //call function to show code number
        }
    }


    void CheckInput() //function checks for user input to move tiles on the grid
    {
        if (Input.GetKeyDown(KeyCode.I)) //move up
        {
            if(tiles[selectedTile].currentGridSquare - 6 >= 0) //check if tile is not on the top row of the grid
            {
                tiles[selectedTile].currentGridSquare -= 6; //minus 6 from the current grid square of the tile (since the grid is 6x6)
                tiles[selectedTile].MoveToLocation(gridSquares[tiles[selectedTile].currentGridSquare]); //call function to move the tile to the new grid square
            }
        }
        else if (Input.GetKeyDown(KeyCode.K)) //move down
        {
            if (tiles[selectedTile].currentGridSquare + 6 <= 35) //check if tile is not on the bottom row of the grid
            {
                tiles[selectedTile].currentGridSquare += 6; //add 6 to the current grid square of the tile (since the grid is 6x6)
                tiles[selectedTile].MoveToLocation(gridSquares[tiles[selectedTile].currentGridSquare]); //call function to move the tile to the new grid square
            }
        }
        else if (Input.GetKeyDown(KeyCode.J)) //move left
        {
            if (tiles[selectedTile].currentGridSquare != 0 && tiles[selectedTile].currentGridSquare != 6 && tiles[selectedTile].currentGridSquare != 12 &&
                tiles[selectedTile].currentGridSquare != 18 && tiles[selectedTile].currentGridSquare != 24 && tiles[selectedTile].currentGridSquare != 30)
                //check if tile is on the left column of the grid
            {
                tiles[selectedTile].currentGridSquare--; //minus one from the current grid square
                tiles[selectedTile].MoveToLocation(gridSquares[tiles[selectedTile].currentGridSquare]); //call function to move the tile to the new grid square
            }
        }
        else if (Input.GetKeyDown(KeyCode.L)) //move right
        {
            if (tiles[selectedTile].currentGridSquare != 5 && tiles[selectedTile].currentGridSquare != 11 && tiles[selectedTile].currentGridSquare != 17 &&
                tiles[selectedTile].currentGridSquare != 23 && tiles[selectedTile].currentGridSquare != 29 && tiles[selectedTile].currentGridSquare != 35)
                //check if the tile is on the right column of the grid
            {
                tiles[selectedTile].currentGridSquare++; //add one to the current grid square
                tiles[selectedTile].MoveToLocation(gridSquares[tiles[selectedTile].currentGridSquare]); //call function to move the tile to the new grid square
            }
        }
        else if (Input.GetKeyDown(KeyCode.O)) //change tile
        {
            ChangeTile();
        }

    }

    void ChangeTile()
    {
        if (selectedTile == tiles.Length - 1)  //checks if the selected tile is the last one in the array
        {
            selectedTile = 0; //if yes set the selectedTile to 0
        }
        else
        {
            selectedTile++; //otherwise increase the selected tile by 1
        }

        meshRenderer.material = screenMaterial[selectedTile]; //change the screen material to show the symbol for the selected tile
    }

    void ShowCodeNumber()
    {
        meshRenderer.material = screenMaterial[4]; //change console screen material to show code number
        roomFinished = true; //set variable to true so function doesn't run again in update
    }


    private void OnTriggerStay(Collider collider)
    {
        if(collider.CompareTag("Player")) //check if player is in trigger box collider
        {
            isInRange = true;
        }
    }

    private void OnTriggerExit(Collider collider)
    {
        if (collider.CompareTag("Player")) //chek if player has left trigger box collider
        {
            isInRange = false;
        }
    }
}
