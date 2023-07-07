using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseMenu : MonoBehaviour
{
    //store menu game objects
    public GameObject menu;
    public GameObject pauseMenu;
    [SerializeField]
    GameObject optionsMenu;

    //store ui game objects
    public GameObject UI;
    public GameObject velocimeter;
    public GameObject minimap;

    private void Start()
    {
        Time.timeScale = 1f;

        //disable pause menu and show ui
        menu.SetActive(false);
        UI.SetActive(true);
        velocimeter.SetActive(true);
        minimap.SetActive(true);
    }

    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.P))
        {
            ToggleMenu();
        }
    }

    public void ToggleMenu()
    {
        //hide/show pause menu
        menu.SetActive(!menu.activeSelf);
        UI.SetActive(!UI.activeSelf);
        velocimeter.SetActive(!velocimeter.activeSelf);
        minimap.SetActive(!minimap.activeSelf);

        if(menu.activeSelf)
        {
            //pause the game
            pauseMenu.SetActive(true);
            optionsMenu.SetActive(false);

            Time.timeScale = 0f;
        }
        else
        {
            //unpause the game
            Time.timeScale = 1f;
        }
    }

    public void ToggleOptions()
    {
        //hide/show options in pause menu
        pauseMenu.SetActive(!pauseMenu.activeSelf);
        optionsMenu.SetActive(!optionsMenu.activeSelf);
    }

    public void LoadMainMenu()
    {
        //load main menu scene
        SceneManager.LoadScene(0);
    }

    public void RestartLevel()
    {
        //reload current scene to restart the level
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }
}
