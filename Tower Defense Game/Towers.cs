using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Towers : MonoBehaviour
{
    [SerializeField]
    GameObject[] towersFireRate; //stores towers with higher fire rate
    [SerializeField]
    GameObject[] towersDamage; //stores towers with higher damage
    [SerializeField]
    GameObject[] towersRange; //stores towers with higher range

    [SerializeField]
    GameObject menuUI; //stores the ui to show when a tower is clicked
    [SerializeField]
    GameObject buyButton; //stores buy button on canvas
    [SerializeField]
    GameObject upgradeButton; //stores upgrade button on canvas
    [SerializeField]
    GameObject maxLevelText; //stores text to show max level
    [SerializeField]
    Slider durabilityBar; //stores slider component for durability bar

    //store the tower script
    FireRateTower fireRateTower;
    DamageTower damageTower;
    RangeTower rangeTower;

    //store text components to show user cost of each tower
    [SerializeField]
    Text fireRateTowerCostText;
    [SerializeField]
    Text damageTowerCostText;
    [SerializeField]
    Text rangeTowerCostText;
    [SerializeField]
    Text upgradeCostText;


    private void Awake()
    {
        //get all scripts at the start of the game
        fireRateTower = gameObject.GetComponentInParent<FireRateTower>();
        damageTower = gameObject.GetComponentInParent<DamageTower>();
        rangeTower = gameObject.GetComponentInParent<RangeTower>();

        durabilityBar.gameObject.SetActive(false);

        fireRateTowerCostText.text = fireRateTower.towerCost.ToString();
        damageTowerCostText.text = damageTower.towerCost.ToString();
        rangeTowerCostText.text = rangeTower.towerCost.ToString();
    }

    private void Update()
    {
        //set the slider value for the durability bar
        if(fireRateTower.level > 0 && durabilityBar.gameObject.activeSelf)
        {
            if(fireRateTower.currentDurability >= 0)
            {
                durabilityBar.value = fireRateTower.currentDurability;
            }
            else if (fireRateTower.currentDurability < 0)
            {
                durabilityBar.value = 0;
            }
        }
        else if (damageTower.level > 0 && durabilityBar.gameObject.activeSelf)
        {
            if (damageTower.currentDurability >= 0)
            {
                durabilityBar.value = damageTower.currentDurability;
            }
            else if (damageTower.currentDurability < 0)
            {
                durabilityBar.value = 0;
            }
        }
        else if (rangeTower.level > 0 && durabilityBar.gameObject.activeSelf)
        {
            if (rangeTower.currentDurability >= 0)
            {
                durabilityBar.value = rangeTower.currentDurability;
            }
            else if (rangeTower.currentDurability < 0)
            {
                durabilityBar.value = 0;
            }
        }
    }

    public void ToggleUI()
    {
        menuUI.SetActive(!menuUI.activeSelf); //if ui is enabled, disabled it. if ui is disbaled, enable it

        if(menuUI.activeSelf)
        {
            bool towerExists = false; //used check if a tower alreaady exists in that place
            bool maxTowerLevel = false; //used to check if tower is at max level

            if (fireRateTower.level > 0 || damageTower.level > 0 || rangeTower.level > 0)
            {
                towerExists = true; //if the tower level is above 0, a tower exists in that place
            }

            if (fireRateTower.level == towersFireRate.Length || damageTower.level == towersDamage.Length || rangeTower.level == towersRange.Length)
            {
                maxTowerLevel = true; //if tower level is the same as length of array, it is at max level
            }

            if(!towerExists)
            {
                //if tower doesn't exit show buy button and hide upgrade button and max level text
                buyButton.SetActive(true);
                upgradeButton.SetActive(false);
                maxLevelText.SetActive(false);
            }
            else if(towerExists && !maxTowerLevel)
            {
                //if tower exists and is not at max level show upgrade button and hide buy button and max level text
                buyButton.SetActive(false);
                upgradeButton.SetActive(true);
                maxLevelText.SetActive(false);

                if(fireRateTower.level > 0)
                {
                    upgradeCostText.text = fireRateTower.upgradeCost.ToString();
                }
                else if(damageTower.level > 0)
                {
                    upgradeCostText.text = damageTower.upgradeCost.ToString();
                }
                else if(rangeTower.level > 0)
                {
                    upgradeCostText.text = rangeTower.upgradeCost.ToString();
                }
            }
            else
            {
                //if tower is at max level show max level text and hide buy and upgrade buttons
                buyButton.SetActive(false);
                upgradeButton.SetActive(false);
                maxLevelText.SetActive(true);
            }
        }
    }


}
