using UnityEngine.UI;
using UnityEngine;
using System.Collections;

public class MessagePanelController : MonoBehaviour {
	public Text MessageText = null;
	
	public void SetMessage(string message)
	{
		MessageText.text = message;
	}
	
}
