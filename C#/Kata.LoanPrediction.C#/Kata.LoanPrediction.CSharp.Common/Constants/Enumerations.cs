using System;
using System.Collections.Generic;
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
        MinimumRepayment,
        ExtraRepayment,
        InterestCharged,
        FinalRepayment
    }
}
