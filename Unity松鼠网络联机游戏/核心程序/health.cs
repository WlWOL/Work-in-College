using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Networking;

public class health : NetworkBehaviour
{

    public const int maxHealth = 100;
    public bool destroyOnDeath;

    [SyncVar(hook = "OnChangeHealth")]
    public int currentHealth = 100;


    [SyncVar(hook = "OnChangeCount")]
    public int count = 0;



    [SyncVar]
    public bool dead = false;


    public RectTransform healthBar;

    public NetworkStartPosition[] spawnPoints;

    // Use this for initialization
    public void TakeDamage(int amount)              //受到冬天伤害,血量越高,伤害
    {
        if (!isServer)
        {
            return;
        }
        currentHealth -= (int)(((amount * currentHealth) / 200) + 5);                           //血量越高,伤害越高,这里是线性关系,设amount=10,,基础伤害5，每多20点血，伤害+1;
        if (currentHealth <= 0)
        {
            if (destroyOnDeath)
            {
                Destroy(gameObject);
            }
            else
            {
                dead = true; 
         
            }
        }
    }

    public void TakeplayerDamage(int amount)              //受到玩家伤害,
    {
        if (!isServer)
        {
            return;
        }
        currentHealth -= amount;                           //血量越高,伤害越高,这里是线性关系,设amount=10,,基础伤害5，每多20点血，伤害+1;
        if (currentHealth <= 0)
        {
            if (destroyOnDeath)
            {
                Destroy(gameObject);
            }
            else
            {
                dead = true;
            }
        }
    }










    void Start()
    {

    }




    public void Take()
    {
        if (!isServer)
        {
            return;
        }
        count++;                                
       
    }


    [Command]
    public void CmdEat()
    {
 
        if (count > 0)
        {
            count--;
            currentHealth += 20;                //吃一个松果回+20血
        }
    }









    void OnChangeHealth(int currentHealth)
    {
        healthBar.sizeDelta = new Vector2(currentHealth, healthBar.sizeDelta.y);
        if (isLocalPlayer)
        {
            this.currentHealth = currentHealth;
        }
           
    }
    void OnChangeCount(int count)
    {
        if (isLocalPlayer)
        {
            this.count= count;
        }

    }





    [ClientRpc]
    void RpcRespawn()
    {
        if (isLocalPlayer)
        {
            // Set the spawn point to origin as a default value
            Vector3 spawnPoint = Vector3.zero;

            // If there is a spawn point array and the array is not empty, pick one at random
            if (spawnPoints != null && spawnPoints.Length > 0)
            {
                spawnPoint = spawnPoints[Random.Range(0, spawnPoints.Length)].transform.position;
            }

            // Set the player’s position to the chosen spawn point
            transform.position = spawnPoint;

        }
    }
}
