using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    #region Variables
    private bool releaseBall;
    public Transform ballPosition;

    private Rigidbody2D rb;
    public int force;

    [SerializeField]
    private UI ui;
    #endregion

    void Awake()
    {
        rb = GetComponent<Rigidbody2D>();
        releaseBall = false;
        transform.position = ballPosition.position;

    }

    // Update is called once per frame
    void Update()
    {
        if(BlockBreakerGameManager.gameOver == false) //if game is not over
        {
            ReleaseBall();

            if (Input.GetKeyDown(KeyCode.R))
            {
                ResetBall();
            }
        }
        else
        {
            rb.velocity = new Vector2(0f, 0f);
            transform.position = ballPosition.position; //if game is over stop the ball from moving
        }
    }


    private void ReleaseBall()
    {
        if (releaseBall == false)
        {
            transform.position = ballPosition.position; //move ball to position above player

            if (Input.GetMouseButtonDown(0)) //check if LMB is pressed
            {
                releaseBall = true;

                rb.AddForce(new Vector2(force, force)); //add forve to the ball to move it
            }
        }
    }

    void ResetBall()
    {
        BlockBreakerGameManager.lives--; //decrease lives by 1

        releaseBall = false;
        rb.velocity = new Vector2(0f, 0f); //reset velocity to 0

        ui.DecreaseLives(); //decrease number of lives in ui
    }


    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.CompareTag("Bottom")) //if ball hits bottom of screen
        {
            ResetBall();
        }
    }
}
