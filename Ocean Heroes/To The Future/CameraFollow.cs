using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    #region Variables
    [SerializeField]
    private Transform playerPosition;
    [SerializeField]
    private Vector3 offset;

    private Vector3 clampedPlayerPosition;

    [SerializeField]
    private float minYValue;
    [SerializeField]
    private float maxYValue;
    [SerializeField]
    private float minXValue;
    [SerializeField]
    private float maxXValue;
    #endregion

    private void LateUpdate()
    {
        clampedPlayerPosition.x = Mathf.Clamp(playerPosition.position.x, minXValue, maxXValue); //make sure camera can't move past min and max x values
        clampedPlayerPosition.y = Mathf.Clamp(playerPosition.position.y, minYValue, maxYValue); //make sure camera can't move past min and max y values
        transform.position = clampedPlayerPosition + offset; //move camera to player position
    }
}
