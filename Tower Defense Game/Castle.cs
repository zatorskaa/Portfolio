using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Castle : MonoBehaviour
{
    [SerializeField]
    float maxDurability; //store max durability of castle
    [HideInInspector]
    public float currentDurability; //store current durability of castle

    [SerializeField]
    Slider durabilityBar; //stores slider component for durability bar


    private void Awake()
    {
        //enable durability bar and set max value to max durability
        durabilityBar.gameObject.SetActive(true);
        durabilityBar.maxValue = maxDurability;
        currentDurability = maxDurability;
    }

    private void Update()
    {
        if(currentDurability >= 0)
        {
            durabilityBar.value = currentDurability; //set slider value as current durability
        }
        else if (currentDurability < 0)
        {
            durabilityBar.value = 0;
        }
    }
}
