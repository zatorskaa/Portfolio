using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    [HideInInspector]
    public GameObject target;
    [HideInInspector]
    public float speed;
    [HideInInspector]
    public float damage;

    void Update()
    {
        if(target != null)
        {
            transform.position = Vector3.MoveTowards(transform.position, target.transform.position, speed * Time.deltaTime); //move bullet towards enemey
        }
        else
        {
            Destroy(gameObject);
        }
    }
}
