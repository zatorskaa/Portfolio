using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBullet : Bullet
{
    private void OnCollisionEnter(Collision collision)
    {
        if (collision.collider.CompareTag("Tower"))
        {
            if(collision.collider.GetComponent<FireRateTower>() != null)
            {
                if(collision.collider.GetComponent<FireRateTower>().enabled)
                {
                    collision.collider.GetComponent<FireRateTower>().currentDurability -= damage; //decrease tower durability
                }
            }
            
            if (collision.collider.GetComponent<DamageTower>() != null)
            {
                if (collision.collider.GetComponent<DamageTower>().enabled)
                {
                    collision.collider.GetComponent<DamageTower>().currentDurability -= damage; //decrease tower durability
                }
            }
            
            if (collision.collider.GetComponent<RangeTower>() != null)
            {
                if (collision.collider.GetComponent<RangeTower>().enabled)
                {
                    collision.collider.GetComponent<RangeTower>().currentDurability -= damage; //decrease tower durability
                }
            }

            Destroy(gameObject);
        }
        
        if(collision.collider.CompareTag("Castle"))
        {
            collision.collider.GetComponent<Castle>().currentDurability -= damage; //decrease castle durability

            Destroy(gameObject);
        }
    }
}
