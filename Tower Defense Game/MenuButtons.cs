using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MenuButtons : MonoBehaviour
{
    //store the build index of scenes to load
    [SerializeField]
    int mainMenuBuildIndex;
    [SerializeField]
    int gameBuildIndex;

    public void LoadGame()
    {
        Time.timeScale = 1f; //unpause game

        SceneManager.LoadScene(gameBuildIndex); //load the main game scene
    }

    public void LoadMenu()
    {
        Time.timeScale = 1f; //unpause game

        SceneManager.LoadScene(mainMenuBuildIndex); //load the main menu scene
    }
}
