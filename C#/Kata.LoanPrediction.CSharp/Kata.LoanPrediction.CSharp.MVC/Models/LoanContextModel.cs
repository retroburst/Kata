using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;
using Kata.LoanPrediction.CSharp.Common.Models;

namespace Kata.LoanPrediction.CSharp.MVC.Models
{
    /// <summary>
    /// Represents a loan context
    /// for use in MVC project.
    /// </summary>
    public class LoanContextModel
    {
        /// <summary>
        /// Default constructor.
        /// </summary>
        public LoanContextModel()
        {
            TodaysDate = DateTime.Now;
            StartDate = DateTime.Now;
            ExtraRepaymentAmount = 0.00d;
            ExtraRepaymentDay = 1;
            MinRepaymentAmount = 0.00d;
            MinRepaymentDay = 1;
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
        [Required]
        [Display(Name = "Start Date")]
        public DateTime StartDate { get; set; }

        /// <summary>
        /// Gets or sets the target end date.
        /// </summary>
        /// <value>
        /// The target end date.
        /// </value>
        [Required]
        [Display(Name = "Target End Date")]
        public DateTime TargetEndDate { get; set; }

        /// <summary>
        /// Gets or sets the balance.
        /// </summary>
        /// <value>
        /// The balance.
        /// </value>
        [Required]
        [Display(Name = "Balance")]
        public double Balance { get; set; }

        /// <summary>
        /// Gets or sets the interest rate.
        /// </summary>
        /// <value>
        /// The interest rate.
        /// </value>
        [Required]
        [Display(Name = "Interest Rate")]
        public double InterestRate { get; set; }

        /// <summary>
        /// Gets or sets the minimum repayment amount.
        /// </summary>
        /// <value>
        /// The minimum repayment amount.
        /// </value>
        [Required]
        [Display(Name = "Minimum Repayment Amount")]
        public double MinRepaymentAmount { get; set; }

        /// <summary>
        /// Gets or sets the minimum repayment day.
        /// </summary>
        /// <value>
        /// The minimum repayment day.
        /// </value>
        [Required]
        [Display(Name = "Minimum Repayment Day")]
        public int MinRepaymentDay { get; set; }

        /// <summary>
        /// Gets or sets the extra repayment amount.
        /// </summary>
        /// <value>
        /// The extra repayment amount.
        /// </value>
        [Display(Name = "Extra Repayment Amount")]
        [Required]
        public double ExtraRepaymentAmount { get; set; }

        /// <summary>
        /// Gets or sets the extra repayment day.
        /// </summary>
        /// <value>
        /// The extra repayment day.
        /// </value>
        [Display(Name = "Extra Repayment Day")]
        [Required]
        public int ExtraRepaymentDay { get; set; }

        /// <summary>
        /// Converts this model to a loan context 
        /// for use by common library.
        /// </summary>
        /// <returns></returns>
        public LoanContext ToLoanContext()
        {
            LoanContext result = new LoanContext(TodaysDate, StartDate, TargetEndDate, Balance, InterestRate, MinRepaymentAmount, MinRepaymentDay, ExtraRepaymentAmount, ExtraRepaymentDay);
            return (result);
        }

    }
}
