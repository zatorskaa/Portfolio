using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    #region Variables
    [Header("Movement")]
    [SerializeField]
    float walkSpeed;
    [SerializeField]
    float runSpeed;
    float speed; //store movement speed of player
    CharacterController controller; //store character controller component
    [SerializeField]
    Transform cam; //store transform of camera

    //store axis inputs
    float horizontalInput; 
    float verticalInput;
    bool isRunning;

    Vector3 direction; //store direction player is moving
    Vector3 moveDirection; //store direction based on camera
    float targetAngle; //store angle to rotate player
    float angle; //store angle after smoothing
    float turnSmoothVelocity;
    [SerializeField]
    float turnSmoothTime = 0.1f;

    [HideInInspector]
    public bool isInteracting; //used to check if player is interacting with an object or person
    [HideInInspector]
    public bool menuIsOpen; //used to check if case files menu is open to stop player from moving
    


    [Header("Gravity")]
    [SerializeField]
    float gravity = -9.81f; //store gravity value
    Vector3 velocity; //store vertical velocity of player

    //used to check if player is on ground
    [SerializeField]
    Transform groundCheck;
    [SerializeField]
    float groundDistance;
    [SerializeField]
    LayerMask groundMask;
    bool isGrounded;



    [Header("Jumping")]
    [SerializeField]
    float jumpHeight; //stores height to jump



    [Header("Climbing")]
    [SerializeField]
    Transform mainClimbingPointCheck;
    [SerializeField]
    Transform leftClimbingPointCheck;
    [SerializeField]
    Transform rightClimbingPointCheck;
    [SerializeField]
    Transform topClimbingPointCheck;
    [SerializeField]
    Transform bottomClimbingPointCheck;
    [SerializeField]
    Transform leftBuildingClimbingPointCheck;
    [SerializeField]
    Transform rightBuildingClimbingPointCheck;
    [SerializeField]
    Transform leftCornerClimbingPointCheck;
    [SerializeField]
    Transform rightCornerClimbingPointCheck;
    [SerializeField]
    Transform leftInsideCornerClimbingPointCheck;
    [SerializeField]
    Transform rightInsideCornerClimbingPointCheck;

    [SerializeField]
    float pointCheckHeightDifference;
    [SerializeField]
    float verticalPointDistance;
    [SerializeField]
    float horizontalPointDistance;
    [SerializeField]
    float cornerPointDistance;
    [SerializeField]
    float buildingPointDistance;
    [SerializeField]
    LayerMask pointMask;
    bool isClimbing;

    [SerializeField]
    LayerMask buildingMask;
    bool isNearBuilding;

    [SerializeField]
    float climbingSpeed;
    Vector3 playerClimbPosition;
    Quaternion playerClimbRotation;
    //float yClimbPosition;
    //float xClimbPosition;
    //float zClimbPosition;
    //float yClimbVelocity;
    //float xClimbVelocity;
    //float zClimbVelocity;
    //[SerializeField]
    //float climbSmoothTime = 0.1f;

    Collider[] closestPoint;
    Collider[] leftPoint;
    Collider[] rightPoint;
    Collider[] topPoint;
    Collider[] bottomPoint;
    Collider[] leftCornerPoint;
    Collider[] rightCornerPoint;
    Collider[] leftInsideCornerPoint;
    Collider[] rightInsideCornerPoint;
    Collider[] leftBuildingPoint;
    Collider[] rightBuildingPoint;



    [Header("Animation")]
    //stores values for switching animations
    [SerializeField]
    float walkAnimationSpeed;
    [SerializeField]
    float runAnimationSpeed;
    Animator animator;
    #endregion

    void Start()
    {
        controller = GetComponent<CharacterController>(); //store character controller of player
        animator = GetComponentInChildren<Animator>(); //store animator of character

        isClimbing = false;
        isInteracting = false;
        menuIsOpen = false;
    }

    void Update()
    {
        if (!menuIsOpen) //if case files menu is not open
        {
            if (!isInteracting) //if player is not interacting with any objects
            {
                if (Input.GetKeyDown(KeyCode.G))
                {
                    isClimbing = !isClimbing;
                }

                if ((closestPoint == null || closestPoint.Length == 0) && isGrounded) //check if array is not empty
                {
                    isClimbing = false;
                }

                if ((topPoint == null || topPoint.Length == 0) && (!isGrounded || !isNearBuilding) && !(Input.GetKey(KeyCode.Q) || Input.GetKey(KeyCode.E) || Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D)))
                {
                    isClimbing = false;
                }

                if ((topPoint == null || topPoint.Length == 0) && isGrounded)
                {
                    isClimbing = false;
                }

                if (isClimbing && (isNearBuilding || Input.GetKey(KeyCode.Q) || Input.GetKey(KeyCode.E)))
                {
                    Climbing();
                }
                else
                {
                    Jump();
                    Movement();
                    Gravity();
                }

                Animation();
            }
        }
    }

    private void FixedUpdate()
    {
        GroundCheck();
        ClimbingPointCheck();
    }



    void GroundCheck()
    {
        isGrounded = Physics.CheckSphere(groundCheck.position, groundDistance, groundMask); //check if player is on ground
    }


    void Movement()
    {
        //get input from axis
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");

        direction = new Vector3(horizontalInput, 0f, verticalInput).normalized; //store direction of movement based on axis inputs


        if (Input.GetKey(KeyCode.LeftShift)) //check if player is holding down shift button
        {
            speed = runSpeed; //set speed to run speed
            isRunning = true;
        }
        else
        {
            speed = walkSpeed; //set speed to walk speed
            isRunning = false;
        }


        if(direction.magnitude >= 0.1f)
        {
            if(direction.z < 0f && direction.x == 0f)
            {
                //stops player from turning when moving backwards
                targetAngle = Mathf.Atan2(direction.x, direction.z) * Mathf.Rad2Deg + cam.eulerAngles.y; //calculate angle to rotate character in degrees
                angle = Mathf.SmoothDampAngle(transform.eulerAngles.y, targetAngle + 180, ref turnSmoothVelocity, turnSmoothTime); //make rotation smooth
                transform.rotation = Quaternion.Euler(0f, angle, 0f); //rotate character

                moveDirection = Quaternion.Euler(0f, targetAngle, 0f) * Vector3.forward; //make player move in direction that the camera is facing
                controller.Move(speed * Time.deltaTime * moveDirection.normalized); //move character controller
            }
            else 
            {
                targetAngle = Mathf.Atan2(direction.x, direction.z) * Mathf.Rad2Deg + cam.eulerAngles.y; //calculate angle to rotate character in degrees
                angle = Mathf.SmoothDampAngle(transform.eulerAngles.y, targetAngle, ref turnSmoothVelocity, turnSmoothTime); //make rotation smooth
                transform.rotation = Quaternion.Euler(0f, angle, 0f); //rotate character

                moveDirection = Quaternion.Euler(0f, targetAngle, 0f) * Vector3.forward; //make player move in direction that the camera is facing
                controller.Move(speed * Time.deltaTime * moveDirection.normalized); //move character controller
            }
        }
    }

    void Gravity()
    {
        if (isGrounded && velocity.y < 0)
        {
            velocity.y = -2f; //reset velocity if player is on ground
        }

        //add gravity to player
        velocity.y += gravity * Time.deltaTime;
        controller.Move(velocity * Time.deltaTime);
    }

    void Jump()
    {
        if (Input.GetButtonDown("Jump") && isGrounded) //check if player is on ground and jump buttton is pressed
        {
            velocity.y = Mathf.Sqrt(jumpHeight * -2f * gravity); //move player up (jump)
        }
    }

    void Animation()
    {
        if(!isClimbing && !isGrounded) 
        {
            animator.SetBool("isJumping", true);
            animator.SetBool("isClimbing", false);
        }
        else if(isClimbing)
        {
            animator.SetBool("isJumping", false);
            animator.SetBool("isClimbing", true);
        }
        else if(direction.magnitude == 0)
        {
            animator.SetBool("isClimbing", false);
            animator.SetBool("isJumping", false);
            animator.SetFloat("speedPercent", 0f); //play idle animation
        }
        else if(isRunning)
        {
            animator.SetBool("isClimbing", false);
            animator.SetBool("isJumping", false);
            animator.SetFloat("speedPercent", runAnimationSpeed); //play run animation
        }
        else
        {
            animator.SetBool("isClimbing", false);
            animator.SetBool("isJumping", false);
            animator.SetFloat("speedPercent", walkAnimationSpeed); //play walk animation
        }
    }


    void ClimbingPointCheck()
    {
        closestPoint = Physics.OverlapCapsule(mainClimbingPointCheck.position, new Vector3(mainClimbingPointCheck.position.x, mainClimbingPointCheck.position.y + pointCheckHeightDifference, mainClimbingPointCheck.position.z), verticalPointDistance, pointMask); //get the position of the closest climbing point
        isNearBuilding = Physics.CheckSphere(bottomClimbingPointCheck.position, verticalPointDistance, buildingMask); //check if player is next to a building


        //if(!isNearBuilding)
        //{
        //    if (Input.GetKey(KeyCode.Space))
        //    {
        //        isClimbing = false;
        //    }
        //    else if ((Input.GetKey(KeyCode.Q) || Input.GetKey(KeyCode.E) || Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D)) && !isGrounded)
        //    {
        //        isClimbing = true;
        //    }
        //    else if (!Input.GetKey(KeyCode.Q) || !Input.GetKey(KeyCode.E))
        //    {
        //        isClimbing = false;
        //    }
        //}


        //get positions of points around current point
        leftPoint = Physics.OverlapCapsule(leftClimbingPointCheck.position, new Vector3(leftClimbingPointCheck.position.x, leftClimbingPointCheck.position.y + pointCheckHeightDifference, leftClimbingPointCheck.position.z), horizontalPointDistance, pointMask);
        rightPoint = Physics.OverlapCapsule(rightClimbingPointCheck.position, new Vector3(rightClimbingPointCheck.position.x, rightClimbingPointCheck.position.y + pointCheckHeightDifference, rightClimbingPointCheck.position.z), horizontalPointDistance, pointMask);
        topPoint = Physics.OverlapCapsule(topClimbingPointCheck.position, new Vector3(topClimbingPointCheck.position.x, topClimbingPointCheck.position.y + pointCheckHeightDifference, topClimbingPointCheck.position.z), verticalPointDistance, pointMask);
        bottomPoint = Physics.OverlapCapsule(bottomClimbingPointCheck.position, new Vector3(bottomClimbingPointCheck.position.x, bottomClimbingPointCheck.position.y - pointCheckHeightDifference, bottomClimbingPointCheck.position.z), verticalPointDistance, pointMask);

        leftCornerPoint = Physics.OverlapCapsule(leftCornerClimbingPointCheck.position, new Vector3(leftCornerClimbingPointCheck.position.x, leftCornerClimbingPointCheck.position.y + pointCheckHeightDifference, leftCornerClimbingPointCheck.position.z), cornerPointDistance, pointMask);
        rightCornerPoint = Physics.OverlapCapsule(rightCornerClimbingPointCheck.position, new Vector3(rightCornerClimbingPointCheck.position.x, rightCornerClimbingPointCheck.position.y + pointCheckHeightDifference, rightCornerClimbingPointCheck.position.z), cornerPointDistance, pointMask);

        leftInsideCornerPoint = Physics.OverlapCapsule(leftInsideCornerClimbingPointCheck.position, new Vector3(leftInsideCornerClimbingPointCheck.position.x, leftInsideCornerClimbingPointCheck.position.y + pointCheckHeightDifference, leftInsideCornerClimbingPointCheck.position.z), cornerPointDistance, pointMask);
        rightInsideCornerPoint = Physics.OverlapCapsule(rightInsideCornerClimbingPointCheck.position, new Vector3(rightInsideCornerClimbingPointCheck.position.x, rightInsideCornerClimbingPointCheck.position.y + pointCheckHeightDifference, rightInsideCornerClimbingPointCheck.position.z), cornerPointDistance, pointMask);

        leftBuildingPoint = Physics.OverlapCapsule(leftBuildingClimbingPointCheck.position, new Vector3(leftBuildingClimbingPointCheck.position.x, leftBuildingClimbingPointCheck.position.y + pointCheckHeightDifference, leftBuildingClimbingPointCheck.position.z), buildingPointDistance, pointMask);
        rightBuildingPoint = Physics.OverlapCapsule(rightBuildingClimbingPointCheck.position, new Vector3(rightBuildingClimbingPointCheck.position.x, rightBuildingClimbingPointCheck.position.y + pointCheckHeightDifference, rightBuildingClimbingPointCheck.position.z), buildingPointDistance, pointMask);
    }


    void Climbing()
    {
        //get input from axis
        horizontalInput = Input.GetAxis("Horizontal");
        verticalInput = Input.GetAxis("Vertical");


        if(Input.GetKeyDown(KeyCode.A) || Input.GetKeyDown(KeyCode.LeftArrow)) //check for left input
        {
            if (leftCornerPoint != null && leftCornerPoint.Length != 0)
            {
                playerClimbPosition = leftCornerPoint[0].transform.GetChild(0).transform.position; //set position to left corner point
                playerClimbRotation = leftCornerPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
            else if (leftPoint != null && leftPoint.Length != 0) //check if left point exists
            {
                playerClimbPosition = leftPoint[0].transform.GetChild(0).transform.position; //set position to left point
                playerClimbRotation = leftPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
            else if (leftInsideCornerPoint != null && leftInsideCornerPoint.Length != 0)
            {
                playerClimbPosition = leftInsideCornerPoint[0].transform.GetChild(0).transform.position; //set position to left corner point
                playerClimbRotation = leftInsideCornerPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
        }
        else if(Input.GetKeyDown(KeyCode.D) || Input.GetKeyDown(KeyCode.RightArrow)) //check for right input
        {
            if (rightCornerPoint != null && rightCornerPoint.Length != 0)
            {
                playerClimbPosition = rightCornerPoint[0].transform.GetChild(0).transform.position; //set position to right corner point
                playerClimbRotation = rightCornerPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
            else if (rightPoint != null && rightPoint.Length != 0) //check if right point exists
            {
                playerClimbPosition = rightPoint[0].transform.GetChild(0).transform.position; //set position to right point
                playerClimbRotation = rightPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
            else if (rightInsideCornerPoint != null && rightInsideCornerPoint.Length != 0)
            {
                playerClimbPosition = rightInsideCornerPoint[0].transform.GetChild(0).transform.position; //set position to right corner point
                playerClimbRotation = rightInsideCornerPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
        }
        else if(Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.UpArrow)) //check for up input
        {
            if (topPoint != null && topPoint.Length != 0) //check if top point exists
            {
                playerClimbPosition = topPoint[0].transform.GetChild(0).transform.position; //set position to top point
                playerClimbRotation = topPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
        }
        else if (Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.DownArrow)) //check for down input
        {
            if (bottomPoint != null && bottomPoint.Length != 0) //check if bottom point exists
            {
                playerClimbPosition = bottomPoint[0].transform.GetChild(0).transform.position; //set position to bottom point
                playerClimbRotation = bottomPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
        }
        else if(Input.GetKeyDown(KeyCode.Q))
        {
            if(leftBuildingPoint != null && leftBuildingPoint.Length != 0)
            {
                playerClimbPosition = leftBuildingPoint[0].transform.GetChild(0).transform.position; //set position to left point on next building
                playerClimbRotation = leftBuildingPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
        }
        else if(Input.GetKeyDown(KeyCode.E))
        {
            if (rightBuildingPoint != null && rightBuildingPoint.Length != 0)
            {
                playerClimbPosition = rightBuildingPoint[0].transform.GetChild(0).transform.position; //set position to right point on next building
                playerClimbRotation = rightBuildingPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
        }
        else if(horizontalInput == 0 && verticalInput == 0 && controller.velocity.y == 0 && controller.velocity.x == 0 && !Input.GetKey(KeyCode.Q) && !Input.GetKey(KeyCode.E))
        {
            if (closestPoint != null && closestPoint.Length != 0) //check if closest point exists
            {
                playerClimbPosition = closestPoint[0].transform.GetChild(0).transform.position; //set position to closest point
                playerClimbRotation = closestPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
        }
        else if ((!(horizontalInput == 0) || !(verticalInput == 0) || Input.GetKey(KeyCode.Space)) && Input.GetKey(KeyCode.G))
        {
            if (closestPoint != null && closestPoint.Length != 0) //check if closest point exists
            {
                playerClimbPosition = closestPoint[0].transform.GetChild(0).transform.position; //set position to closest point
                playerClimbRotation = closestPoint[0].transform.GetChild(0).transform.rotation; //set rotation to match climbing point
            }
        }
        else if (Input.GetKey(KeyCode.Space) || Input.GetKeyDown(KeyCode.G) || Input.GetKey(KeyCode.G))
        {
            playerClimbPosition = transform.position;
            playerClimbRotation = transform.rotation;
        }



        transform.rotation = playerClimbRotation;
        //yClimbPosition = Mathf.SmoothDamp(transform.position.y, playerClimbPosition.y, ref yClimbVelocity, climbSmoothTime); //smooth climbing up and down
        ////transform.position = new Vector3(playerClimbPosition.x, yClimbPosition, playerClimbPosition.z); //set player position to point

        //xClimbPosition = Mathf.SmoothDamp(transform.position.x, playerClimbPosition.x, ref xClimbVelocity, climbSmoothTime); //smooth climbing left and right
        //zClimbPosition = Mathf.SmoothDamp(transform.position.z, playerClimbPosition.z, ref zClimbVelocity, climbSmoothTime); //smooth climbing left and right
        //transform.position = new Vector3(xClimbPosition, yClimbPosition, zClimbPosition); //set player position to point


        transform.position = Vector3.MoveTowards(transform.position, playerClimbPosition, Time.deltaTime * climbingSpeed);

    }



    private void OnDrawGizmos()
    {
        Gizmos.color = Color.blue;
        Gizmos.DrawWireSphere(groundCheck.position, groundDistance);
        Gizmos.color = Color.white;
        Gizmos.DrawWireSphere(mainClimbingPointCheck.position, verticalPointDistance);
        Gizmos.DrawWireSphere(new Vector3(mainClimbingPointCheck.position.x, mainClimbingPointCheck.position.y + pointCheckHeightDifference, mainClimbingPointCheck.position.z), verticalPointDistance);
        Gizmos.DrawWireSphere(bottomClimbingPointCheck.position, verticalPointDistance);
        Gizmos.DrawWireSphere(topClimbingPointCheck.position, verticalPointDistance);

        Gizmos.DrawWireSphere(leftClimbingPointCheck.position, horizontalPointDistance);
        Gizmos.DrawWireSphere(leftCornerClimbingPointCheck.position, cornerPointDistance);
        Gizmos.DrawWireSphere(leftInsideCornerClimbingPointCheck.position, cornerPointDistance);
        Gizmos.DrawWireSphere(leftBuildingClimbingPointCheck.position, buildingPointDistance);
    }


    public bool CheckIfCanMove() //function called by camera script to check if player can move
    {
        if(isInteracting || menuIsOpen)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
