using System.Collections;
using UnityEngine;

public class Vines : MonoBehaviour
{
    [SerializeField]
    float growTime;


    public IEnumerator GrowVine(Transform enemyPosition, float distance)
    {
        //growing bush animation
        CharacterStats stats = enemyPosition.GetComponent<CharacterStats>();
        float timePassed = 0;
        yield return new WaitUntil(() =>
        {
            float progress = timePassed / growTime;
            if (stats == null || enemyPosition == null) return true;
            transform.position = Vector3.Lerp(new Vector3(enemyPosition.position.x, enemyPosition.position.y - distance, enemyPosition.position.z), enemyPosition.position, progress);
            transform.eulerAngles = Vector3.Lerp(new Vector3(transform.eulerAngles.x, 0f, transform.eulerAngles.z), new Vector3(transform.eulerAngles.x, -360f, transform.eulerAngles.z), progress);

            timePassed += Time.deltaTime;
            if (timePassed >= growTime)
            {
                return true;
            }
            return false;
        });
    }
}
