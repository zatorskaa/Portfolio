using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThirdPersonCamera : MonoBehaviour
{
    #region Variables
    [SerializeField]
    bool lockCursor;

    float yaw; //horizontal movement
    float pitch; //vertical movement
    Vector3 targetRotation;
    [SerializeField]
    Vector2 pitchMinMax; //store min and max values for pitch

    [SerializeField]
    float mouseSensitivity = 10f; //rotation speed
    [SerializeField]
    Transform target; //stores target to rotate around
    [SerializeField]
    float distanceFromTarget; //stores distance camera should be from target

    [SerializeField]
    float rotationSmoothTime = 0.12f;
    Vector3 rotationSmoothVelocity;
    Vector3 currentRotation;

    [SerializeField]
    PlayerMovement player;
    #endregion

    void Start()
    {
        pitch = transform.rotation.eulerAngles.x;
        yaw = player.transform.localRotation.eulerAngles.y;

        if (lockCursor)
        {
            LockCursor();
        }
    }

    void LateUpdate()
    {
        if(player.CheckIfCanMove() == true)
        {
            UnlockCursor();
        }
        else
        {
            MoveCamera();
            LockCursor();
        }
    }

    void MoveCamera()
    {
        //get mouse movement from axis
        yaw += Input.GetAxis("Mouse X") * mouseSensitivity;
        pitch -= Input.GetAxis("Mouse Y") * mouseSensitivity;
        pitch = Mathf.Clamp(pitch, pitchMinMax.x, pitchMinMax.y); //clamp pitch value


        targetRotation = new Vector3(pitch, yaw);
        currentRotation = Vector3.SmoothDamp(currentRotation, targetRotation, ref rotationSmoothVelocity, rotationSmoothTime); //smooth rotation

        transform.eulerAngles = targetRotation; //rotate camera

        transform.position = target.position - transform.forward * distanceFromTarget; //set camera position away from target
        
    }

    void LockCursor()
    {
        //disable and hide cursor
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }

    void UnlockCursor()
    {
        //enable cursor
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;
    }
}
