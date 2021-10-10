using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Block : MonoBehaviour
{
    #region Variables
    public int value;
    private bool isDestroyed;

    [SerializeField]
    private UI ui;
    #endregion

    private void Start()
    {
        isDestroyed = false;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.CompareTag("Ball") && !isDestroyed)
        {
            isDestroyed = true;

            BlockBreakerGameManager.points += value; //add value of block to total points
            ui.SetPoints(BlockBreakerGameManager.points); //change points in ui

            Destroy(gameObject); //destroy the block
        }
    }
}
