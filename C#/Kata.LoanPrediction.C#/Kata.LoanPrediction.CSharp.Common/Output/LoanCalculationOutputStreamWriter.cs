using Kata.LoanPrediction.CSharp.Common.Models;
using Kata.LoanPrediction.CSharp.Common.Extensions;
using Kata.LoanPrediction.CSharp.Common.Helpers;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kata.LoanPrediction.CSharp.Common.Output
{
    /// <summary>
    /// Writes calculation output to a stream.
    /// </summary>
    public class LoanCalculationOutputStreamWriter
    {
        private LoanContext context = null;
        private LoanCalculationOutput output = null;

        /// <summary>
        /// Initializes a new instance of the <see cref="LoanCalculationOutputStreamWriter"/> class.
        /// </summary>
        /// <param name="context">The context.</param>
        /// <param name="output">The output.</param>
        public LoanCalculationOutputStreamWriter(LoanContext context, LoanCalculationOutput output)
        {
            this.context = context;
            this.output = output;
        }

        /// <summary>
        /// Writets the calculations.
        /// </summary>
        /// <param name="stream">The stream.</param>
        public void WritetCalculations(Stream stream)
        {
            using (StreamWriter streamWriter = new StreamWriter(stream))
            {
                using (TextWriter writer = TextWriter.Synchronized(streamWriter))
                {
                    WritetCalculations(writer);
                }
            }
        }

        /// <summary>
        /// Writets the calculations.
        /// </summary>
        /// <param name="stream">The stream.</param>
        public void WritetCalculations(TextWriter writer)
        {
            DateTime targetEndDate = context.TargetEndDate;
            StringBuilder sb = new StringBuilder();
            foreach (LoanTransaction t in output.Transactions)
            {
                DateTime transactionDate = t.Date;
                bool isTargetDate = transactionDate.Year == targetEndDate.Year && transactionDate.Month == targetEndDate.Month;

                if (isTargetDate) sb.AppendFormat("{0, -3}", "^T ");
                else sb.AppendFormat("{0, -3}", string.Empty);
                sb.AppendFormat("{0,-11}", transactionDate.ToString(Constants.DATE_FORMAT));
                sb.AppendFormat("{0, -3}", " - ");
                sb.AppendFormat("{0, -17}", EnumerationHelpers.GetDescription(t.Type));
                sb.AppendFormat("{0, -3}", " -");
                sb.AppendFormat(" Credit: {0, 9}", t.Credit.ToString("c"));
                sb.AppendFormat(" Debit: {0, 9}", t.Debit.ToString("c"));
                sb.AppendFormat(" Balance: {0, 9}", t.Balance.ToString("c"));
                sb.AppendLine();
            }

            sb.AppendFormat("Loan is paid off on {0}, total interest paid from {1} to {2} is {3}.",
                output.LoanEndsDate.ToString(Constants.DATE_FORMAT),
                output.InterestStartDate.ToString(Constants.DATE_FORMAT),
                output.LoanEndsDate.ToString(Constants.DATE_FORMAT),
                output.TotalInterestPaid.ToString("c"));
            sb.AppendLine();

            if (output.TargetEndDateHit) sb.AppendFormat("Target end date of {0} was hit perfectly.", context.TargetEndDate.ToString(Constants.DATE_FORMAT));
            else sb.AppendFormat("Target end date of {0} was missed by {1} days.", context.TargetEndDate.ToString(Constants.DATE_FORMAT), output.TargetEndDateMissedInDays);
            sb.AppendLine();
            writer.Write(sb.ToString());
        }

        /// <summary>
        /// Writes the output header.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <param name="programName">Name of the program.</param>
        public void WriteOutputHeader(Stream stream, string programName)
        {
            using (StreamWriter streamWriter = new StreamWriter(stream))
            {
                using (TextWriter writer = TextWriter.Synchronized(streamWriter))
                {
                    WriteOutputHeader(writer, programName);
                }
            }
        }

        /// <summary>
        /// Writes the output header.
        /// </summary>
        /// <param name="writer">The writer.</param>
        /// <param name="programName">Name of the program.</param>
        public void WriteOutputHeader(TextWriter writer, string programName)
        {
            StringBuilder sb = new StringBuilder();

            sb.AppendLine(programName);
            sb.AppendLine();
            sb.AppendLineFormat("Today's Date: {0}", context.TodaysDate.ToString(Constants.DATE_FORMAT));
            sb.AppendLineFormat("Start Date: {0}", context.StartDate.ToString(Constants.DATE_FORMAT));
            sb.AppendLineFormat("Target End Date: {0}", context.TargetEndDate.ToString(Constants.DATE_FORMAT));
            sb.AppendLineFormat("Balance: {0}", context.Balance.ToString("c"));
            sb.AppendLineFormat("Interest Rate: {0}%", context.InterestRate.ToString("n2"));
            sb.AppendLineFormat("Min. Repayment Amount: {0}", context.MinRepaymentAmount.ToString("c"));
            sb.AppendLineFormat("Min. Repayment Day: {0}", context.MinRepaymentDay);
            sb.AppendLineFormat("Extra Repayment Amount: {0}", context.ExtraRepaymentAmount.ToString("c"));
            sb.AppendLineFormat("Extra Repayment Day: {0}", context.ExtraRepaymentDay);
            sb.AppendLine();
            sb.AppendLine();
            writer.Write(sb.ToString());
        }

    }
}
