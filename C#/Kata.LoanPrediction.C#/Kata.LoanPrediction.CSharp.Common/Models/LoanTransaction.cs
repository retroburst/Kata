using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kata.LoanPrediction.CSharp.Common.Models
{
    /// <summary>
    /// Represents a loan transaction.
    /// </summary>
    public class LoanTransaction
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="LoanTransaction"/> class.
        /// </summary>
        public LoanTransaction()
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="LoanTransaction"/> class.
        /// </summary>
        /// <param name="date">The date.</param>
        /// <param name="type">The type.</param>
        /// <param name="credit">The credit.</param>
        /// <param name="debit">The debit.</param>
        /// <param name="balance">The balance.</param>
        public LoanTransaction(DateTime date, TransactionType type, double credit, double debit, double balance)
        {
            Date = date;
            Type = type;
            Credit = credit;
            Debit = debit;
            Balance = balance;
        }

        /// <summary>
        /// Gets or sets the date.
        /// </summary>
        /// <value>
        /// The date.
        /// </value>
        public DateTime Date { get; set; }

        /// <summary>
        /// Gets or sets the type.
        /// </summary>
        /// <value>
        /// The type.
        /// </value>
        public TransactionType Type { get; set; }

        /// <summary>
        /// Gets or sets the credit.
        /// </summary>
        /// <value>
        /// The credit.
        /// </value>
        public double Credit { get; set; }

        /// <summary>
        /// Gets or sets the debit.
        /// </summary>
        /// <value>
        /// The debit.
        /// </value>
        public double Debit { get; set; }

        /// <summary>
        /// Gets or sets the balance.
        /// </summary>
        /// <value>
        /// The balance.
        /// </value>
        public double Balance { get; set; }
    }
}
