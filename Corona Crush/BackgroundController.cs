using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackgroundController : MonoBehaviour
{
    #region Variables
    public float parallaxEffect; //variable that decides by how much the background moves compared to the camera

    public Camera cam; //stores camera game object
    private Vector3 previousCameraPosition; //stores previous position of camera
    private Vector3 currentCameraPosition; //stores current camera position
    private float distance; //stores distance camera has moved between frames

    private Vector3 backgroundPosition; //stores previous background position
    private float width; //stores the width of the background sprite
    #endregion

    private void Start()
    {
        transform.position = new Vector3(cam.transform.position.x, transform.position.y, transform.position.z); //set start x position of background to same x position as camera

        previousCameraPosition = cam.transform.position; //sets start value of previous camera position to its position at the start of the game
        backgroundPosition = transform.position; //sets starts value of background position to its position at the start of the game

        width = GetComponent<SpriteRenderer>().bounds.size.x; //finds the width of the background sprite
    }

    private void LateUpdate()
    {
        currentCameraPosition = cam.transform.position; //sets current camera position to its position in the current frame
        distance = currentCameraPosition.x - previousCameraPosition.x; //calculate how much the camera has moved between frames

        if(currentCameraPosition.x > backgroundPosition.x + width) //if the camera moves more than the current background position plus the width of the sprite
        {
            transform.position = new Vector3(backgroundPosition.x + width + (distance * parallaxEffect), transform.position.y, transform.position.z); //moves background to its previous position plus the width of the sprite plus the camera position times the parallax effect variable
        }
        else if(currentCameraPosition.x < backgroundPosition.x - width) //if the camera moves less than the current background position minus the width of the sprite
        {
            transform.position = new Vector3(backgroundPosition.x - width + (distance * parallaxEffect), transform.position.y, transform.position.z); //moves background to its previous position minus the width of the sprite plus the camera position times the parallax effect variable
        }
        else
        {
            transform.position = new Vector3(backgroundPosition.x + (distance * parallaxEffect), transform.position.y, transform.position.z); //moves background to its previous position plus the camera position times the parallax effect variable
        }

        backgroundPosition = transform.position; //sets the background position variable to the new position for the next frame
        previousCameraPosition = currentCameraPosition; //sets the previous camera position to current camera position for the next frame
    }
}
