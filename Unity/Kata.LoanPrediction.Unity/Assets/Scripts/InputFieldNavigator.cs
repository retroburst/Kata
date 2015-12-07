using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class InputFieldNavigator : MonoBehaviour
{
	private EventSystem eventSystem = null;
	public Selectable[] Fields = null;
	
	public void Initialise()
	{
		Fields[0].Select();
		InputField input = Fields[0].gameObject.GetComponent<InputField>();
		if(input != null) input.ActivateInputField();
	}
	
	private void Awake()
	{
		eventSystem = EventSystem.current;// EventSystemManager.currentSystem	
	}
	
	// Update is called once per frame
	void Update()
	{
		if (Input.GetKeyDown(KeyCode.Tab))
		{
			Selectable next = null;
			GameObject current = eventSystem.currentSelectedGameObject;
			
			for(int i=0; i < Fields.Length; i++)
			{
				if(Fields[i].gameObject == current) 
				{
					if(i+1 < Fields.Length) next = Fields[i+1];
					else next = Fields[0];
					break;
				}
			}
			//next.OnPointerClick(new PointerEventData(eventSystem));  //if it's an input field, also set the text caret
			//eventSystem.SetSelectedGameObject(next.gameObject, new BaseEventData(eventSystem));
			if(next != null)
			{
				next.Select();
				InputField input = next.gameObject.GetComponent<InputField>();
				if(input != null) input.ActivateInputField();
			}
			//else Debug.Log("next nagivation element not found");
		}
	}
}