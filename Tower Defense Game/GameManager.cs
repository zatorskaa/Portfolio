using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    //store scripts
    [SerializeField]
    WaveSpawner waveSpawner;
    [SerializeField]
    Castle castle;

    //store ui screens
    [SerializeField]
    GameObject gameOverScreen;
    [SerializeField]
    GameObject winScreen;

    bool showui; //used to check if the ui is already showing so that the function won't be called in Update anymore


    void Awake()
    {
        //disable screens
        winScreen.SetActive(false);
        gameOverScreen.SetActive(false);
        showui = false;
    }


    private void LateUpdate() 
    {
        if(!showui) //check if ui is already showing, if not call function
        {
            ShowUI();
        }
    }

    void ShowUI()
    {
        if(waveSpawner.currentWave == waveSpawner.waves.Length && WaveSpawner.enemiesLeft == 0)
        {
            winScreen.SetActive(true); //if player clears all waves, show win screen
            Time.timeScale = 0; //pause game
            showui = true;
        }

        if(castle.currentDurability <= 0)
        {
            gameOverScreen.SetActive(true); //if castle durability reaches 0, show game over screen
            Time.timeScale = 0; //pause game
            showui = true;
        }
    }
}
