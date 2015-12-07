using System;
using System.Collections;
using Kata.LoanPrediction.Unity.Common.Models;

[Serializable]
public class SavedState {
	public DateTime SavedDate { get; set; }
	public LoanContext State { get; set; }
}
