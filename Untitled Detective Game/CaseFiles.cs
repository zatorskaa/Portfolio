using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CaseFiles : MonoBehaviour
{
    #region Variables
    [SerializeField]
    GameObject caseFilesUI;
    [SerializeField]
    GameObject caseSolvedUI;
    [SerializeField]
    GameObject evidenceNumberUI;

    //stores toggle object component of correct evidence and person
    [SerializeField]
    Toggle[] correctEvidenceInfo;
    [SerializeField]
    Toggle[] correctPersonName;
    //stores toggle oject component of other evidence and people (not including correct ones)
    [SerializeField]
    Toggle[] otherEvidenceInfo;
    [SerializeField]
    Toggle[] otherPersonName;

    //store text components to set number of evidence and people found
    [SerializeField]
    Text evidenceNumberText;
    [SerializeField]
    Text peopleNumberText;

    //used to check if all correct evidence is selected and all incorrect evidence is deselected
    int numberOfCorrectEvidence;
    int numberOfCorrectPeople;
    int numberOfIncorrectEvidence;
    int numberOfIncorrectPeople;

    //variables to check if correct evidence is selected
    bool correctEvidenceSelected;
    bool correctPersonSelected;

    //variables used to store number of evidence to be found and current number found
    int totalNumberOfEvidence;
    int totalNumberOfPeople;
    [HideInInspector]
    public int numberOfEvidenceFound;
    [HideInInspector]
    public int numberOfPeopleFound;

    [SerializeField]
    PlayerMovement player;
    [SerializeField]
    PauseMenu pauseMenu;

    [SerializeField]
    int sceneToLoadBuildIndex;
    [SerializeField]
    bool missionFinished;
    [SerializeField]
    int missionNumber;
    #endregion


    private void Start()
    {
        //set variables at start of game
        caseFilesUI.SetActive(false);
        caseSolvedUI.SetActive(false);
        evidenceNumberUI.SetActive(true);

        correctEvidenceSelected = false;
        correctPersonSelected = false;

        //reset counters
        numberOfCorrectEvidence = 0;
        numberOfCorrectPeople = 0;
        numberOfIncorrectEvidence = 0;
        numberOfIncorrectPeople = 0;

        //find the total number of evidence and people in current case
        totalNumberOfEvidence = correctEvidenceInfo.Length + otherEvidenceInfo.Length;
        totalNumberOfPeople = correctPersonName.Length + otherPersonName.Length;
    }

    private void Update()
    {
        if (!pauseMenu.pauseMenuUI.activeInHierarchy) //if pause menu is not active
        {
            if (!caseFilesUI.activeInHierarchy)
            {
                evidenceNumberUI.SetActive(true); //show number of evidence found
            }
                
            if (!correctEvidenceSelected || !correctPersonSelected) //if correct evidence and person has not been selected
            {
                ToggleCaseFilesMenu();
            }

            CheckSelectedEvidence();
            SetEvidenceNumber();
        }
        else
        {
            evidenceNumberUI.SetActive(false); //hide number of evidence found
        }
    }

    void ToggleCaseFilesMenu()
    {
        if(!player.isInteracting)
        {
            if (Input.GetKeyDown(KeyCode.M)) //check if m key is pressed
            {
                if (caseFilesUI.activeInHierarchy) //check if case files menu is active
                {
                    caseFilesUI.SetActive(false); //if yes hide the menu

                    //set player and pause menu variables to false
                    player.menuIsOpen = false;
                    pauseMenu.caseFilesIsOpen = false;

                    evidenceNumberUI.SetActive(true); //show number of evidence found
                }
                else
                {
                    caseFilesUI.SetActive(true); //if no show the menu

                    //set player and pause menu variables to true
                    player.menuIsOpen = true;
                    pauseMenu.caseFilesIsOpen = true;

                    evidenceNumberUI.SetActive(false); //hide number of evidence found
                }
            }
        }
    }

    void CheckSelectedEvidence()
    {
        if(!correctEvidenceSelected || !correctPersonSelected) //if the correct evidence and person hasn't been selected yet
        {
            //reset counters
            numberOfCorrectEvidence = 0;
            numberOfCorrectPeople = 0;
            numberOfIncorrectEvidence = 0;
            numberOfIncorrectPeople = 0;

            for (int i = 0; i < correctEvidenceInfo.Length; i++)
            {
                if (correctEvidenceInfo[i].isOn)
                {
                    numberOfCorrectEvidence++; //check number of correct evidence selected
                }
            }

            for (int i = 0; i < correctPersonName.Length; i++)
            {
                if (correctPersonName[i].isOn)
                {
                    numberOfCorrectPeople++; //check number of correct people selected
                }
            }

            for (int i = 0; i < otherEvidenceInfo.Length; i++)
            {
                if (otherEvidenceInfo[i].isOn)
                {
                    numberOfIncorrectEvidence++; //check number of incorrect evidence selected
                }
            }

            for (int i = 0; i < otherPersonName.Length; i++)
            {
                if (otherPersonName[i].isOn)
                {
                    numberOfIncorrectPeople++; //check number of incorrect people selected
                }
            }


            if(numberOfCorrectEvidence == correctEvidenceInfo.Length && numberOfIncorrectEvidence == 0)
            {
                correctEvidenceSelected = true; //if all correct evidence is selected and all incorrect evidence is deselcted set to true
            }
            else
            {
                correctEvidenceSelected = false;
            }

            if(numberOfCorrectPeople == correctPersonName.Length && numberOfIncorrectPeople == 0)
            {
                correctPersonSelected = true; //if all correct people are selected and all incorrect people are deselcted set to true
            }
            else
            {
                correctPersonSelected = false;
            }

            if(correctEvidenceSelected && correctPersonSelected)
            {
                caseSolvedUI.SetActive(true);

                StartCoroutine(CaseSolved());
            }
        }
    }


    void SetEvidenceNumber()
    {
        //set the number of evidence and people found in the ui
        evidenceNumberText.text = numberOfEvidenceFound.ToString() + "/" + totalNumberOfEvidence.ToString();
        peopleNumberText.text = numberOfPeopleFound.ToString() + "/" + totalNumberOfPeople.ToString();
    }

    IEnumerator CaseSolved()
    {
        if (missionFinished)
        {
            //set mission to finished in game manager
            GameManager.instance.MissionFinished(missionNumber);
        }

        //if case is solved go back to main game area
        yield return new WaitForSeconds(3f);

        SceneManager.LoadScene(sceneToLoadBuildIndex);
    }
}
