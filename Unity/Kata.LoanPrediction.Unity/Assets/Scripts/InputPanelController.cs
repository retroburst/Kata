using System.Collections;
using System;
using UnityEngine;
using UnityEngine.UI;
using Kata.LoanPrediction.Unity.Common.Models;
using System.Globalization;

public class InputPanelController : MonoBehaviour {
	public event Action<LoanContext> BuildRequested;
	public InputField LoanStartDateField = null;
	public InputField LoanTargetEndDateField = null;
	public InputField LoanBalanceField = null;
	public InputField LoanInterestRateField = null;
	public InputField LoanMinRepaymentDayField = null;
	public InputField LoanMinRepaymentAmountField = null;
	public InputField LoanExtraRepaymentDayField = null;
	public InputField LoanExtraRepaymentAmountField = null;
	private InputFieldNavigator navigator = null;
	
	/// <summary>
	/// Awake this instance.
	/// </summary>
	private void Awake()
	{
		navigator = GetComponent<InputFieldNavigator>();
	}
	
	/// <summary>
	/// Initialises from a given context.
	/// </summary>
	/// <param name="context">Context.</param>
	public void InitialiseFrom(LoanContext context)
	{
		LoanStartDateField.text = context.StartDate.ToShortDateString();
		LoanTargetEndDateField.text = context.TargetEndDate.ToShortDateString();
		LoanBalanceField.text = context.Balance.ToString();
		LoanInterestRateField.text = context.InterestRate.ToString();
		LoanMinRepaymentDayField.text = context.MinRepaymentDay.ToString();
		LoanMinRepaymentAmountField.text = context.MinRepaymentAmount.ToString();
		LoanExtraRepaymentDayField.text = context.ExtraRepaymentDay.ToString();
		LoanExtraRepaymentAmountField.text = context.ExtraRepaymentAmount.ToString();
		navigator.Initialise();
	}
	
	/// <summary>
	/// Validates the input.
	/// </summary>
	/// <returns><c>true</c>, if input was validated, <c>false</c> otherwise.</returns>
	/// <param name="target">Target.</param>
	private bool ValidateInput(out LoanContext target)
	{
		target = new LoanContext();
		// todo parse values
		DateTime loanStart = DateTime.Now;
		if(DateTime.TryParseExact(LoanStartDateField.text, new string[] {"dd/MM/yyyy", "d/M/yyyy", "d/MM/yyyy", "dd/M/yyyy"}, CultureInfo.CurrentCulture, DateTimeStyles.AllowWhiteSpaces | DateTimeStyles.AssumeLocal, out loanStart))
			target.StartDate = loanStart;
		else
			return(false);
	
		DateTime loanTargetEnd = DateTime.Now;
		if(DateTime.TryParseExact(LoanTargetEndDateField.text, new string[] {"dd/MM/yyyy", "d/M/yyyy", "d/MM/yyyy", "dd/M/yyyy"}, CultureInfo.CurrentCulture, DateTimeStyles.AllowWhiteSpaces | DateTimeStyles.AssumeLocal, out loanTargetEnd))
			target.TargetEndDate = loanTargetEnd;
		else
			return(false);
			
		double balance = 0.0d;
		if(double.TryParse(LoanBalanceField.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out balance))
			target.Balance = balance;
		else
			return(false);
		
		double interestRate = 0.0d;
		if(double.TryParse(LoanInterestRateField.text, NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out interestRate))
			target.InterestRate = interestRate;
		else
			return(false);		
		
		int minRepaymentDay = 0;
		if(int.TryParse(LoanMinRepaymentDayField.text, NumberStyles.Integer, CultureInfo.CurrentCulture, out minRepaymentDay))
			target.MinRepaymentDay = minRepaymentDay;
		else
			return(false);
		
		double minRepaymentAmount = 0.0d;
		if(double.TryParse(LoanMinRepaymentAmountField.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out minRepaymentAmount))
			target.MinRepaymentAmount = minRepaymentAmount;
		else
			return(false);
		
		int extraRepaymentDay = 0;
		if(int.TryParse(LoanExtraRepaymentDayField.text, NumberStyles.Integer, CultureInfo.CurrentCulture, out extraRepaymentDay))
			target.ExtraRepaymentDay = extraRepaymentDay;
		else
			return(false);
		
		double extraRepaymentAmount = 0.0d;
		if(double.TryParse(LoanExtraRepaymentAmountField.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out extraRepaymentAmount))
			target.ExtraRepaymentAmount = extraRepaymentAmount;
		else
			return(false);
		
		// make sure we won't get infinite loop like no minimum repayment or extra repayment amount
		if(target.MinRepaymentAmount <= 0 || target.MinRepaymentDay <= 0 || target.MinRepaymentDay > 31)
			return(false);
		
		return(true);
	}
	
	/// <summary>
	/// Requests the build.
	/// </summary>
	public void RequestBuild()
	{
		LoanContext context = null;
		if(!ValidateInput(out context)) return;
		if(BuildRequested != null) BuildRequested(context);
	}
	

	
}
