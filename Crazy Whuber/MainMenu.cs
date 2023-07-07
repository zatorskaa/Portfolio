using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour
{
    //store menu game objects
    [SerializeField]
    GameObject mainMenu;
    [SerializeField]
    GameObject optionsMenu;
    [SerializeField]
    GameObject levelSelectionMenu;
    [SerializeField]
    //this will get the parent of all scoreboards
    GameObject ScoreBoardsParent;
    [SerializeField]
    //this wuill get all the scoresboards (race, normal)
    GameObject[] ScoreBoards;
    //this will save wich scoreboard is active
    int currentScoreBoard;

    private void Start()
    {
        //hide options menu and show main menu when menu is loaded
        ShowMainMenu();
        Time.timeScale = 1f;
    }

    public void ShowOptions()
    {
        mainMenu.SetActive(false);
        optionsMenu.SetActive(true);
        levelSelectionMenu.SetActive(false);
        ScoreBoardsParent.SetActive(false);
    }

    public void ShowMainMenu()
    {
        mainMenu.SetActive(true);
        optionsMenu.SetActive(false);
        levelSelectionMenu.SetActive(false);
        ScoreBoardsParent.SetActive(false);
    }

    public void PlayGame(int level)
    {
        SceneManager.LoadScene(level); //load game scene
    }
    public void ShowScores()
    {
        levelSelectionMenu.SetActive(false);
        mainMenu.SetActive(false);
        optionsMenu.SetActive(false);
        ScoreBoardsParent.SetActive(true);
    }

    public void LoadLevelSelection()
    {
        levelSelectionMenu.SetActive(true);
        mainMenu.SetActive(false);
        optionsMenu.SetActive(false);
        ScoreBoardsParent.SetActive(false);
    }

    public void NextScoreBoard()
    {
        ScoreBoards[currentScoreBoard].SetActive(false);

        //if we  are not on the last scoreboard increase the scoreoard and set that to true
        if (currentScoreBoard < ScoreBoards.Length - 1)
        {
            currentScoreBoard = currentScoreBoard + 1;
            ScoreBoards[currentScoreBoard].SetActive(true);
        }
        //else jus make it the first score active because we did a loop
        else
        {
            currentScoreBoard = 0;
            ScoreBoards[currentScoreBoard].SetActive(true);
        }
        
    }

    public void PreviousScoreBoard()
    {
        //deactivate the current scoreboard
        ScoreBoards[currentScoreBoard].SetActive(false);
        //if we already are not on the first scoreboard decrease the scoreoard and set that to true
        if (currentScoreBoard > 0)
        {
            currentScoreBoard = currentScoreBoard - 1;
            ScoreBoards[currentScoreBoard].SetActive(true);
        }
        //else jus make it the last score active because we did a loop
        else
        {
            currentScoreBoard = ScoreBoards.Length - 1;
            ScoreBoards[currentScoreBoard].SetActive(true);
        }
    }
}
