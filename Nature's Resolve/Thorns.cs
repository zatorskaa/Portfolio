using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Thorns : BaseAbility
{
   [Header("Thorns")]
   [SerializeField]
   private float areaRadius = 2;
   [SerializeField]
   GameObject[] bushPrefab;
    

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

       if (Physics.Raycast(ray, out RaycastHit hit, Mathf.Infinity, groundMask, QueryTriggerInteraction.UseGlobal))
       {
           int bushNumber = Random.Range(0, bushPrefab.Length);

           Instantiate(bushPrefab[bushNumber], new Vector3(hit.point.x, hit.point.y + 0.2f, hit.point.z), Quaternion.identity); //instantiate a random bush prefab

           return true;
       }

       return false;
   }
}
