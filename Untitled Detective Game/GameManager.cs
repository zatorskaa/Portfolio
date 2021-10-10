using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    #region Variables
    public static GameManager instance;

    public List<bool> missionsFinished;
    #endregion

    private void Awake()
    {
        if(instance != null)
        {
            Destroy(gameObject); //make sure there is only one game manager
        }
        else
        {
            instance = this;
            DontDestroyOnLoad(gameObject);
        }
    }


    public void MissionFinished(int missionNumber)
    {
        missionsFinished[missionNumber] = true;
    }

    
}
