using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Keypad : MonoBehaviour
{
    [SerializeField]
    private int[] code;
    private List<int> codeInput;
    [SerializeField]
    private Text codeUI;
    private bool isCorrect;
    private bool isInRange;

    [SerializeField]
    private GameObject gameFinishedText;


    private void Awake()
    {
        ResetCodeInput();
        isCorrect = false; //initialize to false
        isInRange = false;
        gameFinishedText.SetActive(false); //disable game object
    }

    private void Update()
    {
        if(isCorrect == false)
        {
            InputCode(); //if code isn't correct call function to let player enter code
        }
        else
        {
            Debug.Log("Correct Code Entered");
            gameFinishedText.SetActive(true); //activate game object to display message to player
        }
    }


    void InputCode()
    {
        if (isInRange) //check if player is near keypad
        {
            if(Input.GetKeyDown(KeyCode.R))
            {
                ResetCodeInput(); //call function to reset code input
            }
            else if(Input.GetKeyDown(KeyCode.E))
            {
                isCorrect = CheckCode(); //call function to check if code input is correct
            }

            if(codeInput.Count < code.Length) //if the code input length is less than the code length
            {
                if(Input.GetKeyDown(KeyCode.Alpha1) || Input.GetKeyDown(KeyCode.Keypad1)) //check if user enters 1
                {
                    codeInput.Add(1); //add 1 to the code input list
                    ShowCode();
                }
                else if(Input.GetKeyDown(KeyCode.Alpha2) || Input.GetKeyDown(KeyCode.Keypad2)) //check if user enters 2
                {
                    codeInput.Add(2); //add 2 to the code input list
                    ShowCode();
                }
                else if (Input.GetKeyDown(KeyCode.Alpha3) || Input.GetKeyDown(KeyCode.Keypad3)) //check if user enters 3
                {
                    codeInput.Add(3); //add 3 to the code input list
                    ShowCode();
                }
                else if (Input.GetKeyDown(KeyCode.Alpha4) || Input.GetKeyDown(KeyCode.Keypad4)) //check if user enters 4
                {
                    codeInput.Add(4); //add 4 to the code input list
                    ShowCode();
                }
                else if (Input.GetKeyDown(KeyCode.Alpha5) || Input.GetKeyDown(KeyCode.Keypad5)) //check if user enters 5
                {
                    codeInput.Add(5); //add 5 to the code input list
                    ShowCode();
                }
                else if (Input.GetKeyDown(KeyCode.Alpha6) || Input.GetKeyDown(KeyCode.Keypad6)) //check if user enters 6
                {
                    codeInput.Add(6); //add 6 to the code input list
                    ShowCode();
                }
                else if (Input.GetKeyDown(KeyCode.Alpha7) || Input.GetKeyDown(KeyCode.Keypad7)) //check if user enters 7
                {
                    codeInput.Add(7); //add 7 to the code input list
                    ShowCode();
                }
                else if (Input.GetKeyDown(KeyCode.Alpha8) || Input.GetKeyDown(KeyCode.Keypad8)) //check if user enters 8
                {
                    codeInput.Add(8); //add 8 to the code input list
                    ShowCode();
                }
                else if (Input.GetKeyDown(KeyCode.Alpha9) || Input.GetKeyDown(KeyCode.Keypad9)) //check if user enters 9
                {
                    codeInput.Add(9); //add 9 to the code input list
                    ShowCode();
                }
                else if (Input.GetKeyDown(KeyCode.Alpha0) || Input.GetKeyDown(KeyCode.Keypad0)) //check if user enters 0
                {
                    codeInput.Add(0); //add 0 to the code input list
                    ShowCode();
                }
            }
        }
    }

    void ResetCodeInput()
    {
        codeUI.text = ""; //reset code text
        codeInput = new List<int>(); //create new list for code input
    }

    bool CheckCode()
    {
        if(codeInput.Count == code.Length)
        {
            for (int i = 0; i < code.Length; i++)
            {
                if (code[i] != codeInput[i]) //check if the code input by user is correct
                {
                    return false; //if there is a number that doesn't match return false
                }
            }

            return true; //if all numbers match return true
        }
        else
        {
            return false; //if code is not correct length return false
        }
    }

    void ShowCode()
    {
        string codeString = "";

        for(int i = 0; i < codeInput.Count; i++)
        {
            codeString += codeInput[i].ToString(); //convert each number in code input to a string
        }

        codeUI.text = codeString; //disply code entered on UI
        Debug.Log(codeString);
    }

    private void OnTriggerStay(Collider collider)
    {
        if (collider.CompareTag("Player"))
        {
            isInRange = true; //check if player is in trigger collider
        }
    }

    private void OnTriggerExit(Collider collider)
    {
        if (collider.CompareTag("Player"))
        {
            isInRange = false; //check if player left trigger collider
        }
    }
}
