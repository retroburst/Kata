using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Kata.LoanPrediction.Unity.Common.Models
{
    /// <summary>
    /// Represents the output from the
    /// LoanCalculator.
    /// </summary>
    public class LoanCalculationOutput
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="LoanCalculationOutput"/> class.
        /// </summary>
        public LoanCalculationOutput()
        {
            Transactions = new List<LoanTransaction>();
            Failure = false;
            FailureMessage = string.Empty;
        }

        /// <summary>
        /// Gets the transactions.
        /// </summary>
        /// <value>
        /// The transactions.
        /// </value>
        public List<LoanTransaction> Transactions { get; private set; }

        /// <summary>
        /// Gets or sets the interest start date.
        /// </summary>
        /// <value>
        /// The interest start date.
        /// </value>
        public DateTime InterestStartDate { get; set; }

        /// <summary>
        /// Gets or sets the loan ends date.
        /// </summary>
        /// <value>
        /// The loan ends date.
        /// </value>
        public DateTime LoanEndsDate { get; set; }

        /// <summary>
        /// Gets or sets the total interest paid.
        /// </summary>
        /// <value>
        /// The total interest paid.
        /// </value>
        public double TotalInterestPaid { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [target end date hit].
        /// </summary>
        /// <value>
        ///   <c>true</c> if [target end date hit]; otherwise, <c>false</c>.
        /// </value>
        public bool TargetEndDateHit { get; set; }

        /// <summary>
        /// Gets or sets the target end date missed in days.
        /// </summary>
        /// <value>
        /// The target end date missed in days.
        /// </value>
        public int TargetEndDateMissedInDays { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this
        /// <see cref="Kata.LoanPrediction.Unity.Common.Models.LoanCalculationOutput"/> is failure.
        /// </summary>
        /// <value><c>true</c> if failure; otherwise, <c>false</c>.</value>
        public bool Failure {get; set;}

        /// <summary>
        /// Gets or sets the failure message.
        /// </summary>
        /// <value>The failure message.</value>
        public string FailureMessage { get; set; }
        
    }
}
