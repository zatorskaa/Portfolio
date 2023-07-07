using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Enemy : MonoBehaviour
{
    [Header("Stats")]
    //stores max and current health of enemy
    [SerializeField]
    float maxHealth;
    [HideInInspector]
    public float currentHealth;
    [SerializeField]
    Slider healthBar;

    [SerializeField]
    float damage; //stores the amount of damage that the enemy will do to a tower or the castle
    [SerializeField]
    float movementSpeed;

    [SerializeField]
    int coinValue; //number of coins that will be added to player's coins when enemy is defeated

    [HideInInspector]
    public GameObject castle; //store the castle object
    [HideInInspector]
    public GameObject target; //store the current target that the enemy will attack


    [Header("Attack")]
    [SerializeField]
    Vector3 attackRange; //range that the enemy will check for objects to attack
    [SerializeField]
    LayerMask destructibleLayerMask; //layer mask for towers and castle
    Collider[] destructibleObject; //used to store colliders of objects that the overlap box finds

    public bool canShoot; //check whether the enemy will attack or shoot

    bool isAttacking; //used to check if the enemy is currently attacking a tower or the castle
    bool attackTarget;

    [SerializeField]
    GameObject bulletPrefab; //bullet prefab to shoot at tower
    [SerializeField]
    float bulletSpeed; //speed that the bullet moves at
    [SerializeField]
    float attackRate; //how fast new bullets are spwaned


    private void Start()
    {
        target = castle; //set the castle as the initial target
        currentHealth = maxHealth; //set the current health to max health when the enemy is spawned

        //enable health bar and set max value to max health
        healthBar.gameObject.SetActive(true);
        healthBar.maxValue = maxHealth;

        //initialize variables to false
        isAttacking = false;
        attackTarget = true;
    }

    private void FixedUpdate()
    {
        destructibleObject = Physics.OverlapBox(transform.position, attackRange, Quaternion.identity, destructibleLayerMask); //check for nearby destructible objects
    }

    private void Update()
    {
        if(destructibleObject != null && destructibleObject.Length != 0) //if enemy is near a destrucible object
        {
            //if the object has these scripts
            if (destructibleObject[0].GetComponent<FireRateTower>() != null &&
               destructibleObject[0].GetComponent<DamageTower>() != null &&
               destructibleObject[0].GetComponent<RangeTower>() != null)
            {
                //if the tower is level 1 or above (if the tower exists)
                if (destructibleObject[0].GetComponent<FireRateTower>().level != 0 ||
                    destructibleObject[0].GetComponent<DamageTower>().level != 0 ||
                    destructibleObject[0].GetComponent<RangeTower>().level != 0)
                {
                    target = destructibleObject[0].gameObject; //set the target as the tower

                    isAttacking = true; //enemy can attack
                }
                else
                {
                    target = castle; //set the target as the castle
                    isAttacking = false; //enemy can't attack
                }
            }
            else if (destructibleObject[0].GetComponent<Castle>() != null)
            {
                target = castle; //set the target as the castle
                isAttacking = true; //enemy can attack
            }

        }
        else
        {
            isAttacking = false; //enemy can't attack
        }



        if(isAttacking && attackTarget) //if enemy can shoot
        {
            //check if enemy shoots to attack
            if(canShoot)
            {
                StartCoroutine(ShootBullet());
            }
            else
            {
                StartCoroutine(Attack());
            }
        }
        else if(!isAttacking) //if enemy is not attacking the castle or a tower
        {
            transform.position = Vector3.MoveTowards(transform.position, target.transform.position, movementSpeed * Time.deltaTime); //move enemy towards target
        }



        if (currentHealth >= 0)
        {
            healthBar.value = currentHealth; //set slider value as current health
        }
        else if (currentHealth < 0)
        {
            healthBar.value = 0;
        }

        if (currentHealth <= 0)
        {
            Die(); //if enemy health is at 0 or below they will die
        }
    }

    IEnumerator ShootBullet()
    {
        attackTarget = false; //stop update from calling coroutine

        //instantiate bullet to shoot at target
        GameObject bullet = Instantiate(bulletPrefab);
        bullet.transform.position = new Vector3(transform.position.x, transform.position.y + 1f, transform.position.z);
        bullet.GetComponent<Bullet>().target = target;
        bullet.GetComponent<Bullet>().speed = bulletSpeed;
        bullet.GetComponent<Bullet>().damage = damage;

        yield return new WaitForSeconds(attackRate); //wait to shoot bullet
        attackTarget = true; //let update call coroutine
    }

    IEnumerator Attack()
    {
        attackTarget = false; //stop update from calling coroutine

        if (target.GetComponent<FireRateTower>() != null &&
            target.GetComponent<DamageTower>() != null &&
            target.GetComponent<RangeTower>() != null)
        {
            //damage tower
            if (target.GetComponent<FireRateTower>().enabled)
            {
                target.GetComponent<FireRateTower>().currentDurability -= damage;
            }
            else if (target.GetComponent<DamageTower>().enabled)
            {
                target.GetComponent<DamageTower>().currentDurability -= damage;
            }
            else if (target.GetComponent<RangeTower>().enabled)
            {
                target.GetComponent<RangeTower>().currentDurability -= damage;
            }
        }
        else if (target.GetComponent<Castle>() != null)
        {
            //damage castle
            target.GetComponent<Castle>().currentDurability -= damage;
        }

        yield return new WaitForSeconds(attackRate); //wait to attack
        attackTarget = true; //let update call coroutine
    }


    void Die()
    {
        WaveSpawner.enemiesLeft--; //decrease the number of enemies left in current wave
        CurrencySystem.coins += coinValue; //increase player's number of coins

        Destroy(gameObject); //destroy enemy game object
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.collider.CompareTag("Weapon"))
        {
            currentHealth -= collision.gameObject.GetComponent<Weapon>().damage; //decrease enemy health when hit by weapon
        }
    }


    private void OnDrawGizmos()
    {
        //show box to check for enemies in inspector
        Gizmos.color = Color.red;
        Gizmos.DrawWireCube(transform.position, attackRange * 2);
    }
}
