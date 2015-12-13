using System.Collections;
using System.Collections.Generic;
using System;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;
using Kata.LoanPrediction.Unity.Common.Models;
using System.Globalization;

/// <summary>
/// Input panel controller.
/// Manages the input panel.
/// </summary>
public class InputPanelController : MonoBehaviour
{
	public event Action<LoanContext> BuildRequested;

	public InputField LoanStartDateField = null;
	public InputField LoanTargetEndDateField = null;
	public InputField LoanBalanceField = null;
	public InputField LoanInterestRateField = null;
	public InputField LoanMinRepaymentDayField = null;
	public InputField LoanMinRepaymentAmountField = null;
	public InputField LoanExtraRepaymentDayField = null;
	public InputField LoanExtraRepaymentAmountField = null;
	public GameObject InputPanel = null;
	public MessagePanelController MessagePanelController = null;
	private InputFieldNavigator navigator = null;

	/// <summary>
	/// Awake this instance.
	/// </summary>
	private void Awake ()
	{
		navigator = GetComponent<InputFieldNavigator> ();
	}

	/// <summary>
	/// Update this instance.
	/// </summary>
//	private void Update()
//	{
//		if (Input.GetKeyUp (KeyCode.Return) && InputPanel.activeInHierarchy && (!MessagePanelController.PanelActiveInHierachy)) {
//			RequestBuild();
//		}
//	}

	/// <summary>
	/// Initialises from a given context.
	/// </summary>
	/// <param name="context">Context.</param>
	public void InitialiseFrom (LoanContext context)
	{
		LoanStartDateField.text = context.StartDate.ToShortDateString ();
		LoanTargetEndDateField.text = context.TargetEndDate.ToShortDateString ();
		LoanBalanceField.text = context.Balance.ToString ();
		LoanInterestRateField.text = context.InterestRate.ToString ();
		LoanMinRepaymentDayField.text = context.MinRepaymentDay.ToString ();
		LoanMinRepaymentAmountField.text = context.MinRepaymentAmount.ToString ();
		LoanExtraRepaymentDayField.text = context.ExtraRepaymentDay.ToString ();
		LoanExtraRepaymentAmountField.text = context.ExtraRepaymentAmount.ToString ();
		navigator.Initialise ();
	}

	/// <summary>
	/// Validates the input.
	/// </summary>
	/// <returns><c>true</c>, if input was validated, <c>false</c> otherwise.</returns>
	/// <param name="context">Context.</param>
	private bool ValidateInput (out LoanContext context)
	{
		List<bool> results = new List<bool> ();
		context = new LoanContext ();
		ValidateLoanStartDate (context, results);
		ValidateLoanTargetEndDate (context, results);
		ValidateLoanBalance (context, results);
		ValidateLoanInterestRate (context, results);
		ValidateLoanMinRepaymentDay (context, results);
		ValidateLoanMinRepaymentAmount (context, results);
		ValidateLoanExtraRepaymentDay (context, results);
		ValidateLoanExtraRepaymentAmount (context, results);
		return(results.All (x => x));
	}

	/// <summary>
	/// Validates the loan start date.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="validationResults">Validation results.</param>
	private void ValidateLoanStartDate (LoanContext context, List<bool> validationResults)
	{
		DateTime loanStart = DateTime.Now;
		bool valid = DateTime.TryParseExact (LoanStartDateField.text, Constants.DateFormatsForParsing, CultureInfo.CurrentCulture, DateTimeStyles.AllowWhiteSpaces | DateTimeStyles.AssumeLocal, out loanStart);
		ProcessFieldValidationColor (valid, LoanStartDateField);
		context.StartDate = loanStart;
		validationResults.Add (valid);
	}

	/// <summary>
	/// Validates the loan target end date.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="validationResults">Validation results.</param>
	private void ValidateLoanTargetEndDate (LoanContext context, List<bool> validationResults)
	{
		DateTime loanTargetEnd = DateTime.MinValue;
		bool valid = true;
		// allow this field to be empty
		if (!string.IsNullOrEmpty (LoanTargetEndDateField.text)) {
			DateTime.TryParseExact (LoanTargetEndDateField.text, Constants.DateFormatsForParsing, CultureInfo.CurrentCulture, DateTimeStyles.AllowWhiteSpaces | DateTimeStyles.AssumeLocal, out loanTargetEnd);
		}
		ProcessFieldValidationColor (valid, LoanTargetEndDateField);
		context.TargetEndDate = loanTargetEnd;
		validationResults.Add (valid);
	}

	/// <summary>
	/// Validates the loan balance.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="validationResults">Validation results.</param>
	private void ValidateLoanBalance (LoanContext context, List<bool> validationResults)
	{
		double balance = 0.0d;
		bool valid = double.TryParse (LoanBalanceField.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out balance);
		ProcessFieldValidationColor (valid, LoanBalanceField);
		context.Balance = balance;
		validationResults.Add (valid);
	}

	/// <summary>
	/// Validates the loan interest rate.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="validationResults">Validation results.</param>
	private void ValidateLoanInterestRate (LoanContext context, List<bool> validationResults)
	{
		double interestRate = 0.0d;
		bool valid = double.TryParse (LoanInterestRateField.text, NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out interestRate);
		ProcessFieldValidationColor (valid, LoanInterestRateField);
		context.InterestRate = interestRate;
		validationResults.Add (valid);
	}

	/// <summary>
	/// Validates the loan minimum repayment day.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="validationResults">Validation results.</param>
	private void ValidateLoanMinRepaymentDay (LoanContext context, List<bool> validationResults)
	{
		int minRepaymentDay = 1;
		bool valid = int.TryParse (LoanMinRepaymentDayField.text, NumberStyles.Integer, CultureInfo.CurrentCulture, out minRepaymentDay);
		valid = valid && minRepaymentDay >= 1 && minRepaymentDay <= 31;
		ProcessFieldValidationColor (valid, LoanMinRepaymentDayField);
		context.MinRepaymentDay = minRepaymentDay;
		validationResults.Add (valid);
	}

	/// <summary>
	/// Validates the loan minimum repayment amount.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="validationResults">Validation results.</param>
	private void ValidateLoanMinRepaymentAmount (LoanContext context, List<bool> validationResults)
	{
		double minRepaymentAmount = 0.0d;
		bool valid = double.TryParse (LoanMinRepaymentAmountField.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out minRepaymentAmount);
		valid = valid && minRepaymentAmount > 0;
		ProcessFieldValidationColor (valid, LoanMinRepaymentAmountField);
		context.MinRepaymentAmount = minRepaymentAmount;
		validationResults.Add (valid);
	}

	/// <summary>
	/// Validates the loan extra repayment day.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="validationResults">Validation results.</param>
	private void ValidateLoanExtraRepaymentDay (LoanContext context, List<bool> validationResults)
	{
		int extraRepaymentDay = 1;
		bool valid = true;
		if (!string.IsNullOrEmpty (LoanExtraRepaymentDayField.text)) {
			int.TryParse (LoanExtraRepaymentDayField.text, NumberStyles.Integer, CultureInfo.CurrentCulture, out extraRepaymentDay);
			valid = valid && extraRepaymentDay >= 1 && extraRepaymentDay <= 31;
		}
		ProcessFieldValidationColor (valid, LoanExtraRepaymentDayField);
		context.ExtraRepaymentDay = extraRepaymentDay;
		validationResults.Add (valid);
	}

	/// <summary>
	/// Validates the loan extra repayment amount.
	/// </summary>
	/// <param name="context">Context.</param>
	/// <param name="validationResults">Validation results.</param>
	private void ValidateLoanExtraRepaymentAmount (LoanContext context, List<bool> validationResults)
	{
		double extraRepaymentAmount = 0.0d;
		bool valid = true;
		if (!string.IsNullOrEmpty (LoanExtraRepaymentAmountField.text)) {
			valid = double.TryParse (LoanExtraRepaymentAmountField.text, NumberStyles.AllowCurrencySymbol | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite, CultureInfo.CurrentCulture, out extraRepaymentAmount);
			valid = valid && extraRepaymentAmount > 0;
			if (string.IsNullOrEmpty (LoanExtraRepaymentDayField.text)) { 
				ProcessFieldValidationColor (false, LoanExtraRepaymentDayField); 
				valid = false;
			}
		}
		ProcessFieldValidationColor (valid, LoanExtraRepaymentAmountField);
		context.ExtraRepaymentAmount = extraRepaymentAmount;
		validationResults.Add (valid);
	}

	/// <summary>
	/// Processes the color of the field validation.
	/// </summary>
	/// <param name="valid">If set to <c>true</c> valid.</param>
	/// <param name="field">Field.</param>
	/// <typeparam name="T">The 1st type parameter.</typeparam>
	private void ProcessFieldValidationColor (bool valid, InputField field)
	{
		if (valid) {
			field.transform.FindChild ("Label").GetComponent<Text> ().color = Color.white;
		} else {
			field.transform.FindChild ("Label").GetComponent<Text> ().color = Color.red;
		}
	}

	/// <summary>
	/// Requests the build.
	/// </summary>
	public void RequestBuild ()
	{
		LoanContext context = null;
		if (!ValidateInput (out context)) {
			MessagePanelController.SetMessage ("Some values input are invalid, please review the fields marked with red.");
			MessagePanelController.ShowMessagePanel ();
			return;
		}
		if (BuildRequested != null)
			BuildRequested (context);
	}

	/// <summary>
	/// Shows the input panel.
	/// </summary>
	public void ShowInputPanel ()
	{
		InputPanel.SetActive (true);
	}

	/// <summary>
	/// Hides the input panel.
	/// </summary>
	public void HideInputPanel ()
	{
		InputPanel.SetActive (false);
	}

	/// <summary>
	/// Is the pancel active in the hierachy.
	/// </summary>
	/// <returns><c>true</c>, if in hierachy was actived, <c>false</c> otherwise.</returns>
	public bool PanelActiveInHierachy {
		get { return(InputPanel.activeInHierarchy); }
	}
	
}
