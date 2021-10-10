using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockBreakerGameManager : MonoBehaviour
{
    #region Variables
    [SerializeField]
    private int startingLives;
    public static int lives;
    [HideInInspector]
    public static bool gameOver;

    [HideInInspector]
    public static int points;

    [SerializeField]
    private GameObject[] blocks;
    private int maxPoints;
    #endregion


    // Start is called before the first frame update
    void Awake()
    {
        lives = startingLives;
        gameOver = false;
        points = 0;
        maxPoints = 0;

        for(int i = 0; i < blocks.Length; i++)
        {
            maxPoints += blocks[i].GetComponent<Block>().value; //add number of points for each block
        }
    }

    // Update is called once per frame
    void Update()
    {
        if(lives == 0 || points == maxPoints) //check if lives is equal to 0 or if all blocks have been destroyed (points is equal to max points)
        {
            gameOver = true; 
        }
    }
}
