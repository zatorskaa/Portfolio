using UnityEngine;
using System.Collections;

public class Regrowth : BaseAbility
{
    [Header("Regrowth")]
    [SerializeField]
    private float areaRadius = 2;
    [SerializeField]
    private float treeGrowTime = 1;

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
            Collider[] treeLogs = Physics.OverlapSphere(hit.point, areaRadius, targetMask);
            if (treeLogs.Length != 0)
            {
                for (int i = 0; i < treeLogs.Length; i++)
                {
                    if (!treeLogs[i].GetComponent<GrowableTree>().IsGrown)
                    {
                        treeLogs[i].GetComponent<GrowableTree>().Grow(treeGrowTime);
                        GrowTree tree = treeLogs[i].GetComponentInChildren<GrowTree>();
                        StartCoroutine(tree.GrowTreeCoroutine(treeGrowTime));
                    }
                }

                // The ability succeeded, and should drain mana / be set on cooldown.
                return true;
            }
        }

        // The ability did not succeed.
        return false;
    }

    //private void OnDrawGizmos()
    //{
    //    Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition); //shoot ray from camera mouse position

    //    if (Physics.Raycast(ray, out RaycastHit hit, Mathf.Infinity, groundMask, QueryTriggerInteraction.Ignore))
    //    {
    //        Gizmos.DrawWireSphere(hit.point, areaRadius);
    //    }
    //}
}
