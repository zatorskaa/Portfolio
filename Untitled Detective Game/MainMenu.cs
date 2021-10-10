using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : Menu
{
    #region Variables
    [SerializeField]
    int mainGameAreaBuildIndex;
    #endregion

    private void Start()
    {
        Time.timeScale = 1f;
        ShowMainScreen();
    }

    public void StartGame()
    {
        SceneManager.LoadScene(mainGameAreaBuildIndex); //load main game scene when start button is pressed
    }


}
