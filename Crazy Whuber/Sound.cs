using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.UI;

public class Sound : MonoBehaviour
{
    //store audio mixer and sliders for changing volume
    [SerializeField]
    AudioMixer audioMixer;
    [SerializeField]
    Slider engineVolume;
    [SerializeField]
    Slider musicVolume;

    public void SetEngineVolume(float volume)
    {
        //set the engine sound volume using slider value
        audioMixer.SetFloat("engineVolume", volume);
    }

    public void SetMusicVolume(float volume)
    {
        //set the music volume using slider value
        audioMixer.SetFloat("musicVolume", volume);
    }

    private void Start()
    {
        //get the value of audio mixer and set slider value when loading new scene
        float mixerVolume;
        audioMixer.GetFloat("engineVolume", out mixerVolume);
        engineVolume.value = mixerVolume;

        audioMixer.GetFloat("musicVolume", out mixerVolume);
        musicVolume.value = mixerVolume;
    }
}
