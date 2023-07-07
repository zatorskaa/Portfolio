using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
    call CalculateScore() function when player has reached destination

    call ResetStars() when new location is set
    call RemoveStar() when player hits an NPC
 */

public class ScoringSystem : MonoBehaviour
{
    int score; //score the score for the current location

    [HideInInspector]
    public int totalScore; //store total score for the game

    [SerializeField]
    TimeSystem timeSystem; //store time system script
    [SerializeField]
    int scorePerSecond; //store the score value per second that is left

    int maxStars;
    int currentStars;

    [SerializeField]
    UiSystem uiSystem;

    void Awake()
    {
        totalScore = 0; //set total score to 0
        maxStars = 5; //set max stars to 5

        ResetStars();
    }

    public int CalculateScore()
    {
        //calculate score for current location
        if(timeSystem.timeLeft >= 0)
        {
            score = (int)timeSystem.timeLeft * scorePerSecond * currentStars; //if score is greater than 0 times by number of stars
        }
        else
        {
            score = (int)timeSystem.timeLeft * scorePerSecond / currentStars; //if score is less than zero divide by number of stars
        }
        totalScore += score;

        //set score in ui
        uiSystem.SetScore(totalScore);

        return score;
    }

    public int ReturnTotalScore()
    {
        return totalScore;
    }


    public void ResetStars()
    {
        //reset the number of stars for each location
        currentStars = maxStars;
        uiSystem.SetStars();
    }

    public void RemoveStar()
    {
        //remove one of the stars for the current location
        if(currentStars > 1)
        {
            currentStars--;
            uiSystem.SetStars();
        }
    }

    public int ReturnStarNumber()
    {
        //get the final number of stars for the current location
        return currentStars;
    }


    public int CalculateRaceScore()
    {
        int raceScore;

        if (timeSystem.raceTime >= 0)
        {
            raceScore = (int)timeSystem.raceTime * scorePerSecond * currentStars; //if score is greater than 0 times by number of stars
        }
        else
        {
            raceScore = (int)timeSystem.raceTime * scorePerSecond / currentStars; //if score is less than zero divide by number of stars
        }

        uiSystem.SetScore(raceScore);

        totalScore = raceScore;

        return raceScore;
    }
}
