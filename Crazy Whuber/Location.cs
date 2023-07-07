using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Location : MonoBehaviour
{
    //pickup location = green
    //drop off location = red

    SpriteRenderer spriteRenderer;
    Collider2D col;

    [SerializeField]
    ScoringSystem scoringSystem; //store the scoring system script

    [SerializeField]
    TimeSystem timeSystem; //store the time system script
 
    private void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
        col = GetComponent<Collider2D>();
        col.enabled = false;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.CompareTag("Player") && spriteRenderer.enabled) //check if location is active and if player has collided with it
        {
            CarController player = collision.GetComponent<CarController>(); //get the car controller script from the player

            if (spriteRenderer.color == Color.green) //check if the location has a green colour
            {
                spriteRenderer.enabled = false; //disable the sprite renderer for the location
                col.enabled = false;

                player.hasPickedUpPerson = true; //if yes, the player has picked up a person

                timeSystem.CalculateTime(); //call function to calculate time for the current location
                timeSystem.timeText.gameObject.SetActive(true); //show the time for the current location

                scoringSystem.ResetStars();
            }
            else if (spriteRenderer.color == Color.red) //check if location has a red colour
            {
                if(player.hasPickedUpPerson) //check if the player has picked up a person from the pickup location
                {
                    spriteRenderer.enabled = false; //disable the sprite renderer for the location
                    col.enabled = false;

                    timeSystem.timeText.gameObject.SetActive(false); //hide the time
                    scoringSystem.CalculateScore(); //calculate the score for the current location

                    player.GetPickupLocation(); //get new locations
                    player.hasPickedUpPerson = false; //set to false for new location
                }
            }
        }

    }
}
