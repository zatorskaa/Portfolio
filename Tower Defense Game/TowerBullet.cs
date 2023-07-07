using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TowerBullet : Bullet
{
    private void OnCollisionEnter(Collision collision)
    {
        if(collision.collider.CompareTag("Enemy"))
        {
            collision.collider.GetComponent<Enemy>().currentHealth -= damage; //decrease enemy health

            Destroy(gameObject); //detroy bullet
        }
    }
}
