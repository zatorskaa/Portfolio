using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DropPowerUp : MonoBehaviour
{
    [SerializeField]
    private GameObject powerUpPrefab;

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.collider.CompareTag("Ball"))
        {
            Instantiate(powerUpPrefab, new Vector3(transform.position.x, transform.position.y, transform.position.z), Quaternion.identity); //drop a power up when hit by ball
        }
    }
}
