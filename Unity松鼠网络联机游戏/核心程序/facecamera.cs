using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class facecamera : MonoBehaviour {


	
	// Update is called once per frame
	void Update () {
        this.transform.LookAt(Camera.main.transform.position);
        this.transform.Rotate(new Vector3(0,180,0));
    }
}
