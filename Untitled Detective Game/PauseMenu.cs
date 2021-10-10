using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseMenu : Menu
{
    #region Variables
    [SerializeField]
    int mainMenuBuildIndex;

    public GameObject pauseMenuUI; //store main pause menu object with pause screen and controls screen

    [SerializeField]
    PlayerMovement player;

    [HideInInspector]
    public bool caseFilesIsOpen;
    #endregion

    private void Start()
    {
        //disable pause screen
        pauseMenuUI.SetActive(false);
        Time.timeScale = 1f;

        caseFilesIsOpen = false;
    }

    private void Update()
    {
        if(!caseFilesIsOpen) //if case files menu is not open
        {
            if (Input.GetKeyDown(KeyCode.P)) //if p key pressed enable/disable pause menu
            {
                TogglePauseMenu();
            }
        }
    }

    public void LoadMainMenu()
    {
        //load main menu scene
        SceneManager.LoadScene(mainMenuBuildIndex);
    }

    public void TogglePauseMenu()
    {
        if (pauseMenuUI.activeInHierarchy)
        {
            //disable pause menu and set time scale to 1
            pauseMenuUI.SetActive(false);
            Time.timeScale = 1f;

            player.menuIsOpen = false;
        }
        else
        {
            //enable pause screen and set time scale to 0
            pauseMenuUI.SetActive(true);
            ShowMainScreen();
            Time.timeScale = 0f;

            player.menuIsOpen = true;
        }
    }
}
