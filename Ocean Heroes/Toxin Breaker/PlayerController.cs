using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    #region Variables
    [SerializeField]
    private float minPosition;
    [SerializeField]
    private float maxPosition;

    [Header("Power Ups")]
    [SerializeField]
    private float powerUpTime;
    private bool isUsingPowerUp;

    [Header("Change Length")]
    [SerializeField]
    private float scaleLong;
    [SerializeField]
    private float scaleShort;
    private float scaleNormal;

    [Header("Extra Balls")]
    [SerializeField]
    private GameObject extraBallPrefab;
    [SerializeField]
    private int numberOfExtraBalls;
    [SerializeField]
    private float timeBetweenBalls;
    [SerializeField]
    private Transform ballPosition;
    #endregion

    private void Start()
    {
        isUsingPowerUp = false;
        scaleNormal = transform.localScale.x;
    }

    void Update()
    {
        if(BlockBreakerGameManager.gameOver == false)
        {
            MovePlayer();
        }
    }


    void MovePlayer()
    {
        if(Camera.main.ScreenToWorldPoint(Input.mousePosition).x < maxPosition && Camera.main.ScreenToWorldPoint(Input.mousePosition).x > minPosition) //check if mouse is on screen
        {
            transform.position = new Vector3(Camera.main.ScreenToWorldPoint(Input.mousePosition).x, transform.position.y, transform.position.z); //move player position to mouse position on screen
        }
    }



    private void OnTriggerEnter2D(Collider2D collider)
    {
        if (collider.CompareTag("Increase Length") && !isUsingPowerUp)
        {
            StartCoroutine(IncreasePlayerLength());
        }

        if(collider.CompareTag("Decrease Length") && !isUsingPowerUp)
        {
            StartCoroutine(DecreasePlayerLength());
        }

        if(collider.CompareTag("Extra Balls"))
        {
            StartCoroutine(AddExtraBalls());
        }
    }

    IEnumerator IncreasePlayerLength()
    {
        isUsingPowerUp = true;

        transform.localScale = new Vector3(scaleLong, transform.localScale.y, transform.localScale.z); //increase length of player

        yield return new WaitForSeconds(powerUpTime); //wait for time

        transform.localScale = new Vector3(scaleNormal, transform.localScale.y, transform.localScale.z); //set length to normal

        isUsingPowerUp = false;
    }

    IEnumerator DecreasePlayerLength()
    {
        isUsingPowerUp = true;

        transform.localScale = new Vector3(scaleShort, transform.localScale.y, transform.localScale.z); //increase length of player

        yield return new WaitForSeconds(powerUpTime); //wait for time

        transform.localScale = new Vector3(scaleNormal, transform.localScale.y, transform.localScale.z); //set length to normal

        isUsingPowerUp = false;
    }

    IEnumerator AddExtraBalls()
    {
        Instantiate(extraBallPrefab, new Vector3(ballPosition.position.x, ballPosition.position.y, ballPosition.position.z), Quaternion.identity);

        yield return new WaitForSeconds(timeBetweenBalls);

        Instantiate(extraBallPrefab, new Vector3(ballPosition.position.x, ballPosition.position.y, ballPosition.position.z), Quaternion.identity);
    }
}