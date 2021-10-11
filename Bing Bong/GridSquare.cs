using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GridSquare : MonoBehaviour
{
    [HideInInspector]
    public Vector3 location; //stores the location of the grid square

    private void Awake()
    {
        location = new Vector3(transform.position.x, transform.position.y, transform.position.z); //sets the value for the location variable
    }
}
