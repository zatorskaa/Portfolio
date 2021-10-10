using System;
using UnityEngine;
using UnityEngine.AI;

[RequireComponent(typeof(NavMeshAgent))]
public class PlayerController : MonoBehaviour
{
    private NavMeshAgent agent;

    private CharacterStats stats = null;

    private void Awake()
    {
        agent = GetComponent<NavMeshAgent>();
        stats = GetComponent<CharacterStats>();
    }

    private void OnEnable() 
    {
        if(stats != null)
        {
            stats.OnTargetDeath += OnDeath;
        }
    }
    private void OnDisable()
    {
        if(stats != null)
        {
            stats.OnTargetDeath -= OnDeath;
        }
    }

    void Update()
    {
        if(Input.GetMouseButton(1))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition); //shoot ray from camera mouse position

            RaycastHit hit;

            if(Physics.Raycast(ray, out hit)) //if ray hits an object
            {
                agent.SetDestination(hit.point); //move character
            }
        }
    }

    private void OnDeath(object sender, EventArgs e)
    {
        agent.isStopped = true;
        Destroy(this, Time.deltaTime);
    }
}
