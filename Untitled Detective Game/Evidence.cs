using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Evidence : MonoBehaviour
{
    #region Variables
    bool isInteracting; //check if player is interacting with the evidence
    bool isFound; //check if player has found evidence

    bool playerIsNear; //check if player is near evidence
    [SerializeField]
    Vector3 boxDimensions; //dimensions of box around evidence to check for player
    [SerializeField]
    LayerMask playerLayerMask;

    [SerializeField]
    GameObject evidenceUI; //evidence ui canvas

    //button objects from case files ui
    [SerializeField]
    GameObject caseFilesEvidenceInfo;

    [SerializeField]
    CaseFiles caseFiles;

    [SerializeField]
    PlayerMovement player;
    #endregion


    private void Start()
    {
        isInteracting = false; //set to false at start of game
        playerIsNear = false;
        isFound = false; //set isFound to false at start of game

        //disable ui at start of game
        evidenceUI.SetActive(false); 
        caseFilesEvidenceInfo.SetActive(false);
    }

    private void Update()
    {
        if (playerIsNear)
        {
            Interact();
        }

        if (!player.menuIsOpen)
        {
            if (Input.GetKeyDown(KeyCode.I) && isInteracting)
            {
                evidenceUI.SetActive(true); //if player is interacting with evidence show ui
            }
            else if (Input.GetKeyDown(KeyCode.I) && !isInteracting)
            {
                evidenceUI.SetActive(false); //if player is not interacting with evidence disable ui
            }
        }

        FoundEvidence();
    }

    private void FixedUpdate()
    {
        playerIsNear = Physics.CheckBox(transform.position, boxDimensions, transform.rotation, playerLayerMask); //check if player is near evidence
    }

    void FoundEvidence()
    {
        //check if evidence has been found and is not active in case files yet
        if(isFound && !caseFilesEvidenceInfo.activeInHierarchy)
        {
            caseFilesEvidenceInfo.SetActive(true);
        }
    }

    void Interact()
    {
        if (!player.menuIsOpen)
        {
            if (Input.GetKeyDown(KeyCode.I))
            {
                if (!isFound)
                {
                    caseFiles.numberOfEvidenceFound++; //increase number of evidence found when new evidence is added to case files
                }

                isInteracting = !isInteracting;
                player.isInteracting = !player.isInteracting;
                isFound = true; //if i key is pressed while player is inside collider set to true
            }
        }
    }

    private void OnDrawGizmos()
    {
        Gizmos.matrix = transform.localToWorldMatrix;
        Gizmos.color = Color.red;
        Gizmos.DrawWireCube(Vector3.zero, boxDimensions * 2);
    }
}
