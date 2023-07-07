using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/*
    ui for score and stars is finished
 */

public class UiSystem : MonoBehaviour
{
    [SerializeField]
    Sprite yellowStar;
    [SerializeField]
    Sprite greyStar;

    [SerializeField]
    Image[] stars;
    [SerializeField]
    Text scoreText;

    [SerializeField]
    ScoringSystem scoringSystem;

    public void SetStars()
    {
        if(scoringSystem.ReturnStarNumber() == 1)
        {
            stars[0].sprite = yellowStar;
            stars[1].sprite = greyStar;
            stars[2].sprite = greyStar;
            stars[3].sprite = greyStar;
            stars[4].sprite = greyStar;
        }
        else if(scoringSystem.ReturnStarNumber() == 2)
        {
            stars[0].sprite = yellowStar;
            stars[1].sprite = yellowStar;
            stars[2].sprite = greyStar;
            stars[3].sprite = greyStar;
            stars[4].sprite = greyStar;
        }
        else if(scoringSystem.ReturnStarNumber() == 3)
        {
            stars[0].sprite = yellowStar;
            stars[1].sprite = yellowStar;
            stars[2].sprite = yellowStar;
            stars[3].sprite = greyStar;
            stars[4].sprite = greyStar;
        }
        else if(scoringSystem.ReturnStarNumber() == 4)
        {
            stars[0].sprite = yellowStar;
            stars[1].sprite = yellowStar;
            stars[2].sprite = yellowStar;
            stars[3].sprite = yellowStar;
            stars[4].sprite = greyStar;
        }
        else if(scoringSystem.ReturnStarNumber() == 5)
        {
            stars[0].sprite = yellowStar;
            stars[1].sprite = yellowStar;
            stars[2].sprite = yellowStar;
            stars[3].sprite = yellowStar;
            stars[4].sprite = yellowStar;
        }
    }

    public void SetScore(int score)
    {
        scoreText.text = "Score: " + score.ToString();
    }
}
