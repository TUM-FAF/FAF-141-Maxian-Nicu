using UnityEngine;
using System.Collections;

public class RandomShooter : MonoBehaviour
{
    public GameObject Bolt;
    public Transform SpawnTransform;
    public float SpawnInterval;

    void Start()
    {
        StartCoroutine(BoltSpanwer());
    }

    IEnumerator BoltSpanwer()
    {
        while (true)
        {
            Shoot();
            yield return new WaitForSeconds(SpawnInterval);
        }
    }

    private void Shoot()
    {
        Instantiate(Bolt, SpawnTransform.position, SpawnTransform.rotation);
        GetComponent<AudioSource>().Play();
    }
}
