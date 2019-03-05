using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class pine : MonoBehaviour {

    // Use this for initialization


   void OnCollisionEnter(Collision collision)
    {
    var hit = collision.gameObject;
    var counttt = hit.GetComponent<health>();

        if (counttt.count<4)                //限制捡4个松果
        {
            if(counttt!=null)
        {
            counttt.Take();
        }
        Destroy(gameObject);

        }



    }



}
