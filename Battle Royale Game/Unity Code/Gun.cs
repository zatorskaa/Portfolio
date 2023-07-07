using UnityEngine;

public class Gun : MonoBehaviour
{
    //damage and range of raycast gun
    [SerializeField] float damage;
    [SerializeField] float range;

    public Camera cam;

    // Update is called once per frame
    void Update()
    {
        //check for left mouse button input and call function to shoot a raycast
        if (Input.GetButtonDown("Fire1"))
        {
            Shoot();
        }
    }

    void Shoot()
    {
        //shoot a raycast
        RaycastHit hit;
        if(Physics.Raycast(cam.transform.position, cam.transform.forward, out hit, range))
        {
            //check if raycast hit object has a player component
            Player player = hit.transform.GetComponentInParent<Player>();
            if(player != null)
            {
                player.Shot(damage); //call function in player class to reduce health
            }
        }
    }

    //get functions for variables
    public float GetDamage()
    {
        return damage;
    }

    public float GetRange()
    {
        return damage;
    }
}
