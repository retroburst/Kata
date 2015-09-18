using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kata.LoanPrediction.CSharp.Common.Models
{
    /// <summary>
    /// Transaction types.
    /// </summary>
    public enum TransactionType
    {
        [Description("Minimum Repayment")]
        MinimumRepayment,
        [Description("Extra Repayment")]
        ExtraRepayment,
        [Description("Interest Charged")]
        InterestCharged,
        [Description("Final Repayment")]
        FinalRepayment
    }
}
