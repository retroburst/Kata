using UnityEngine;
using System.Collections;

/// <summary>
/// Wooden sign controller.
/// </summary>
public class WoodenSignController : MonoBehaviour
{
	private TextMesh MonthBalanceText = null;
	private TextMesh TransactionsText = null;

	/// <summary>
	/// Awake this instance.
	/// </summary>
	public void Awake ()
	{
		MonthBalanceText = gameObject.transform.FindChild (Constants.CHILD_MONTH_BALANCE_TEXT).GetComponent<TextMesh> ();
		TransactionsText = gameObject.transform.FindChild (Constants.CHILD_MONTH_TRANSACTIONS_TEXT).GetComponent<TextMesh> ();
	}

	/// <summary>
	/// Sets the month balance text.
	/// </summary>
	/// <param name="text">Text.</param>
	public void SetMonthBalanceText (string text)
	{
		if (MonthBalanceText != null && text != null)
			MonthBalanceText.text = text;
	}

	/// <summary>
	/// Sets the transactions text.
	/// </summary>
	/// <param name="text">Text.</param>
	public void SetTransactionsText (string text)
	{
		if (TransactionsText != null && text != null)
			TransactionsText.text = text;
	}

	/// <summary>
	/// Changs the material.
	/// </summary>
	/// <param name="target">Target.</param>
	public void ChangMaterial (Material target)
	{
		gameObject.GetComponent<MeshRenderer> ().material = target;
	}
}
