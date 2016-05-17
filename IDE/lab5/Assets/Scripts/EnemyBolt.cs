using UnityEngine;
using System.Collections;

public class EnemyBolt : MonoBehaviour
{
    public GameObject explosion;
    private GameController gameController;

    void Start()
    {
        gameController = GameObject.FindWithTag("GameController").GetComponent<GameController>();
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            Instantiate(explosion, other.transform.position, other.transform.rotation);
            gameController.GameOver();
            Destroy(other.gameObject);
            Destroy(gameObject);
        }
    }
}
