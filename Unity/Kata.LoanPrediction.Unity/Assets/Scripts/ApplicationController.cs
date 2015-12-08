using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using Kata.LoanPrediction.Unity.Common;
using Kata.LoanPrediction.Unity.Common.Calculator;
using Kata.LoanPrediction.Unity.Common.Models;

//TODO: save input in user prefs or serialization
using System.Runtime.Serialization.Formatters.Binary;


public class ApplicationController : MonoBehaviour
{
	public TowerBuilder TowerBuilder = null;
	public CameraController CameraController = null;
	public InputPanelController InputPanelController = null;
	public MessagePanelController MessagePanelController = null;
	public GameObject InputPanel = null;
	public Text DebugText = null;
	private object applicationSaveStateLock = null;
	private object applicationLoadStateLock = null;
	public string SaveStateFilename = "Kata.LoanPrediction.Unity.State.save";
	private LoanContext defaultState = null;
	public Material RedWoodenSignMaterial = null;
	public GameObject MessagePanel = null;
	
	/// <summary>
	/// Awake this instance.
	/// </summary>
	private void Awake()
	{
		defaultState = BuildDefaultState();
		applicationSaveStateLock = new object();
		applicationLoadStateLock = new object();
		InputPanelController.BuildRequested += HandleBuildRequested;
		TowerBuilder.ClearTower();
		ShowInputPanel();
		TryLoadSavedState();
	}
	
	/// <summary>
	/// Builds the default state.
	/// </summary>
	/// <returns>The default state.</returns>
	private LoanContext BuildDefaultState()
	{
		LoanContext result = new LoanContext();
		result.Balance = 200000.00d;
		result.ExtraRepaymentAmount = 1000.00d;
		result.ExtraRepaymentDay = 18;
		result.InterestRate = 5.50d;
		result.MinRepaymentAmount = 1500.00d;
		result.MinRepaymentDay = 1;
		result.StartDate = DateTime.Now;
		result.TargetEndDate = DateTime.Now.AddYears(25);
		result.TodaysDate = DateTime.Now;
		return(result);
	}

	private void HandleBuildRequested (LoanContext context)
	{
		DebugText.text = string.Empty;
		TrySaveState(context);
		LoanCalculator calculator = new LoanCalculator (context);
		LoanCalculationOutput output = null;
		try {
			output = calculator.Calculate ();
		} catch (Exception ex) {
			MessagePanelController.SetMessage(ex.Message);
			Debug.LogError(ex.Message);
			Debug.Log(ex.StackTrace);
			ShowMessagePanel();
			return;
		}
		
		int currentMonth = 0;
		var groupedByMonthYear = output.Transactions.GroupBy (x => new { Month = x.Date.Month, Year = x.Date.Year });
		
		int towerLevels = groupedByMonthYear.Count ();
		
		List<GameObject> levels = TowerBuilder.BuildTower (towerLevels);
		//levels.Reverse ();
		
		int currentLevel = 0;
		foreach (var group in groupedByMonthYear) {
			DateTime timePoint = new DateTime (group.Key.Year, group.Key.Month, 1);
			string date = timePoint.ToString ("MMM yyyy");
			string balance = group.Last ().Balance.ToString ("c0");
			GameObject level = levels [currentLevel];
			WoodenSignController sign = level.transform.FindChild ("WoodenSign").GetComponent<WoodenSignController> ();
			sign.SetMonthBalanceText (string.Format ("{0}\n{1}", date, balance));
			
			string transactions = string.Empty;
			foreach (LoanTransaction tx in group) {
				transactions += ConvertTransactionType (tx.Type);
				transactions += tx.Debit > 0 ? " +" : " -";
				transactions += tx.Debit > 0 ? tx.Debit.ToString ("c0") : tx.Credit.ToString ("c0");
				transactions += "\n";
			}
			
			sign.SetTransactionsText (transactions);
			
			if(context.TargetEndDate.Year == group.Key.Year && context.TargetEndDate.Month == group.Key.Month)
			{
				sign.ChangMaterial(RedWoodenSignMaterial);
			}
			currentLevel++;
		}
		CameraController.MaxY = levels.Last().transform.position.y - 5;	
		HideInputPanel();
		
		DebugText.text = string.Format("Tower Levels: {0} / Total Interest: {1} / Loan Ends: {2}", towerLevels, output.TotalInterestPaid.ToString("c"), output.LoanEndsDate.ToShortDateString());
	}
	
	// Use this for initialization
	void Start ()
	{
		
	}
	
	private string ConvertTransactionType (TransactionType target)
	{
		switch (target) {
		case TransactionType.ExtraRepayment:
			return("Extra Repay");
			break;
		case TransactionType.FinalRepayment:
			return("Final Repay");
			break;
		case TransactionType.InterestCharged:
			return("Interest");
			break;
		case TransactionType.MinimumRepayment:
			return("Min Repay");
			break;
		default:
			return("Unknown");
			break;
		}
	}
	
	// Update is called once per frame
	void Update ()
	{
		if(Input.GetKeyUp(KeyCode.Escape) && !InputPanel.activeInHierarchy)
		{
			ShowInputPanel();
		}
	}
	
	public void ShowInputPanel()
	{
		InputPanel.SetActive(true);
		
	}
	
	public void HideInputPanel()
	{
		InputPanel.SetActive(false);
	}
	
	public void ShowMessagePanel()
	{
		MessagePanel.SetActive(true);
	}
	
	public void HideMessagePanel()
	{
		MessagePanel.SetActive(false);
	}
	
	/// <summary>
	/// Tries to load saved state.
	/// </summary>
	private void TryLoadSavedState ()
	{
		lock (applicationLoadStateLock) {
			try {
				string savedStateFilename = Path.Combine (Application.persistentDataPath, SaveStateFilename);
				if (!File.Exists (savedStateFilename)) {
					InputPanelController.InitialiseFrom(defaultState);
					return;
				}
				SavedState savedState = null;
				BinaryFormatter formatter = new BinaryFormatter ();
				using (FileStream fs = File.Open(savedStateFilename, FileMode.Open)) {
					savedState = (SavedState)formatter.Deserialize (fs);
					fs.Close ();
				}
				InputPanelController.InitialiseFrom(savedState.State);
			} catch (Exception ex) {
				// todo: do something with this - msg or something
			}
		}
	}
	
	/// <summary>
	/// Tries to save the state.
	/// </summary>
	private void TrySaveState (LoanContext state)
	{
		lock (applicationSaveStateLock) {
			try {
				string savegameFilename = Path.Combine (Application.persistentDataPath, SaveStateFilename);
				SavedState saveState = new SavedState ();
				saveState.SavedDate = DateTime.Now;
				saveState.State = state;
				BinaryFormatter formatter = new BinaryFormatter ();
				using (FileStream fs = File.Open(savegameFilename, FileMode.OpenOrCreate)) {
					fs.SetLength (0);
					formatter.Serialize (fs, saveState);
					fs.Close ();
				}
			} catch (Exception ex) {
				// todo: do something with this - msg or something
			}
		}
	}

	
}
