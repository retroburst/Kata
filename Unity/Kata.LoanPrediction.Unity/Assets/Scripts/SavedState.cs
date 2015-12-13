using System;
using System.Collections;
using Kata.LoanPrediction.Unity.Common.Models;

/// <summary>
/// Represents a saved state.
/// </summary>
[Serializable]
public class SavedState {

	/// <summary>
	/// Gets or sets the saved date.
	/// </summary>
	/// <value>The saved date.</value>
	public DateTime SavedDate { get; set; }

	/// <summary>
	/// Gets or sets the context.
	/// </summary>
	/// <value>The context.</value>
	public LoanContext Context { get; set; }
}
