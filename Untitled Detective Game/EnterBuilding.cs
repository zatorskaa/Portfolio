using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EnterBuilding : MonoBehaviour
{
    #region Variables
    [SerializeField]
    int sceneBuildIndex; //store build index number of scene to load

    bool playerIsNear; //check if player is near door
    [SerializeField]
    Vector3 boxDimensions; //dimensions of box around door to check for player
    [SerializeField]
    LayerMask playerLayerMask;

    [SerializeField]
    int missionNumber;
    #endregion


    private void Start()
    {
        if (GameManager.instance.missionsFinished[missionNumber])
        {
            gameObject.SetActive(false);
        }
    }

    private void FixedUpdate()
    {
        playerIsNear = Physics.CheckBox(transform.position, boxDimensions, transform.rotation, playerLayerMask); //check if player is near building door
    }

    private void Update()
    {
        if (playerIsNear)
        {
            if (Input.GetKeyDown(KeyCode.O))
            {
                SceneManager.LoadScene(sceneBuildIndex); //load scene when o pressed
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
