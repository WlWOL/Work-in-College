﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using UnityStandardAssets.


public class drive : MonoBehaviour {
    float speed = 10.0F;
    float rotationSpeed = 100.0F;

	
	
	// Update is called once per frame
	void Update () {
        float translation = Input.GetAxis("Vertical") * speed * Time.deltaTime;
        float rotation = Input.GetAxis("Horizontal") * rotationSpeed * Time.deltaTime;


        transform.Translate(0, 0, translation);
        transform.Rotate(0, rotation, 0);

    }
}
