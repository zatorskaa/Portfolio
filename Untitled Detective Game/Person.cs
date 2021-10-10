using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Person : MonoBehaviour
{
    #region Variables
    bool isInteracting; //check if player is interacting with the person
    bool isFound;

    bool playerIsNear; //check if player is near evidence
    [SerializeField]
    Vector3 boxDimensions; //dimensions of box around person to check for player
    [SerializeField]
    LayerMask playerLayerMask;

    [SerializeField]
    GameObject dialogueUI; //dialogue ui canvas
    [SerializeField]
    GameObject[] dialogueOptionsText; //list of dialogue options for person
    [SerializeField]
    GameObject[] dialogueAnswersText; //list of dialogue options for person

    //button objects from case files ui
    [SerializeField]
    GameObject caseFilesPersonName;
    [SerializeField]
    GameObject[] caseFilesPersonInfo;

    [SerializeField]
    CaseFiles caseFiles;

    [SerializeField]
    PlayerMovement player;
    #endregion


    private void Start()
    {
        isInteracting = false; //set to false at start of game
        isFound = false;

        //disable ui
        dialogueUI.SetActive(false);
        caseFilesPersonName.SetActive(false);

        for (int i = 0; i < caseFilesPersonInfo.Length; i++)
        {
            caseFilesPersonInfo[i].SetActive(false);
        }


        if (dialogueOptionsText.Length != dialogueAnswersText.Length)
        {
            Debug.Log("The number of dialogue options and answers do not match"); //debug log check to make sure the number of dialogue options and answers is the same
        }

        DisableAnswers();
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
                dialogueUI.SetActive(true); //if player is interacting with the person enable ui
            }
            else if (Input.GetKeyDown(KeyCode.I) && !isInteracting)
            {
                DisableAnswers();
                dialogueUI.SetActive(false); //if player is not interacting with person disable ui
            }
        }

        FoundPerson();
    }

    private void FixedUpdate()
    {
        playerIsNear = Physics.CheckBox(transform.position, boxDimensions, transform.rotation, playerLayerMask); //check if player is near person
    }


    void FoundPerson()
    {
        if (isFound && !caseFilesPersonName.activeInHierarchy)
        {
            caseFilesPersonName.SetActive(true); //show person name in case files
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
                    caseFiles.numberOfPeopleFound++; //increase number of evidence found when new evidence is added to case files
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

    public void ChangeButtonText(int buttonNumber)
    {
        //change the text displayed on the button
        if(dialogueOptionsText[buttonNumber].activeInHierarchy)
        {
            dialogueOptionsText[buttonNumber].SetActive(false);
            dialogueAnswersText[buttonNumber].SetActive(true);
        }
        else
        {
            dialogueOptionsText[buttonNumber].SetActive(true);
            dialogueAnswersText[buttonNumber].SetActive(false);
        }

        if(!caseFilesPersonInfo[buttonNumber].activeInHierarchy)
        {
            caseFilesPersonInfo[buttonNumber].SetActive(true); //show person info for that question in case files
        }
    }

    void DisableAnswers()
    {
        for (int i = 0; i < dialogueOptionsText.Length; i++)
        {
            dialogueOptionsText[i].SetActive(true); //enable all the dialogue options
        }

        for (int i = 0; i < dialogueAnswersText.Length; i++)
        {
            dialogueAnswersText[i].SetActive(false); //disable all the dialogue answers
        }
    }
}
