using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ControlsMenuButton : MonoBehaviour
{
    Toggle dialogueButton;
    [SerializeField]
    GameObject questionText;
    [SerializeField]
    GameObject answerText;

    private void Start()
    {
        dialogueButton = GetComponent<Toggle>();
    }

    public void ChangeDialogueButton() //change the example dialogue button text in the controls screen
    {
        if (!dialogueButton.isOn)
        {
            answerText.SetActive(false);
            questionText.SetActive(true);
        }
        else
        {
            questionText.SetActive(false);
            answerText.SetActive(true);
        }
    }
}
