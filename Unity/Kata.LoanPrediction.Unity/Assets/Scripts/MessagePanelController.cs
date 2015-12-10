using UnityEngine.UI;
using UnityEngine;
using System.Collections;

/// <summary>
/// Manages the message panel.
/// </summary>
public class MessagePanelController : MonoBehaviour {
	public Text MessageText = null;
	public GameObject MessagePanel = null;

	/// <summary>
	/// Sets the message.
	/// </summary>
	/// <param name="message">Message.</param>
	public void SetMessage(string message)
	{
		MessageText.text = message;
	}

	/// <summary>
	/// Shows the message panel.
	/// </summary>
	public void ShowMessagePanel()
	{
		MessagePanel.SetActive(true);
	}

	/// <summary>
	/// Hides the message panel.
	/// </summary>
	public void HideMessagePanel()
	{
		MessagePanel.SetActive(false);
	}

	/// <summary>
	/// Is the panel active in the hirachy.
	/// </summary>
	/// <returns><c>true</c>, if in hierachy was actived, <c>false</c> otherwise.</returns>
	public bool PanelActiveInHierachy
	{
		get{ return (MessagePanel.activeInHierarchy); }
	}

}
