using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Menu : MonoBehaviour
{
    #region Variables
    [SerializeField]
    GameObject mainScreenUI;
    [SerializeField]
    GameObject controlsScreenUI;
    #endregion

    public void QuitGame()
    {
        //quit game
        Debug.Log("Quit");
        Application.Quit();
    }

    public void ShowControlsScreen()
    {
        //show controls screen
        mainScreenUI.SetActive(false);
        controlsScreenUI.SetActive(true);
    }

    public void ShowMainScreen()
    {
        //show title or pause screen
        mainScreenUI.SetActive(true);
        controlsScreenUI.SetActive(false);
    }
}
