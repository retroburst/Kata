using UnityEngine;
using System.Collections;

/// <summary>
/// Controls the camera movement and rotation.
/// </summary>
public class CameraController : MonoBehaviour {
	public float Speed = 0.75f;
	public float MaxY = 100.00f;
	public float MinY = 8.00f;

	/// <summary>
	/// Update this instance.
	/// </summary>
	private void Update()
	{
		float vertical = Input.GetAxis("Vertical");
		Vector3 newPosition = gameObject.transform.position + new Vector3(0.0f, vertical * Speed, 0.0f);
		gameObject.transform.position = new Vector3(newPosition.x, Mathf.Clamp(newPosition.y, MinY, MaxY), newPosition.z);
		gameObject.transform.rotation =  Quaternion.Euler (new Vector3 (vertical * -60, 0.0f, 0.0f));
	}

}
