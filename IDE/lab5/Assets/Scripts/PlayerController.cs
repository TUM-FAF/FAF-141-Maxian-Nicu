using UnityEngine;
using System.Collections;

public class PlayerController : MonoBehaviour
{
    public float Speed;
    public float Tilt;
    public Boundaries Boundaries;

    public float FireRate;
    public Transform BoltSpawn;
    public GameObject Bolt;

    private float _nextFire;

    void Update()
    {
        if (Input.GetButton("Fire1") && Time.time > _nextFire)
        {
            _nextFire = Time.time + FireRate;
            Instantiate(Bolt, BoltSpawn.position, BoltSpawn.rotation);
            GetComponent<AudioSource>().Play();
        }
    }

    void FixedUpdate()
    {
        float verticalMovement = Input.GetAxis("Vertical");
        float horizontalMovement = Input.GetAxis("Horizontal");

        Vector3 movement = new Vector3(horizontalMovement, 0f, verticalMovement);
        var rigidBody = GetComponent<Rigidbody>();
        rigidBody.velocity = movement*Speed;
        rigidBody.position = new Vector3(
            Mathf.Clamp(rigidBody.position.x, Boundaries.MinX, Boundaries.MaxX),
            0,
            Mathf.Clamp(rigidBody.position.y, Boundaries.MinZ, Boundaries.MaxZ)
            );
        rigidBody.rotation = Quaternion.Euler(0f, 0f, rigidBody.position.x*Tilt);
    }
}
