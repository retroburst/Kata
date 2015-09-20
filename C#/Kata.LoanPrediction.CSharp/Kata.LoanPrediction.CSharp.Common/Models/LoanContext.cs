using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kata.LoanPrediction.CSharp.Common.Models
{
    /// <summary>
    /// Represents the context of a loan.
    /// </summary>
    public class LoanContext
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="LoanContext"/> class.
        /// </summary>
        public LoanContext()
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="LoanContext"/> class.
        /// </summary>
        /// <param name="todaysDate">The todays date.</param>
        /// <param name="startDate">The start date.</param>
        /// <param name="targetEndDate">The target end date.</param>
        /// <param name="balance">The balance.</param>
        /// <param name="interestRate">The interest rate.</param>
        /// <param name="minRepaymentAmount">The minimum repayment amount.</param>
        /// <param name="minRepaymentDay">The minimum repayment day.</param>
        /// <param name="extraRepaymentAmount">The extra repayment amount.</param>
        /// <param name="extraRepaymentDay">The extra repayment day.</param>
        public LoanContext(DateTime todaysDate, DateTime startDate, DateTime targetEndDate, double balance,
            double interestRate, double minRepaymentAmount, int minRepaymentDay, double extraRepaymentAmount,
            int extraRepaymentDay)
        {
            TodaysDate = todaysDate;
            StartDate = startDate;
            TargetEndDate = targetEndDate;
            Balance = balance;
            InterestRate = interestRate;
            MinRepaymentAmount = minRepaymentAmount;
            MinRepaymentDay = minRepaymentDay;
            ExtraRepaymentAmount = extraRepaymentAmount;
            ExtraRepaymentDay = extraRepaymentDay;
        }

        /// <summary>
        /// Gets or sets the todays date.
        /// </summary>
        /// <value>
        /// The todays date.
        /// </value>
        public DateTime TodaysDate { get; set; }
        
        /// <summary>
        /// Gets or sets the start date.
        /// </summary>
        /// <value>
        /// The start date.
        /// </value>
        public DateTime StartDate { get; set; } 
        
        /// <summary>
        /// Gets or sets the target end date.
        /// </summary>
        /// <value>
        /// The target end date.
        /// </value>
        public DateTime TargetEndDate { get; set; } 
        
        /// <summary>
        /// Gets or sets the balance.
        /// </summary>
        /// <value>
        /// The balance.
        /// </value>
        public double Balance {get; set; } 
        
        /// <summary>
        /// Gets or sets the interest rate.
        /// </summary>
        /// <value>
        /// The interest rate.
        /// </value>
        public double InterestRate {get; set;} 
        
        /// <summary>
        /// Gets or sets the minimum repayment amount.
        /// </summary>
        /// <value>
        /// The minimum repayment amount.
        /// </value>
        public double MinRepaymentAmount {get;set;}
        
        /// <summary>
        /// Gets or sets the minimum repayment day.
        /// </summary>
        /// <value>
        /// The minimum repayment day.
        /// </value>
        public int MinRepaymentDay { get; set;} 
                
        /// <summary>
        /// Gets or sets the extra repayment amount.
        /// </summary>
        /// <value>
        /// The extra repayment amount.
        /// </value>
        public double ExtraRepaymentAmount { get; set;}
        
        /// <summary>
        /// Gets or sets the extra repayment day.
        /// </summary>
        /// <value>
        /// The extra repayment day.
        /// </value>
        public int ExtraRepaymentDay { get; set; }
    }
}
