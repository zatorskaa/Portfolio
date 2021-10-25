using System;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;

public class MainScript : MonoBehaviour
{
    #region Variables
    public GameObject[] bodyPartObjects = new GameObject[6]; //initialize array for storing body part objects
    private readonly SpriteRenderer[] bodyPartSpriteRenderer = new SpriteRenderer[6]; //initialize array for storing body part sprite renderers
    private readonly BodyParts[] bodyPartScript = new BodyParts[6]; //initialize array for storing body part scripts


    [Header("UI Settings")]
    public Text[] bodyPartNumberText = new Text[6]; //initialize array for storing text objects

    public GameObject arrow; //initialize variable for arrow object
    private RectTransform arrowPosition; //initialize variable for storing rect transform of arrow object
    private Arrow arrowScript; //initialize variable for storing script of arrow object

    public Text errorMessageText; //initialize variable to store text object for error message
    public Text finalCharacterText; //initialize variable to store text object for final character text
    private bool finishedCharacter; //boolean to check if user has finished choosing their character

    private int bodyPartNumber = 0; //variable for storing the current body part selected
    private readonly int[] spriteNumber = new int[9]; //array for storing the current sprite selected for each body part


    [Header("Code Settings")]
    public InputField codeInputField; //initialize variable for storing input field object
    private string codeInput; //initialize variable for storing code input by user
    private readonly string[] codeInputParts = new string[6]; //variable for storing code input by user as separate parts in array

    private string code; //variable for storing final code
    private int codeLength; //variable for storing length of code
    public Text codeOutputText; //variable for storing text component to show final code


    [Header("Random Sprite Generator Settings")]
    public int randomSpriteNumberMin = 0; //minimum random number for sprite
    public int randomSpriteNumberMax = 9; //maximum random numbr for sprite
    private int randomSpriteNumber; //stores random number created
    #endregion

    private void Start()
    {
        finishedCharacter = false; //sets bool to false
        codeInputField.interactable = true; //enables input field

        for(int i = 0; i < bodyPartObjects.Length; i++) //for each body part
        {
            bodyPartSpriteRenderer[i] = bodyPartObjects[i].GetComponent<SpriteRenderer>(); //store sprite renderers in array
            bodyPartScript[i] = bodyPartObjects[i].GetComponent<BodyParts>(); //store body part script in array

            spriteNumber[i] = 0; //reset all sprites to first sprite
            bodyPartSpriteRenderer[i].sprite = bodyPartScript[i].bodyPartSprites[spriteNumber[i]]; //sets sprite renderer of each body part to first sprite

            bodyPartNumberText[i].text = (bodyPartNumber).ToString(); //reset all body part text to 0 at start
        }

        arrowPosition = arrow.GetComponent<RectTransform>(); //store arrow rect transform
        arrowScript = arrow.GetComponent<Arrow>(); //store arrow script
        arrowPosition.anchoredPosition = new Vector2(arrowPosition.anchoredPosition.x, arrowScript.arrowPositions[bodyPartNumber]); //sets position of arrow to first position in array

        errorMessageText.text = ""; //resets error message text to empty
        finalCharacterText.text = ""; //resets final character text to empty

        code = ""; //resets code
        codeLength = bodyPartObjects.Length; //set code length to same as length of body part array
        codeOutputText.text = ""; //resets code text on screen
    }

    private void Update()
    {
        if(finishedCharacter == false) //if the user doesn't press e to end let them choose sprites
        {
            ChooseBodyPart();
            ChooseSprite();

            if (Input.GetKeyDown(KeyCode.E))
            {
                OutputCode(); //if e key pressed call function to output code
            }

            if (Input.GetKeyDown(KeyCode.R))
            {
                ChooseRandomSprites(); //if r key pressed call function to choose random sprite
            }
        }
    }

    private void ChooseBodyPart()
    {
        if ((Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.DownArrow)) && bodyPartNumber < 5) //if down arrow or s key is pressed and the selected body part isn't the last one
        {
            bodyPartNumber++; //select the next body part

            arrowPosition.anchoredPosition = new Vector2(arrowPosition.anchoredPosition.x, arrowScript.arrowPositions[bodyPartNumber]); //move the arrow to the selected body part
        }
        else if ((Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.UpArrow)) && bodyPartNumber > 0) //if up arrow or w key is pressed and the selected body part isn't the first one
        {
            bodyPartNumber--; //select the previous body part

            arrowPosition.anchoredPosition = new Vector2(arrowPosition.anchoredPosition.x, arrowScript.arrowPositions[bodyPartNumber]); //move the arrow to the selected body part
        }
    }

    private void ChooseSprite()
    {
        if ((Input.GetKeyDown(KeyCode.D) || Input.GetKeyDown(KeyCode.RightArrow)) && spriteNumber[bodyPartNumber] < 8) //if right arrow key or d key is pressed and the selected sprite for that body part isn't the last one
        {
            spriteNumber[bodyPartNumber]++; //select the next sprite for that body part

            bodyPartSpriteRenderer[bodyPartNumber].sprite = bodyPartScript[bodyPartNumber].bodyPartSprites[spriteNumber[bodyPartNumber]]; //sets the sprite of the body part object to the correct sprite number in the array
            bodyPartNumberText[bodyPartNumber].text = Convert.ToString(spriteNumber[bodyPartNumber]); //changes the sprite number for the selected body part to the current sprite
        }
        else if ((Input.GetKeyDown(KeyCode.A) || Input.GetKeyDown(KeyCode.LeftArrow)) && spriteNumber[bodyPartNumber] > 0) //if left arrow key or a key is pressed and the selected sprite for that body part isn't the first one
        {
            spriteNumber[bodyPartNumber]--; //select the previous sprite for that body part

            bodyPartSpriteRenderer[bodyPartNumber].sprite = bodyPartScript[bodyPartNumber].bodyPartSprites[spriteNumber[bodyPartNumber]]; //sets the sprite of the body part object to the correct sprite number in the array
            bodyPartNumberText[bodyPartNumber].text = Convert.ToString(spriteNumber[bodyPartNumber]); //changes the sprite number for the selected body part to the current sprite
        }
    }

    private void OutputCode()
    {
        for (int i = 0; i < bodyPartObjects.Length; i++) //for each body part
        { 
            code += Convert.ToString(spriteNumber[i]); //adds each sprite number to the code
        }

        codeOutputText.text = "Code: " + Convert.ToString(code); //outputs code to screen
        Debug.Log(code); //outpus code to debug log

        finalCharacterText.text = "Final Character:"; //displays final character text
        finishedCharacter = true; //sets bool to true

        codeInputField.interactable = false; //disables input field
    }

    private void ChooseRandomSprites()
    {
        for(int i = 0; i < bodyPartObjects.Length; i++) //for each body part
        {
            randomSpriteNumber = UnityEngine.Random.Range(randomSpriteNumberMin, randomSpriteNumberMax); //pick a random number between 0 and 8
            spriteNumber[i] = randomSpriteNumber; //set sprite number for current body part in for loop to the random number

            bodyPartSpriteRenderer[i].sprite = bodyPartScript[i].bodyPartSprites[spriteNumber[i]]; //sets the sprite of the body part object currently in loop to the correct sprite number
            bodyPartNumberText[i].text = Convert.ToString(spriteNumber[i]); //changes the sprite number for the body part currently in loop to the randowm sprite
        }
    }

    public void GetCodeInput() //get input is called by 'On End Edit' function from input field
    {
        codeInput = codeInputField.text; //store the input from the input field in a string variable

        if (codeInput.Length == codeLength) //check if input is correct length
        {
            if (codeInput.All(char.IsDigit) && codeInput.Contains("9") == false) //if the code has only integer numbers from 0 to 8
            {
                errorMessageText.text = ""; //set error message text to empty

                for (int i = 0; i < codeLength; i++)
                {
                    codeInputParts[i] = Convert.ToString(codeInput[i]); //convert each character from code input into a string and store in array

                    spriteNumber[i] = Convert.ToInt32(codeInputParts[i]); //convert each string element in array to int and set it to correct sprite number index

                    bodyPartSpriteRenderer[i].sprite = bodyPartScript[i].bodyPartSprites[spriteNumber[i]]; //sets the sprite of the body part object currently in loop to the correct sprite number
                    bodyPartNumberText[i].text = Convert.ToString(spriteNumber[i]); //changes the sprite number for the body part currently in loop to the randowm sprite
                }
            }
            else
            {
                errorMessageText.text = "Code must only contain integers 0-8"; //set text to error message
            }
        }
        else
        {
            errorMessageText.text = "Enter a valid 6 digit code containing only integers 0-8"; //set text to error message
        }
    }
}