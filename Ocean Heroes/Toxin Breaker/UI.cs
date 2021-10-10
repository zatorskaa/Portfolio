using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI : MonoBehaviour
{
    #region
    [SerializeField]
    private GameObject livesPrefab;
    private Transform[] livesUI;

    [SerializeField]
    private Text numberOfPoints;
    #endregion

    private void Start()
    {
        for(int i = 0; i < BlockBreakerGameManager.lives; i++)
        {
            Instantiate(livesPrefab, transform); //add lives to the ui
        }

        for(int i = 0; i < transform.childCount; i++)
        {
            livesUI = GetComponentsInChildren<Transform>(); //store the lives ui
        }

        SetPoints(0);
    }

    public void DecreaseLives()
    {
        Destroy(livesUI[transform.childCount - 1].gameObject); //destroy lives ui when lives decrease
    }

    public void SetPoints(int points)
    {
        numberOfPoints.text = points.ToString(); //set number of points in ui
    }
}
