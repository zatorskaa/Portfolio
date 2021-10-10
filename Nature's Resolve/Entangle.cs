using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Entangle : BaseAbility
{
    [Header("Entangle")]
    [SerializeField]
    private float areaRadius = 2;
    [SerializeField]
    float enemyStopTime;

    [SerializeField]
    float damageValue;
    [SerializeField]
    GameObject[] vinePrefab;
    [SerializeField]
    float[] vineDistanceBelowGround;

    AIController aiController;
    CharacterStats characterStats;

    protected override AbilityCastRequestArgs GetAbilityCastRequestArgs()
    {
        return new AbilityCastRequestArgs
        {
            ability = this,
            area = true,
            areaRadius = areaRadius
        };
    }

    protected override bool TryUseAbility()
    {
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition); //shoot ray from camera mouse position

        if (Physics.Raycast(ray, out RaycastHit hit, Mathf.Infinity, groundMask, QueryTriggerInteraction.Ignore))
        {
            Collider[] enemies = Physics.OverlapSphere(hit.point, areaRadius, targetMask);
            if (enemies.Length != 0)
            {

                    characterStats = enemies[0].GetComponent<CharacterStats>();
                    aiController = enemies[0].GetComponent<AIController>();

                    if(aiController != null)
                    {
                        StartCoroutine(StopEnemy(enemies[0].gameObject.GetComponent<NavMeshAgent>()));
                    }
                    
                    return true;
            }
        }

        return false;
    }

    IEnumerator StopEnemy(NavMeshAgent enemyNavMesh)
    {
        //stop the machine for certain time and then let it move again
        aiController.SetRooted(true);
        enemyNavMesh.velocity = Vector3.zero;
        enemyNavMesh.isStopped = true;


        GameObject vine;

        if (aiController.enemyType == "machine")
        {
            vine = Instantiate(vinePrefab[0], new Vector3(aiController.transform.position.x, aiController.transform.position.y - vineDistanceBelowGround[0], aiController.transform.position.z), Quaternion.identity);
            Vines vineScript = vine.GetComponent<Vines>();
            StartCoroutine(vineScript.GrowVine(aiController.transform, vineDistanceBelowGround[0]));
        }
        else
        {
            vine = Instantiate(vinePrefab[1], new Vector3(aiController.transform.position.x, aiController.transform.position.y - vineDistanceBelowGround[1], aiController.transform.position.z), Quaternion.identity);
            Vines vineScript = vine.GetComponent<Vines>();
            StartCoroutine(vineScript.GrowVine(aiController.transform, vineDistanceBelowGround[1]));
        }


        float timePassed = 0;
        yield return new WaitUntil(() =>
        {
            float progress = timePassed / enemyStopTime;
            characterStats.ChangeHealth(-damageValue * Time.deltaTime / enemyStopTime); //decrease character health

            if (characterStats.currentHealth == 0)
            {
                return true;
            }

            timePassed += Time.deltaTime;
            if (timePassed >= enemyStopTime)
            {
                return true;
            }
            return false;
        });

        if (aiController != null)
        {
            aiController.SetRooted(false);
            enemyNavMesh.isStopped = false;
        }

        Destroy(vine);
    }
}
