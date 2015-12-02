using System.Collections;
using System;
using UnityEngine;
using UnityEngine.UI;
using Kata.LoanPrediction.Unity.Common.Models;
using System.Globalization;

public class InputPanelController : MonoBehaviour {
	public event Action<LoanContext> BuildRequested;
	public Text LoanStartDateText = null;
	public Text LoanTargetEndDateText = null;
	public Text LoanBalanceText = null;
	public Text LoanInterestRateText = null;
	public Text LoanMinRepaymentDayText = null;
	public Text LoanMinRepaymentAmountText = null;
	public Text LoanExtraRepaymentDayText = null;
	public Text LoanExtraRepaymentAmountText = null;
	
	private bool ValidateInput(out LoanContext target)
	{
		target = new LoanContext();
		// todo parse values
		DateTime loanStart = DateTime.Now;
		if(DateTime.TryParseExact(LoanStartDateText.text, new string[] {"dd/MM/yyyy", "d/M/yyyy", "d/MM/yyyy", "dd/M/yyyy"}, CultureInfo.CurrentCulture, DateTimeStyles.AllowWhiteSpaces | DateTimeStyles.AssumeLocal, out loanStart))
			target.StartDate = loanStart;
		else
			return(false);
	
		DateTime loanTargetEnd = DateTime.Now;
		if(DateTime.TryParseExact(LoanTargetEndDateText.text, new string[] {"dd/MM/yyyy", "d/M/yyyy", "d/MM/yyyy", "dd/M/yyyy"}, CultureInfo.CurrentCulture, DateTimeStyles.AllowWhiteSpaces | DateTimeStyles.AssumeLocal, out loanStart))
			target.TargetEndDate = loanTargetEnd;
		else
			return(false);
			
		double balance = 0.0d;
		if(double.TryParse(LoanBalanceText.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out balance))
			target.Balance = balance;
		else
			return(false);
		
		double interestRate = 0.0d;
		if(double.TryParse(LoanInterestRateText.text, NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out interestRate))
			target.InterestRate = interestRate;
		else
			return(false);		
		
		int minRepaymentDay = 0;
		if(int.TryParse(LoanMinRepaymentDayText.text, NumberStyles.Integer, CultureInfo.CurrentCulture, out minRepaymentDay))
			target.MinRepaymentDay = minRepaymentDay;
		else
			return(false);
		
		double minRepaymentAmount = 0.0d;
		if(double.TryParse(LoanMinRepaymentAmountText.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out minRepaymentAmount))
			target.MinRepaymentAmount = minRepaymentAmount;
		else
			return(false);
		
		int extraRepaymentDay = 0;
		if(int.TryParse(LoanExtraRepaymentDayText.text, NumberStyles.Integer, CultureInfo.CurrentCulture, out extraRepaymentDay))
			target.ExtraRepaymentDay = extraRepaymentDay;
		else
			return(false);
		
		double extraRepaymentAmount = 0.0d;
		if(double.TryParse(LoanExtraRepaymentAmountText.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out extraRepaymentAmount))
			target.ExtraRepaymentAmount = extraRepaymentAmount;
		else
			return(false);
		
		// make sure we won't get infinite loop like no minimum repayment or extra repayment amount
		if(target.MinRepaymentAmount <= 0 || target.MinRepaymentDay <= 0 || target.MinRepaymentDay > 31)
			return(false);
		
		return(true);
	}
	
	public void RequestBuild()
	{
		LoanContext context = null;
		if(!ValidateInput(out context)) return;
		if(BuildRequested != null) BuildRequested(context);
	}
	

	
}
