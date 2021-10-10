using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CharacterChase : MonoBehaviour
{
    #region Variables
    //CharacterController controller;
    Animator animator;

    [Header("Movement")]
    [SerializeField]
    Transform[] waypoints; //store waypoints
    int nextWaypoint; //store which waypoint to move to next
    [SerializeField]
    int resetWaypointNumber;
    [SerializeField]
    float waypointDistance;


    Vector3 direction; //store distance between character and next waypoint
    float targetAngle; //store angle to rotate character

    [SerializeField]
    float runningSpeed;
    [SerializeField]
    float climbingSpeed;
    float speed; //store speed of character


    [Header("Gravity")]
    //used to check if character is on ground
    [SerializeField]
    Transform groundCheck;
    [SerializeField]
    float groundDistance;
    [SerializeField]
    LayerMask groundMask;
    bool isGrounded;

    //used to check if character is near building
    [SerializeField]
    LayerMask buildingMask;
    bool isNearBuilding;



    [Header("Player Chase")]
    //used to check if player is near character
    [SerializeField]
    Transform playerCheck;
    [SerializeField]
    float playerDistance;
    [SerializeField]
    LayerMask playerMask;
    bool isNearPlayer;

    [SerializeField]
    GameObject catchIcon;
    [SerializeField]
    GameObject criminalArrestedUI;
    [SerializeField]
    GameObject catchCriminalUI;
    bool isCaught;

    [SerializeField]
    PlayerMovement player;


    [SerializeField]
    int sceneToLoadBuildIndex;
    [SerializeField]
    bool missionFinished;
    [SerializeField]
    int missionNumber;
    #endregion


    private void Start()
    {
        //store controller and animator components of character
        //controller = GetComponent<CharacterController>();
        animator = GetComponentInChildren<Animator>();

        nextWaypoint = 0; //initialize target waypoint to 0
        transform.position = new Vector3(waypoints[nextWaypoint].position.x, waypoints[nextWaypoint].position.y, waypoints[nextWaypoint].position.z); //move character to first waypoint

        isCaught = false;
        catchIcon.SetActive(false);
        criminalArrestedUI.SetActive(false);

        StartCoroutine(CatchCriminalUI());
    }


    private void Update()
    {
        if (!isCaught)
        {
            ChangeWaypoint();
            Movement();

            Animation();
        }

        CatchCharacter();
    }

    private void FixedUpdate()
    {
        GroundCheck();
        BuildingCheck();

        PlayerCheck();
    }

    void Movement()
    {
        direction = (waypoints[nextWaypoint].position - transform.position).normalized; //calculate distance between character and next waypoint
        targetAngle = Mathf.Atan2(direction.x, direction.z) * Mathf.Rad2Deg; //calculate angle to rotate character in degrees
        transform.rotation = Quaternion.Euler(0f, targetAngle, 0f); //rotate character

        //set speed depending on whether the character is climbing or running
        if(!isGrounded && isNearBuilding)
        {
            speed = climbingSpeed;
        }
        else
        {
            speed = runningSpeed;
        }

        transform.position = Vector3.MoveTowards(transform.position, waypoints[nextWaypoint].transform.position, Time.deltaTime * speed);

        //controller.Move(direction.normalized * speed * Time.deltaTime); //move character
    }

    void ChangeWaypoint()
    {
        if(Vector3.Distance(transform.position, waypoints[nextWaypoint].position) <= waypointDistance)
        {
            if (nextWaypoint == waypoints.Length - 1)
            {
                nextWaypoint = resetWaypointNumber; //if character is at last waypoint, resest waypoint to 0
            }
            else
            {
                nextWaypoint++; //increase waypoint by 1
            }
        }
    }

    void GroundCheck()
    {
        isGrounded = Physics.CheckSphere(groundCheck.position, groundDistance, groundMask); //check if character is on ground
    }

    void BuildingCheck()
    {
        isNearBuilding = Physics.CheckSphere(groundCheck.position, groundDistance, buildingMask); //check if character is near building
    }

    //private void OnTriggerEnter(Collider collider)
    //{
    //    if (collider.CompareTag("Waypoint"))
    //    {
    //        ChangeWaypoint();
    //    }
    //}


    void PlayerCheck()
    {
        isNearPlayer = Physics.CheckSphere(playerCheck.position, playerDistance, playerMask); //check if player is near character
    }

    void CatchCharacter()
    {
        if (isNearPlayer) //check if player is near character
        {
            catchIcon.SetActive(true); //show catch icon

            if (Input.GetKeyDown(KeyCode.Mouse0)) //if LMB is pressed
            {
                //show UI and load next scene
                player.menuIsOpen = true;
                isCaught = true;

                criminalArrestedUI.SetActive(true);

                StartCoroutine(CriminalArrested());
            }
        }
        else
        {
            catchIcon.SetActive(false); //hide catch icon
        }
    }

    IEnumerator CriminalArrested()
    {
        if (missionFinished)
        {
            //set mission to finished in game manager
            GameManager.instance.MissionFinished(missionNumber);
        }

        //if criminal is arrested go back to main game area
        yield return new WaitForSeconds(3f);

        SceneManager.LoadScene(sceneToLoadBuildIndex);
    }

    IEnumerator CatchCriminalUI()
    {
        catchCriminalUI.SetActive(true);

        yield return new WaitForSeconds(3f);

        catchCriminalUI.SetActive(false);
    }


    void Animation()
    {
        if(!isGrounded && !isNearBuilding)
        {
            //if character is not on ground and not near building play jump animation
            animator.SetBool("isJumping", true);
            animator.SetBool("isClimbing", false);
        }
        else if(!isGrounded && isNearBuilding)
        {
            //if character is not on ground and near building play climb animation
            animator.SetBool("isJumping", false);
            animator.SetBool("isClimbing", true);
        }
        else
        {
            //play run animation
            animator.SetBool("isClimbing", false);
            animator.SetBool("isJumping", false);
        }
    }


    private void OnDrawGizmos()
    {
        Gizmos.color = Color.blue;
        Gizmos.DrawWireSphere(groundCheck.position, groundDistance);
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(playerCheck.position, playerDistance);
    }
}
