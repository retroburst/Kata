using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using Kata.LoanPrediction.Unity.Common;
using Kata.LoanPrediction.Unity.Common.Calculator;
using Kata.LoanPrediction.Unity.Common.Models;
using System.Runtime.Serialization.Formatters.Binary;
using System.Threading;
using System.Runtime.Serialization;

/// <summary>
/// Manages the application process flow.
/// </summary>
public class ApplicationController : MonoBehaviour
{
	public TowerBuilder TowerBuilder = null;
	public CameraController CameraController = null;
	public InputPanelController InputPanelController = null;
	public MessagePanelController MessagePanelController = null;
	public Text DebugText = null;
	public string SaveStateFilename = "Kata.LoanPrediction.Unity.State.save";
	public Material RedWoodenSignMaterial = null;
	private object applicationSaveStateLock = null;
	private object applicationLoadStateLock = null;
	private LoanContext defaultState = null;

	/// <summary>
	/// Awake this instance.
	/// </summary>
	private void Awake ()
	{
		CultureInfo enAU = new System.Globalization.CultureInfo ("en-AU");
		Thread.CurrentThread.CurrentCulture = enAU;
		Thread.CurrentThread.CurrentUICulture = enAU;
		defaultState = BuildDefaultLoanContext ();
		applicationSaveStateLock = new object ();
		applicationLoadStateLock = new object ();
		InputPanelController.BuildRequested += HandleBuildRequested;
		TowerBuilder.ClearTower ();
		InputPanelController.ShowInputPanel ();
		TryLoadSavedState ();
	}

	/// <summary>
	/// Builds the default loan context.
	/// </summary>
	/// <returns>The default loan context.</returns>
	private LoanContext BuildDefaultLoanContext ()
	{
		LoanContext result = new LoanContext ();
		result.Balance = 200000.00d;
		result.ExtraRepaymentAmount = 1000.00d;
		result.ExtraRepaymentDay = 18;
		result.InterestRate = 5.50d;
		result.MinRepaymentAmount = 1500.00d;
		result.MinRepaymentDay = 1;
		result.StartDate = DateTime.Now;
		result.TargetEndDate = DateTime.Now.AddYears (8);
		result.TodaysDate = DateTime.Now;
		return(result);
	}

	/// <summary>
	/// Handles the build requested.
	/// </summary>
	/// <param name="context">Context.</param>
	private void HandleBuildRequested (LoanContext context)
	{
		DebugText.text = string.Empty;
		TrySaveState (context);
		LoanCalculator calculator = new LoanCalculator (context);
		LoanCalculationOutput output = null;
		output = calculator.Calculate ();
		if (output.Failure) {
			Debug.LogError (output.FailureMessage);
			InputPanelController.SetErrorText(output.FailureMessage);
			return;
		}
		var groupedByMonthYear = output.Transactions.GroupBy (x => new { Month = x.Date.Month, Year = x.Date.Year });
		int towerLevels = groupedByMonthYear.Count ();
		List<GameObject> levels = TowerBuilder.BuildTower (towerLevels);
		int currentLevel = 0;
		foreach (var group in groupedByMonthYear) {
			int year = group.Key.Year;
			int month = group.Key.Month;
			IEnumerable<LoanTransaction> groupedTransactions = group.ToList ();
			LoanTransaction lastTransaction = group.Last ();
			BuildSignTextForTowerLevel (context, currentLevel, year, month, groupedTransactions, lastTransaction, levels [currentLevel]);
			currentLevel++;
		}
		CameraController.MaxY = levels.Last ().transform.position.y - 5;	
		InputPanelController.HideInputPanel ();
		DebugText.text = string.Format ("Tower Levels: {0} / Total Interest: {1} / Loan Ends: {2}", towerLevels, output.TotalInterestPaid.ToString ("c"), output.LoanEndsDate.ToShortDateString ());
	}

	/// <summary>
	/// Builds the sign text for a tower level.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="currentLevel">Current level.</param>
	/// <param name="year">Year.</param>
	/// <param name="month">Month.</param>
	/// <param name="groupedTransactions">Grouped transactions.</param>
	/// <param name="lastTransaction">Last transaction.</param>
	/// <param name="level">Level.</param>
	private void BuildSignTextForTowerLevel (LoanContext context, int currentLevel, int year, int month, IEnumerable<LoanTransaction> groupedTransactions, LoanTransaction lastTransaction, GameObject level)
	{
		DateTime timePoint = new DateTime (year, month, 1);
		string date = timePoint.ToString ("MMM yyyy");
		string balance = lastTransaction.Balance.ToString ("c0");
		WoodenSignController signController = level.transform.FindChild (Constants.CHILD_WOODEN_SIGN).GetComponent<WoodenSignController> ();
		signController.SetMonthBalanceText (string.Format ("{0}\n{1}", date, balance));
		string transactions = string.Empty;
		foreach (LoanTransaction tx in groupedTransactions) {
			transactions += ConvertTransactionType (tx.Type);
			transactions += tx.Debit > 0 ? " -" : " +";
			transactions += tx.Debit > 0 ? tx.Debit.ToString ("c0") : tx.Credit.ToString ("c0");
			transactions += "\n";
		}
		signController.SetTransactionsText (transactions);
		if (context.TargetEndDate.Year == year && context.TargetEndDate.Month == month) {
			signController.ChangMaterial (RedWoodenSignMaterial);
		} else {
			signController.ResetMaterial();
		}
	}

	/// <summary>
	/// Converts the type of the transaction.
	/// </summary>
	/// <returns>The transaction type.</returns>
	/// <param name="target">Target.</param>
	private string ConvertTransactionType (TransactionType target)
	{
		switch (target) {
		case TransactionType.ExtraRepayment:
			return("Extra Repay");
		case TransactionType.FinalRepayment:
			return("Final Repay");
		case TransactionType.InterestCharged:
			return("Interest");
		case TransactionType.MinimumRepayment:
			return("Min Repay");
		default:
			return("Unknown");
		}
	}

	/// <summary>
	/// Update this instance.
	/// </summary>
	private void Update ()
	{
		if (Input.GetKeyUp (KeyCode.Escape) && !InputPanelController.PanelActiveInHierachy) {
			InputPanelController.ShowInputPanel ();
		}
	}

	/// <summary>
	/// Tries to load saved state.
	/// </summary>
	private void TryLoadSavedState ()
	{
		lock (applicationLoadStateLock) {
			string savedStateFilename = Path.Combine (Application.persistentDataPath, SaveStateFilename);
			try {
				if (!File.Exists (savedStateFilename)) {
					InputPanelController.InitialiseFrom (defaultState);
					return;
				}
				SavedState savedState = null;
				BinaryFormatter formatter = new BinaryFormatter ();
				using (FileStream fs = File.Open (savedStateFilename, FileMode.Open)) {
					savedState = (SavedState)formatter.Deserialize (fs);
					fs.Close ();
				}
				InputPanelController.InitialiseFrom (savedState.Context);
			} catch (SerializationException sx) {
				if (File.Exists (savedStateFilename))
					File.Delete (savedStateFilename);
				InputPanelController.InitialiseFrom (defaultState);
				MessagePanelController.SetMessage (string.Format ("Failed to load saved state: {0}", sx.Message));
				MessagePanelController.ShowMessagePanel ();
			} catch (Exception ex) {
				InputPanelController.InitialiseFrom (defaultState);
				MessagePanelController.SetMessage (string.Format ("Failed to load saved state: {0}", ex.Message));
				MessagePanelController.ShowMessagePanel ();
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
				saveState.Context = state;
				BinaryFormatter formatter = new BinaryFormatter ();
				using (FileStream fs = File.Open (savegameFilename, FileMode.OpenOrCreate)) {
					fs.SetLength (0);
					formatter.Serialize (fs, saveState);
					fs.Close ();
				}
			} catch (Exception ex) {
				MessagePanelController.SetMessage (string.Format ("Failed to save state: {0}", ex.Message));
				MessagePanelController.ShowMessagePanel ();
			}
		}
	}

}
