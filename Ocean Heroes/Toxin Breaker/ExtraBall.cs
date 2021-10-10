using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExtraBall : MonoBehaviour
{
    private Rigidbody2D rb;
    [SerializeField]
    private int force;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        rb.AddForce(new Vector2(force, force)); //add forve to the ball to move it
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.collider.CompareTag("Bottom"))
        {
            Destroy(gameObject);
        }
    }
}
