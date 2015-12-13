using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;

/// <summary>
/// Input field navigator - adds
/// support for tab-ing through
/// the form fields.
/// </summary>
public class InputFieldNavigator : MonoBehaviour
{
	private EventSystem eventSystem = null;
	public Selectable[] Fields = null;

	/// <summary>
	/// Initialise this instance.
	/// </summary>
	public void Initialise ()
	{
		Fields [0].Select ();
		InputField input = Fields [0].gameObject.GetComponent<InputField> ();
		if (input != null)
			input.ActivateInputField ();
	}

	/// <summary>
	/// Awake this instance.
	/// </summary>
	private void Awake ()
	{
		eventSystem = EventSystem.current;	
	}

	/// <summary>
	/// Update this instance.
	/// </summary>
	private void Update ()
	{
		if (Input.GetKeyDown (KeyCode.Tab)) {
			Selectable next = null;
			GameObject current = eventSystem.currentSelectedGameObject;
			for (int i = 0; i < Fields.Length; i++) {
				if (Fields [i].gameObject == current) {
					if (i + 1 < Fields.Length)
						next = Fields [i + 1];
					else
						next = Fields [0];
					break;
				}
			}
			if (next != null) {
				next.Select ();
				InputField input = next.gameObject.GetComponent<InputField> ();
				if (input != null)
					input.ActivateInputField ();
			}
		}
	}
}