using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SeaGrass : MonoBehaviour
{
    [SerializeField]
    private int numberOfHits;

    public void BreakSeaGrass()
    {
        if(numberOfHits == 1) //if number of hits left is 1 destroy sea grass
        {
            Destroy(gameObject);
        }
        else
        {
            numberOfHits--; //if more than one hits left, decrease by 1
        }
    }
}
