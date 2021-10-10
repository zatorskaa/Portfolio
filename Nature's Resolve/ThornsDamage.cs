using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThornsDamage : MonoBehaviour
{
    [SerializeField]
    float damageValue;

    [SerializeField]
    float destroyTime;
    [SerializeField]
    float growTime;

    MeshRenderer meshRenderer;


    void Start() 
    {
        meshRenderer = GetComponent<MeshRenderer>();

        StartCoroutine(GrowBush(growTime));

        StartCoroutine(DestroyBush());
    }

    IEnumerator GrowBush(float time)
    {
        //growing bush animation
        float timePassed = 0;

        Color colorStart = new Color(meshRenderer.material.color.r, meshRenderer.material.color.g, meshRenderer.material.color.b, 0f);
        Color colorEnd = new Color(meshRenderer.material.color.r, meshRenderer.material.color.g, meshRenderer.material.color.b, 1f);

        yield return new WaitUntil(() =>
        {
            float progress = timePassed / time;
            transform.localScale = Vector3.Lerp(Vector3.zero, Vector3.one, progress);
            meshRenderer.material.color = Color.Lerp(colorStart, colorEnd, progress);

            timePassed += Time.deltaTime;
            if (timePassed >= time)
            {
                return true;
            }
            return false;
        });
    }

    IEnumerator DestroyBush()
    {
        yield return new WaitForSeconds(destroyTime);

        Destroy(gameObject); //destroy bush after time
    }

    private void OnTriggerStay(Collider collider) 
    {
        CharacterStats characterStats = collider.GetComponent<CharacterStats>();

        if(characterStats != null)
        {
            characterStats.ChangeHealth(-damageValue); //decrease character health
        }
    }
}
