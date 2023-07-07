using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CurrencySystem : MonoBehaviour
{
    public static int coins; //store number of coins, static so only one value exists in scene and can be accessed by all scripts without a reference

    [SerializeField]
    Text coinsText; //text component to show amount of coins to user

    private void Awake()
    {
        coins = 1000; //set the number of coins the player will have at the start
    }

    private void Update()
    {
        coinsText.text = coins.ToString(); //show the number of coins on the UI
    }
}
