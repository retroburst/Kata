using UnityEngine;
using System.Collections;

public class WoodenSignController : MonoBehaviour {
	private TextMesh MonthBalanceText;
	private TextMesh TransactionsText;
	
	public void Awake()
	{
		MonthBalanceText = gameObject.transform.FindChild("MonthBalanceText").GetComponent<TextMesh>();
		TransactionsText = gameObject.transform.FindChild("TransactionsText").GetComponent<TextMesh>();
	}
	
	public void SetMonthBalanceText(string text)
	{
		if(MonthBalanceText != null && text != null)
			MonthBalanceText.text = text;
	}
	
	public void SetTransactionsText(string text)
	{
		if(TransactionsText != null && text != null)
			TransactionsText.text = text;
	}
}
