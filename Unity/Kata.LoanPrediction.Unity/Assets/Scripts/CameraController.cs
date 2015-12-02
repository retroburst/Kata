using UnityEngine;
using System.Collections;

public class CameraController : MonoBehaviour {
	public float Speed = 0.75f;
	public float MaxY = 100.00f;
	public float MinY = 8.00f;
	
	// Use this for initialization
	void Awake () {
	
	}
	
	void Update()
	{
		float vertical = Input.GetAxis("Vertical");
		//rb.velocity = (new Vector3 (0.0f, vertical, 0.0f) * Speed);
		//float newY = rb.position.y; // Mathf.Clamp (rb.position.z, boundary.zMin, boundary.zMax); use this to clamp boundary
		//gameObject.transform.position = new Vector3(gameObject.transform.position.x, newY, gameObject.transform.position.z);
		//rb.rotation = Quaternion.Euler (new Vector3 (rb.velocity.y * -6, 0.0f, 0.0f));
		Vector3 newPosition = gameObject.transform.position + new Vector3(0.0f, vertical * Speed, 0.0f);
		gameObject.transform.position = new Vector3(newPosition.x, Mathf.Clamp(newPosition.y, MinY, MaxY), newPosition.z);
		gameObject.transform.rotation =  Quaternion.Euler (new Vector3 (vertical * -60, 0.0f, 0.0f));
	}
	
	/*
	// Update is called once per frame
	void FixedUpdate () {
		float vertical = Input.GetAxis("Vertical");
		//rb.velocity = (new Vector3 (0.0f, vertical, 0.0f) * Speed);
		//float newY = rb.position.y; // Mathf.Clamp (rb.position.z, boundary.zMin, boundary.zMax); use this to clamp boundary
		//gameObject.transform.position = new Vector3(gameObject.transform.position.x, newY, gameObject.transform.position.z);
		//rb.rotation = Quaternion.Euler (new Vector3 (rb.velocity.y * -6, 0.0f, 0.0f));
		
		gameObject.transform.position += new Vector3(0.0f, vertical, 0.0f);
		gameObject.transform.rotation =  Quaternion.Euler (new Vector3 (vertical * -50, 0.0f, 0.0f));
	}
	*/
	
	/*
	private void FixedUpdate334343434 ()
	{
		float moveHorizontal = Input.GetAxis (AXIS_HORIZONTAL);
		float moveVertical = Input.GetAxis (AXIS_VERTICAL);
		rb.velocity = (new Vector3 (moveHorizontal, 0.0f, moveVertical) * Speed);
		float newX = Mathf.Clamp (rb.position.x, boundary.xMin, boundary.xMax);
		float newY = Mathf.Clamp (rb.position.z, boundary.zMin, boundary.zMax);
		rb.position = new Vector3 (newX, 0.0f, newY);
		rb.rotation = Quaternion.Euler (new Vector3 (0.0f, 0.0f, rb.velocity.x * -tilt));
	}
	*/
}
