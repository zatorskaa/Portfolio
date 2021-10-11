using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyCounter : MonoBehaviour
{
    #region Variables
    //store number of enemies in each stage
    int numberOfEnemiesStageOne;
    int numberOfEnemiesStageTwo;
    int numberOfEnemiesStageThree;
    int numberOfEnemiesStageFour;

    //store spawner objects
    [SerializeField]
    GameObject enemySpawnerOne;
    [SerializeField]
    GameObject enemySpawnerTwo;
    [SerializeField]
    GameObject enemySpawnerThree;
    [SerializeField]
    GameObject enemySpawnerFour;

    //store animator compoenents for each bridge
    [SerializeField]
    Animator bridgeOneAnim;
    [SerializeField]
    Animator bridgeTwoAnim;
    [SerializeField]
    Animator bridgeThreeAnim;
    [SerializeField]
    Animator bridgeFourAnim;

    //store enemy stage counter objects
    [SerializeField]
    GameObject stageOneEnemies;
    [SerializeField]
    GameObject stageTwoEnemies;
    [SerializeField]
    GameObject stageThreeEnemies;
    [SerializeField]
    GameObject stageFourEnemies;
    #endregion


    private void Update()
    {
        //find number of enemies in each stage
        numberOfEnemiesStageOne = stageOneEnemies.transform.childCount;
        numberOfEnemiesStageTwo = stageTwoEnemies.transform.childCount;
        numberOfEnemiesStageThree = stageThreeEnemies.transform.childCount;
        numberOfEnemiesStageFour = stageFourEnemies.transform.childCount;


        //check if all enemies have spawned and have been destroyed/killed for each stage
        if(enemySpawnerOne == null && numberOfEnemiesStageOne == 0)
        {
            bridgeOneAnim.SetBool("stageFinished", true);
        }

        if(enemySpawnerTwo == null && numberOfEnemiesStageTwo == 0)
        {
            bridgeTwoAnim.SetBool("stageFinished", true);
        }

        if(enemySpawnerThree == null && numberOfEnemiesStageThree == 0)
        {
            bridgeThreeAnim.SetBool("stageFinished", true);
        }

        if(enemySpawnerFour == null && numberOfEnemiesStageFour == 0)
        {
            bridgeFourAnim.SetBool("stageFinished", true);
        }
    }
}
