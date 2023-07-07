using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TowerStats : MonoBehaviour
{
    [Header("Stats")]
    public float maxDurability; //tower durability
    [HideInInspector]
    public float currentDurability;
    [HideInInspector]
    public int level; //tower level

    [SerializeField]
    float range; //tower range to hit enemies
    [SerializeField]
    float fireRate; //tower fire rate
    [SerializeField]
    float damage; //tower damage to enemies

    [Header("Cost")]
    public int towerCost;
    public int upgradeCost;

    //variables to store stat values for level 1 tower to reset them when a tower is destroyed
    float baseDurability;
    float baseRange;
    float baseFireRate;
    float baseDamage;

    [SerializeField]
    GameObject durabilityBar;


    [Header("Shooting")]
    [SerializeField]
    LayerMask enemyLayerMask; //layer mask of enemies
    
    Collider[] enemies; //stores enemies in range of tower

    [SerializeField]
    GameObject bulletPrefab; //stores prefab of bullet object
    [SerializeField]
    float bulletSpeed; //stores the speed that the bullet moves at

    bool shootAtEnemy; //bool to stop coroutine from being called every second in the coroutine


    [Header("Upgrade Per Level")]
    //values for upgradin tower stats
    [SerializeField]
    float durabilityUpgrade;
    [SerializeField]
    float rangeUpgade;
    [SerializeField]
    float fireRateUpgrade;
    [SerializeField]
    float damageUpgrade;


    [Header("Towers")]
    [SerializeField]
    GameObject[] towers; //stores towers

    //stores scripts
    FireRateTower fireRateTower;
    DamageTower damageTower;
    RangeTower rangeTower;


    void Awake()
    {
        shootAtEnemy = true; //initailize to true
        //initialize base values
        level = 0;
        baseDurability = maxDurability;
        baseRange = range;
        baseFireRate = fireRate;
        baseDamage = damage;
        currentDurability = baseDurability;

        //disable all the scripts at the start of the game
        fireRateTower = GetComponent<FireRateTower>();
        damageTower = GetComponent<DamageTower>();
        rangeTower = GetComponent<RangeTower>();

        fireRateTower.enabled = false;
        damageTower.enabled = false;
        rangeTower.enabled = false;
    }


    void FixedUpdate()
    {
        //check if any enemies are near tower
        enemies = Physics.OverlapBox(new Vector3(transform.position.x, 10, transform.position.z), new Vector3(range, 20, range), Quaternion.identity, enemyLayerMask);
    }

    void Update()
    {
        if(enemies != null && enemies.Length != 0)
        {
            if(shootAtEnemy) //check if can shoot at enemy
            {
                //start coroutine to shoot at enemies
                StartCoroutine(ShootBullet());
            }
        }

        if(currentDurability <= 0)
        {
            DestroyTower();
        }
    }

    IEnumerator ShootBullet()
    {
        shootAtEnemy = false; //stop update from calling coroutine

        //instantiate bullet to shoot at enemy
        GameObject bullet = Instantiate(bulletPrefab);
        bullet.transform.position = new Vector3(transform.position.x, transform.position.y + 1f, transform.position.z);
        bullet.GetComponent<Bullet>().target = enemies[0].gameObject;
        bullet.GetComponent<Bullet>().speed = bulletSpeed;
        bullet.GetComponent<Bullet>().damage = damage;
        
        yield return new WaitForSeconds(fireRate); //wait to shoot bullet
        shootAtEnemy = true; //let update call coroutine
    }


    public void UpgradeTower()
    {
        level++; //increase level by 1

        //increase max durability and reset current durability of tower
        maxDurability += durabilityUpgrade;
        currentDurability = maxDurability;

        //increase tower stats
        range += rangeUpgade;
        fireRate -= fireRateUpgrade;
        damage += damageUpgrade;
    }

    void DestroyTower()
    {
        //set all stats to base values
        level = 0;
        maxDurability = baseDurability;
        currentDurability = baseDurability;
        range = baseRange;
        fireRate = baseFireRate;
        damage = baseDamage;

        //disable all tower game objects
        foreach (GameObject tower in towers)
        {
            tower.SetActive(false);
        }

        durabilityBar.SetActive(false); //disable durability bar

        //disable all scripts
        fireRateTower.enabled = false;
        damageTower.enabled = false;
        rangeTower.enabled = false;
    }


    private void OnDrawGizmos() 
    {
        //show box to check for enemies in inspector
        Gizmos.color = Color.blue;
        Gizmos.DrawWireCube(new Vector3(transform.position.x, 10, transform.position.z), new Vector3(range * 2, 20, range * 2));
    }
}
