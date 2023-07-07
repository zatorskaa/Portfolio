using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    public static GameObject instance;

    void Awake()
    {
        if(instance == null)
        {
            instance = this.gameObject;

            //don't destroy audio when loading next scene
            DontDestroyOnLoad(this.gameObject);
        }
        else if(instance != null)
        {
            Destroy(this.gameObject);
        }
    }
}
