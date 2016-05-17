using System;
using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using Random = UnityEngine.Random;

public class GameController : MonoBehaviour
{
    public GameObject PlayerGameObject;
    public List<GameObject> hazards;
    public Vector3 spawnValues;
    public int hazardCount;
    public float spawnWait;
    public float startWait;
    public float waveWait;
    public Text textObject;

    private int score;

    public Vector3 InitialPlayerPosition;

    void Start()
    {
        StartCoroutine(SpawnWaves());
        UpdateScore();
        Restart();
    }

    IEnumerator SpawnWaves()
    {
        yield return new WaitForSeconds(startWait);
        while (true)
        {
            for (int i = 0; i < hazardCount; i++)
            {
                Vector3 spawnPosition = new Vector3(Random.Range(-spawnValues.x, spawnValues.x), spawnValues.y, spawnValues.z);
                Quaternion spawnRotation = Quaternion.identity;
                Instantiate(hazards[Random.Range(0,hazards.Count)], spawnPosition, spawnRotation);
                yield return new WaitForSeconds(spawnWait);
            }
            yield return new WaitForSeconds(waveWait);
        }
    }

    public void SetScore(int score)
    {
        this.score += score;
        UpdateScore();
    }

    public void UpdateScore()
    {
        textObject.text = score.ToString();
    }

    public void GameOver()
    {
        Invoke("Restart", 1);
    }

    public void Restart()
    {
        Instantiate(PlayerGameObject, InitialPlayerPosition, Quaternion.Euler(0, 0, 0));
        score = 0;
        UpdateScore();
    }
}