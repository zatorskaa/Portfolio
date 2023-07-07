using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WaveSpawner : MonoBehaviour
{
    [SerializeField]
    GameObject[] enemySpawnPoints; //array to store spawn point game objects
    public Wave[] waves; //array to store wave scripts
    [SerializeField]
    float timeBetweenWaves; //stores the time before a new wave is spawned after the previous is defeated
    float timeLeft; //used for timer

    [SerializeField]
    GameObject castle; //store the castle game object to set as target for enemies
    [SerializeField]
    Text timeText; //store text component to show time left until next wave
    [SerializeField]
    GameObject text; //store the object that shows 'Time Before Next Wave' text

    bool spawnNewWave; //check if next wave can be spawned
    bool spawningNewWave; //check if a wave is currently being spawned

    [HideInInspector]
    public int currentWave; //store the current wave number
    public static int enemiesLeft; //store the number of enemies left in a wave, static so only one exists in scene and it can be called from enemy script without a reference


    private void Awake()
    {
        //initialize variables
        spawnNewWave = true;
        spawningNewWave = false;
        currentWave = 0;
        enemiesLeft = 0;
        timeText.text = "";
    }

    private void Update()
    {
        if(currentWave < waves.Length) //check if all waves have been spawned
        {
            if (spawnNewWave) //if new wave can be spawned
            {
                StartCoroutine(SpawnWave()); //call coroutine to spawn next wave
            }

            if (enemiesLeft == 0 && !spawningNewWave) //if there are no enemies left in a wave and a new wave is not currently being spawned
            {
                spawnNewWave = true; //set variabled to true to spawn new wave
            }
        }

        if(timeLeft > 0) //before next wave spawns
        {
            timeLeft -= Time.deltaTime; //decrease the time each frame

            timeText.text = ((int)timeLeft).ToString(); //show the time in the ui
        }
        else
        {
            timeText.text = "";
        }
    }

    IEnumerator SpawnWave()
    {
        spawnNewWave = false; //set to false so no new waves can be spawned
        spawningNewWave = true; //set to true so coroutine won't be called again while the current wave is spawning

        text.SetActive(true); //show text above castle
        timeLeft = timeBetweenWaves; //set the time left until next wave to the time between waves

        yield return new WaitForSeconds(timeBetweenWaves); //wait before spawning new wave

        text.SetActive(false); //hide text above castle

        StartCoroutine(SpawnEnemy()); //call coroutine to start spawning enemies
    }

    IEnumerator SpawnEnemy()
    {
        for (int i = 0; i < waves[currentWave].numberOfEnemies; i++) //check how many enemies need to be spawned in current wave
        {
            int randomEnemy = Random.Range(0, waves[currentWave].enemyPrefab.Length); //select random enemy prefab from array
            int randomSpawnPoint = Random.Range(0, enemySpawnPoints.Length); //select random spawn point from array

            GameObject enemy = Instantiate(waves[currentWave].enemyPrefab[randomEnemy]); //spawn random enemy at random spawn point

            if (enemy.GetComponent<Enemy>().canShoot) //check if the spawned enemy can shoot
            {
                enemy.transform.position = new Vector3(enemySpawnPoints[randomSpawnPoint].transform.position.x, enemySpawnPoints[randomSpawnPoint].transform.position.y + 20f, enemySpawnPoints[randomSpawnPoint].transform.position.z); //instantiate the enemy above the spawn point
            }
            else
            {
                enemy.transform.position = new Vector3(enemySpawnPoints[randomSpawnPoint].transform.position.x, enemySpawnPoints[randomSpawnPoint].transform.position.y + 2f, enemySpawnPoints[randomSpawnPoint].transform.position.z); //instantiate the enemy at the spawn point
            }

            //set the target for the enemy to castle
            enemy.GetComponent<Enemy>().castle = castle;
            enemy.GetComponent<Enemy>().target = castle;

            enemiesLeft++; //increase number of enemies in current wave

            yield return new WaitForSeconds(waves[currentWave].spawnRate); //wait to spawn next enemy
        }

        currentWave++; //set the wave number to the next one

        spawningNewWave = false; //set to false so new wave can be spwaned when all enemies are defeated
    }
}
