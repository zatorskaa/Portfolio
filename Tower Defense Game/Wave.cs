using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Wave : MonoBehaviour
{
    public GameObject[] enemyPrefab; //stores the enemy prefabs to spawn in that wave
    public int numberOfEnemies; //stores the number of enemies to spawn in that wave
    public float spawnRate; //stores the time to wait between spawning each enemy in a wave
}
