using UnityEngine;
using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using Kata.LoanPrediction.Unity.Common;
using Kata.LoanPrediction.Unity.Common.Calculator;
using Kata.LoanPrediction.Unity.Common.Models;

public class ApplicationController : MonoBehaviour
{
	public TowerBuilder TowerBuilder = null;

	// Use this for initialization
	void Start ()
	{
		LoanContext context = new LoanContext (DateTime.Now, new DateTime (2007, 03, 01), new DateTime (2010, 10, 01), 186000d, 5.74d, 1280d, 1, 2000d, 18);
		LoanCalculator calculator = new LoanCalculator (context);
		LoanCalculationOutput output = calculator.Calculate ();
		
		int currentMonth = 0;
		var groupedByMonthYear = output.Transactions.GroupBy (x => new { Month = x.Date.Month, Year = x.Date.Year });
		
		int towerLevels = groupedByMonthYear.Count ();
		
		List<GameObject> levels = TowerBuilder.BuildTower (towerLevels);
		levels.Reverse ();
		
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
			currentLevel++;
		}
				
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
	
	}
}
