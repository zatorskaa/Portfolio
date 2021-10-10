using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterMovement : MonoBehaviour
{
    #region Variables
    private Vector2 moveInput;
    [SerializeField]
    private float speed;
    private bool isFacingRight;
    private Rigidbody2D rb;

    [SerializeField]
    private CharacterAbility[] characters;

    [SerializeField]
    private Transform[] characterPositions;
    #endregion

    void Start()
    {
        isFacingRight = true; //initialize to true
        rb = GetComponent<Rigidbody2D>(); //get rigidbody of game object

        characters[0].isSelected = true;
        characters[1].isSelected = false;
        characters[2].isSelected = false;
    }

    void FixedUpdate()
    {
        Move();
    }

    private void Update()
    {
        SelectCharacter();
    }

    void Move()
    {
        moveInput = new Vector2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical")); //get input from WASD or arrow keys

        rb.velocity = moveInput * speed; //set velocity to the input multiplied by speed

        if(isFacingRight == false && moveInput.x > 0) //if character is facing left and player moves to right, flip the characters
        {
            Flip();
        }
        else if(isFacingRight == true && moveInput.x < 0) //if character is facing right and player moves to left, flip the characters
        {
            Flip();
        }
    }

    void Flip()
    {
        isFacingRight = !isFacingRight;

        Vector3 scaler = transform.localScale;
        scaler.x *= -1; //multiplies scale by -1 on x axis to flip characters
        transform.localScale = scaler;
    }

    void SelectCharacter()
    {
        if(Input.GetKeyDown(KeyCode.Alpha1) || Input.GetKeyDown(KeyCode.Keypad1))
        {
            //set first character to selected and others to not selected
            characters[0].isSelected = true;
            characters[1].isSelected = false;
            characters[2].isSelected = false;

            //set first character to front position
            characters[0].transform.position = characterPositions[0].transform.position;
            characters[1].transform.position = characterPositions[1].transform.position;
            characters[2].transform.position = characterPositions[2].transform.position;
        }
        else if(Input.GetKeyDown(KeyCode.Alpha2) || Input.GetKeyDown(KeyCode.Keypad2))
        {
            //set second character to selected and others to not selected
            characters[0].isSelected = false;
            characters[1].isSelected = true;
            characters[2].isSelected = false;

            //set second character to front position
            characters[0].transform.position = characterPositions[1].transform.position;
            characters[1].transform.position = characterPositions[0].transform.position;
            characters[2].transform.position = characterPositions[2].transform.position;
        }
        else if (Input.GetKeyDown(KeyCode.Alpha3) || Input.GetKeyDown(KeyCode.Keypad3))
        {
            //set third character to selected and others to not selected
            characters[0].isSelected = false;
            characters[1].isSelected = false;
            characters[2].isSelected = true;

            //set third character to front position
            characters[0].transform.position = characterPositions[2].transform.position;
            characters[1].transform.position = characterPositions[1].transform.position;
            characters[2].transform.position = characterPositions[0].transform.position;
        }
    }
}
