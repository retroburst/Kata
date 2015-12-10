using System;
using System.Collections;
using Kata.LoanPrediction.Unity.Common.Models;

/// <summary>
/// Represents a saved state.
/// </summary>
[Serializable]
public class SavedState {
	public DateTime SavedDate { get; set; }
	public LoanContext Context { get; set; }
}
