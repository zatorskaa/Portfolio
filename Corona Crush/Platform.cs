using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    private Renderer rend; //stores the renderer component of the platform

    private Animator anim; //stores animator component of platform
    public AnimationClip platformAnimation; //stores the animation clip of the platform dissolving
    private float animationLength; //stores the length of the animation

    public float timeBeforeDestroy; //stores the time before the platform is destroyed

    private void Start()
    {
        rend = GetComponent<Renderer>(); //store renderer component
        anim = GetComponent<Animator>(); //store animator component

        rend.material.SetFloat("scale", 1); //set the scale variable of the platform shader material to 1 to make it fully visible
        animationLength = platformAnimation.length; //find the length of the animation dissilving the platform
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.CompareTag("PlayerFeet")) //check if player is touching the platform
        {
            StartCoroutine(DestroyPlatform()); //call coroutine to detroy platform
        }
    }

    private IEnumerator DestroyPlatform()
    {
        yield return new WaitForSeconds(timeBeforeDestroy); //wait for the time before starting animation

        anim.SetBool("destroyPlatform", true); //set animation transition condition to true

        yield return new WaitForSeconds(animationLength); //wait for the length of the animation before destroying platform

        Destroy(gameObject); //destroy the platform
    }
}
