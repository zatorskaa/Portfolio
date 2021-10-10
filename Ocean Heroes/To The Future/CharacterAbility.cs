using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterAbility : MonoBehaviour
{
    #region Variables
    [SerializeField]
    private string characterName;
    [HideInInspector]
    public bool isSelected; //check if character is selected

    //check if near obstacles
    private bool isNearSeaGrass;
    private bool isNearSeaUrchin;
    private bool isNearToxins;

    //radius to check if obstacles are near character
    [SerializeField]
    private float obstacleCheckRadius;

    //layer masks for obstacles
    [Header("Masks")]
    [SerializeField]
    private LayerMask seaGrassMask;
    [SerializeField]
    private LayerMask seaUrchinMask;
    [SerializeField]
    private LayerMask toxinsMask;

    //colliders for obstacles
    private Collider2D seaGrassCollider;
    private Collider2D seaUrchinCollider;
    private Collider2D toxinsCollider;
    #endregion

    private void FixedUpdate()
    {
        //check for obstacles near character
        isNearSeaGrass = Physics2D.OverlapCircle(transform.position, obstacleCheckRadius, seaGrassMask);
        isNearSeaUrchin = Physics2D.OverlapCircle(transform.position, obstacleCheckRadius, seaUrchinMask);
        isNearToxins = Physics2D.OverlapCircle(transform.position, obstacleCheckRadius, toxinsMask);

        //store collider of obstacle near character
        seaGrassCollider = Physics2D.OverlapCircle(transform.position, obstacleCheckRadius, seaGrassMask);
        seaUrchinCollider = Physics2D.OverlapCircle(transform.position, obstacleCheckRadius, seaUrchinMask);
        toxinsCollider = Physics2D.OverlapCircle(transform.position, obstacleCheckRadius, toxinsMask);
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.E)) //check if 'e' key is pressed
        {
            if(isSelected && characterName == "Turtle") //check if turtle is selected
            {
                TurtleAbility();
            }
            else if(isSelected && characterName == "Otter") //check if otter is selected
            {
                OtterAbility();
            }
            else if(isSelected && characterName == "Mussel") //check if mussel is selected
            {
                MusselAbility();
            }
        }
    }

    private void TurtleAbility()
    {
        if (isNearSeaGrass) //check if near any sea grass
        {
            SeaGrass seaGrass = seaGrassCollider.GetComponent<SeaGrass>(); //get sea grass script
            seaGrass.BreakSeaGrass(); //call function to break sea grass
            Debug.Log("Break Sea Grass");
        }
    }

    private void OtterAbility()
    {
        if(isNearSeaUrchin)
        {
            SeaUrchin seaUrchin = seaUrchinCollider.GetComponent<SeaUrchin>(); //get sea urchin script
            seaUrchin.CollectSeaUrchin(); //call function to collect sea urchin
            Debug.Log("Collect Sea Urchin");
        }
    }

    private void MusselAbility()
    {
        if(isNearToxins)
        {
            Toxins toxins = toxinsCollider.GetComponent<Toxins>(); //get toxins script
            toxins.RemoveToxin(); //call function to remove toxin
            Debug.Log("Remove Toxin");
        }
    }



    private void OnDrawGizmos()
    {
        Gizmos.color = Color.white;
        Gizmos.DrawWireSphere(transform.position, obstacleCheckRadius);
    }
}
