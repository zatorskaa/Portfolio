using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackgroundAnimations : MonoBehaviour
{
    #region Variables
    public Camera cam; //stores camera game object

    private Animator anim; //stores animator component of background object
    public AnimationClip[] backgroundAnimations = new AnimationClip[4]; //stores animation clips of background animations
    private float[] animationLength = new float[4]; //stores the length of each background animation
    private bool[] animationPlayed = new bool[4]; //stores bool to check if each animation has been played

    public GameObject[] bridges = new GameObject[4]; //array for storing bridge objects
    private Vector3[] bridgePositions = new Vector3[4]; //array for storing bridge positions

    public GameObject[] sky = new GameObject[5]; //array for storing the game objects with the sky sprites
    public GameObject[] clouds = new GameObject[5]; //array for storing the game objects with the cloud sprites
    #endregion

    private void Start()
    {
        anim = GetComponent<Animator>(); //store animator component

        for(int i = 0; i < backgroundAnimations.Length; i++)
        {
            animationLength[i] = backgroundAnimations[0].length; //find the length of each animation clip
            animationPlayed[i] = false; //sets the bool at each animationPlayed index to false
        }

        for (int i = 0; i < bridges.Length; i++)
        {
            bridgePositions[i] = bridges[i].transform.position; //find the position of each bridge and add to array
        }

        //enable the first sky and cloud objects
        sky[0].SetActive(true);
        clouds[0].SetActive(true);
        for(int i = 1; i < sky.Length; i++)
        {
            //disable all the sky and cloud objects except the first ones
            sky[i].SetActive(false); 
            clouds[i].SetActive(false);
        } 
    }

    private void Update()
    {
        if(cam.transform.position.x > bridgePositions[0].x && animationPlayed[0] == false) //if the camera moves past the position of the first bridge and the first animation has not been played
        {
            StartCoroutine(AnimationOne()); //calls coroutine for first animation
        }

        if(cam.transform.position.x > bridgePositions[1].x && animationPlayed[1] == false) //if the camera moves past the position of the second bridge and the second animation has not been played
        {
            StartCoroutine(AnimationTwo()); //calls coroutine for second animation
        }

        if (cam.transform.position.x > bridgePositions[2].x && animationPlayed[2] == false) //if the camera moves past the position of the third bridge and the third animation has not been played
        {
            StartCoroutine(AnimationThree()); //calls coroutine for third animation
        }

        if (cam.transform.position.x > bridgePositions[3].x && animationPlayed[3] == false) //if the camera moves past the position of the fourth bridge and the fourth animation has not been played
        {
            StartCoroutine(AnimationFour()); //calls coroutine for fourth animation
        }
    }

    IEnumerator AnimationOne()
    {
        //enable second sky and cloud objects
        sky[1].SetActive(true);
        clouds[1].SetActive(true);

        anim.SetBool("stageOneFinished", true); //set the transition condition for first animation to true

        yield return new WaitForSeconds(animationLength[0] + 1f); //coroutine waits for the length of the animation before disabling the first sky and cloud objects

        //disable first sky and cloud objects
        sky[0].SetActive(false);
        clouds[0].SetActive(false);

        animationPlayed[0] = true; //sets animationPlayed for first animation to true
    }

    IEnumerator AnimationTwo()
    {
        //enable third sky and cloud objects
        sky[2].SetActive(true);
        clouds[2].SetActive(true);

        anim.SetBool("stageTwoFinished", true); //set the transition condition for second animation to true

        yield return new WaitForSeconds(animationLength[1] + 1f); //coroutine waits for the length of the animation before disabling the second sky and cloud objects

        //disable second sky and cloud objects
        sky[1].SetActive(false);
        clouds[1].SetActive(false);

        animationPlayed[1] = true; //sets animationPlayed for second animation to true
    }

    IEnumerator AnimationThree()
    {
        //enable fourth sky and cloud objects
        sky[3].SetActive(true);
        clouds[3].SetActive(true);

        anim.SetBool("stageThreeFinished", true); //set the transition condition for third animation to true

        yield return new WaitForSeconds(animationLength[2] + 1f); //coroutine waits for the length of the animation before disabling the second sky and cloud objects

        //disable third sky and cloud objects
        sky[2].SetActive(false);
        clouds[2].SetActive(false);

        animationPlayed[2] = true; //sets animationPlayed for third animation to true
    }

    IEnumerator AnimationFour()
    {
        //enable fifth sky and cloud objects
        sky[4].SetActive(true);
        clouds[4].SetActive(true);

        anim.SetBool("stageFourFinished", true); //set the transition condition for fourth animation to true

        yield return new WaitForSeconds(animationLength[3] + 1f); //coroutine waits for the length of the animation before disabling the second sky and cloud objects

        //disable fourth sky and cloud objects
        sky[3].SetActive(false);
        clouds[3].SetActive(false);

        animationPlayed[3] = true; //sets animationPlayed for fourth animation to true
    }
}
