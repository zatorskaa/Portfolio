using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Grid : MonoBehaviour
{
    public GridSquare[] gridSquares; //stores the grid square object scripts
    public Tile[] tiles; //stores the tile object scripts

    protected static int selectedTile; //used to check which tile is currently selected
    protected static bool roomFinished; //used to check if puzzle has been solved and code number is displayed

    private void Start()
    {
        roomFinished = false;

        //initialize variables and call function to move tiles to the corners of the grid
        selectedTile = 0; 

        //move the four tiles to the corners of the grid and set their current grid square to that location on the grid
        tiles[0].MoveToLocation(gridSquares[0]);
        tiles[0].currentGridSquare = 0;
        tiles[1].MoveToLocation(gridSquares[5]);
        tiles[1].currentGridSquare = 5;
        tiles[2].MoveToLocation(gridSquares[30]);
        tiles[2].currentGridSquare = 30;
        tiles[3].MoveToLocation(gridSquares[35]);
        tiles[3].currentGridSquare = 35;
    }

    protected bool CheckPuzzleSolved()
    {
        if(tiles[0].isCorrect && tiles[1].isCorrect && tiles[2].isCorrect && tiles[3].isCorrect) //if all tiles are in the correct place
        {
            return true; //return true
        }
        else
        {
            return false; //if not all tiles are correct return false
        }
    }
}
