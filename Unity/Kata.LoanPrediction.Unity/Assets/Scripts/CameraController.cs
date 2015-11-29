using UnityEngine;
using System.Collections;

public class CameraController : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		float vertical = Input.GetAxis("Vertical");
		gameObject.transform.position += new Vector3(0, vertical, 0);
	}
}
