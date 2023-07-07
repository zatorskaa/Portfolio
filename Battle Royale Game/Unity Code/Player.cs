using StarterAssets;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Player : MonoBehaviour
{
    [SerializeField] float maxHealth = 100;
    [SerializeField] float currentHealth = 100;
    [SerializeField] bool isDead;
    [SerializeField] bool isShot;
    [SerializeField] Slider slider; //slider UI for healthbar
    public Vector3 startPosition;

    // Start is called before the first frame update
    void Start()
    {
        //initialise variables
        currentHealth = maxHealth;
        isDead = false;
        isShot = false;
        slider.maxValue = maxHealth;
        slider.value = currentHealth;
        startPosition = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        //change the healthbar value to the current health
        slider.value = currentHealth;

        //check if player health has reached 0
        if (currentHealth <= 0)
        {
            isDead = true;
        }
    }

    public void Shot(float damage)
    {
        //function is called when a player is shot and current health is reduced
        currentHealth -= damage;
        isShot = true;
        Debug.Log("Shot");
    }

    //get and set functions for variables
    public float GetHealth()
    {
        return currentHealth;
    }

    public void SetHealth(float health)
    {
        currentHealth = health;
    }

    public void ResetHealth()
    {
        currentHealth = maxHealth;
    }

    public bool GetIsDead()
    {
        return isDead;
    }

    public void SetIsDead(bool dead)
    {
        isDead = dead;
    }

    public bool GetIsShot()
    {
        return isShot;
    }

    public void SetIsShot(bool dead)
    {
        isShot = dead;
    }

    public void Respawn()
    {
        //reset the local player's position to its starting position
        GetComponent<FirstPersonController>().enabled = false;
        GetComponent<CharacterController>().enabled = false;
        transform.position = startPosition;
        GetComponent<FirstPersonController>().enabled = true;
        GetComponent<CharacterController>().enabled = true;
    }
}
