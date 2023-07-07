using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TowerMenu : MonoBehaviour
{
    [SerializeField]
    GameObject[] towersFireRate; //stores towers with higher fire rate
    [SerializeField]
    GameObject[] towersDamage; //stores towers with higher damage
    [SerializeField]
    GameObject[] towersRange; //stores towers with higher range

    [SerializeField]
    Slider durabilityBar; //stores slider component for durability bar
    [SerializeField]
    GameObject notEnoughCoinsText;

    //stores scripts
    FireRateTower fireRateTower;
    DamageTower damageTower;
    RangeTower rangeTower;


    private void Awake()
    {
        //get all scripts at the start of the game
        fireRateTower = gameObject.GetComponentInParent<FireRateTower>();
        damageTower = gameObject.GetComponentInParent<DamageTower>();
        rangeTower = gameObject.GetComponentInParent<RangeTower>();
    }


    public void BuyFireRate() //buy tower with higher fire rate
    {
        if(fireRateTower.towerCost <= CurrencySystem.coins) //check if player has enough coins to buy tower
        {
            towersFireRate[0].SetActive(true); //enable the first tower
            gameObject.SetActive(false); //disable tower ui

            fireRateTower.enabled = true; //enable fire rate tower script
            fireRateTower.level = 1; //set tower level to 1

            //set the max value for the durability bar
            durabilityBar.gameObject.SetActive(true);
            durabilityBar.maxValue = fireRateTower.maxDurability;

            CurrencySystem.coins -= fireRateTower.towerCost; //decrease amount of coins
        }
        else
        {
            StartCoroutine(ShowCoinsText());
        }
    }

    public void BuyDamage() //buy tower with higher damage
    {
        if (damageTower.towerCost <= CurrencySystem.coins) //check if player has enough coins to buy tower
        {
            towersDamage[0].SetActive(true); //enable the first tower
            gameObject.SetActive(false); //disable tower ui

            damageTower.enabled = true; //enable damage tower script
            damageTower.level = 1; //set tower level to 1

            //set the max value for the durability bar
            durabilityBar.gameObject.SetActive(true);
            durabilityBar.maxValue = damageTower.maxDurability;

            CurrencySystem.coins -= damageTower.towerCost; //decrease amount of coins
        }
        else
        {
            StartCoroutine(ShowCoinsText());
        }
    }

    public void BuyRange() //buy tower with higher range
    {
        if (rangeTower.towerCost <= CurrencySystem.coins) //check if player has enough coins to buy tower
        {
            towersRange[0].SetActive(true); //enable the first tower
            gameObject.SetActive(false); //disable tower ui

            rangeTower.enabled = true; //enable range tower script
            rangeTower.level = 1; //set tower level to 1

            //set the max value for the durability bar
            durabilityBar.gameObject.SetActive(true);
            durabilityBar.maxValue = rangeTower.maxDurability;

            CurrencySystem.coins -= rangeTower.towerCost; //decrease amount of coins
        }
        else
        {
            StartCoroutine(ShowCoinsText());
        }
    }

    public void Upgrade()
    {
        if(fireRateTower.level > 0 && fireRateTower.level < towersFireRate.Length) //check if fire rate tower is built and not at max level
        {
            if(fireRateTower.upgradeCost <= CurrencySystem.coins) //check if player has enough coins to upgrade tower
            {
                for (int i = 0; i < towersFireRate.Length; i++)
                {
                    if (towersFireRate[i].activeSelf)
                    {
                        //disable current tower and enable next tower
                        towersFireRate[i].SetActive(false);
                        towersFireRate[i + 1].SetActive(true);

                        fireRateTower.UpgradeTower(); //call function to upgrade tower stats

                        durabilityBar.maxValue = fireRateTower.maxDurability; //set the max value for the durability bar

                        gameObject.SetActive(false); //disable tower ui
                        break;
                    }
                }

                CurrencySystem.coins -= fireRateTower.upgradeCost; //decrease amount of coins
            }
            else
            {
                StartCoroutine(ShowCoinsText());
            }
        }

        if(damageTower.level > 0 && damageTower.level < towersDamage.Length) //check if damage tower is built and not at max level
        {
            if (damageTower.upgradeCost <= CurrencySystem.coins) //check if player has enough coins to upgrade tower
            {
                for (int i = 0; i < towersDamage.Length; i++)
                {
                    if (towersDamage[i].activeSelf)
                    {
                        //disable current tower and enable next tower
                        towersDamage[i].SetActive(false);
                        towersDamage[i + 1].SetActive(true);

                        damageTower.UpgradeTower(); //call function to upgrade tower stats

                        durabilityBar.maxValue = damageTower.maxDurability; //set the max value for the durability bar

                        gameObject.SetActive(false); //disable tower ui
                        break;
                    }
                }

                CurrencySystem.coins -= damageTower.upgradeCost; //decrease amount of coins
            }
            else
            {
                StartCoroutine(ShowCoinsText());
            }
        }


        if(rangeTower.level > 0 && rangeTower.level < towersRange.Length) //check if range tower is built and not at max level
        {
            if(rangeTower.upgradeCost <= CurrencySystem.coins) //check if player has enough coins to upgrade tower
            {
                for (int i = 0; i < towersRange.Length; i++)
                {
                    if (towersRange[i].activeSelf)
                    {
                        //disable current tower and enable next tower
                        towersRange[i].SetActive(false);
                        towersRange[i + 1].SetActive(true);

                        rangeTower.UpgradeTower(); //call function to upgrade tower stats

                        durabilityBar.maxValue = rangeTower.maxDurability; //set the max value for the durability bar

                        gameObject.SetActive(false); //disable tower ui
                        break;
                    }
                }

                CurrencySystem.coins -= rangeTower.upgradeCost; //decrease amount of coins
            }
            else
            {
                StartCoroutine(ShowCoinsText());
            }
        }
    }


    IEnumerator ShowCoinsText()
    {
        //if player doesn't have enough coins to buy or upgrade show text
        notEnoughCoinsText.SetActive(true);

        yield return new WaitForSeconds(3f);

        notEnoughCoinsText.SetActive(false);
    }
}
