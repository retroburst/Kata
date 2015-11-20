using Kata.LoanPrediction.CSharp.Common.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kata.LoanPrediction.CSharp.Common.Calculator
{
    /// <summary>
    /// Calculates the loan from start date
    /// to a point in time it is paid off.
    /// </summary>
    public class LoanCalculator
    {
        private LoanContext context = null;

        /// <summary>
        /// Initializes a new instance of the <see cref="LoanCalculator"/> class.
        /// </summary>
        /// <param name="context">The context.</param>
        public LoanCalculator(LoanContext context)
        {
            this.context = context;
        }

        /// <summary>
        /// Calculates the loan using the context.
        /// </summary>
        /// <returns></returns>
        public LoanCalculationOutput Calculate()
        {
            LoanCalculationOutput result = new LoanCalculationOutput();
            bool firstIteration = true;
            double balance = context.Balance;
            double monthlyInterest = 0.0d;
            DateTime currentDate = context.StartDate;
            // we will calculate interest from the first of the month
            DateTime calcInterestStartDate = new DateTime(currentDate.Year, currentDate.Month, 1);
            result.InterestStartDate = calcInterestStartDate;
            // loop through dates, caculating interest daily etc
            while (true)
            {
                // if min repay day
                if (currentDate.Day == context.MinRepaymentDay && balance > 0.0d)
                {
                    balance = ProcessMinRepayment(balance, context.MinRepaymentAmount, currentDate, monthlyInterest, result);
                }
                // if extra repay day
                if (currentDate.Day == context.ExtraRepaymentDay && context.ExtraRepaymentAmount > 0.0d && balance > 0.0d)
                {
                    balance = ProcessExtraRepayment(balance, context.ExtraRepaymentAmount, currentDate, result);
                }

                // if balance is zero or less - we are done!
                if (balance <= 0.0d)
                {
                    result.LoanEndsDate = currentDate;
                    break;
                }
                // calculate the daily interest
                monthlyInterest += CalculateDailyInterest(balance, context.InterestRate);
                // if this is the first iteration and we did not start on the first of the month
                // let's calculate the interest for the days back to the first
                if (firstIteration && context.StartDate.Day != 1)
                {
                    int daysToMonthStart = currentDate.Day - 1;
                    monthlyInterest += (monthlyInterest * daysToMonthStart);
                    firstIteration = false;
                }
                // move date forward
                DateTime nextDate = currentDate.AddDays(1);
                // if end of month
                if (currentDate.Month != nextDate.Month)
                {
                    balance = ProcessEndOfMonth(currentDate, monthlyInterest, balance, result);
                    // reset interest to zero
                    monthlyInterest = 0.0d;
                }
                currentDate = nextDate;
            }
            SetTargetEndDateAccuracy(result.LoanEndsDate, context.TargetEndDate, result);
            return (result);
        }

        /// <summary>
        /// Processes the end of month.
        /// </summary>
        /// <param name="currentDate">The current date.</param>
        /// <param name="monthlyInterest">The monthly interest.</param>
        /// <param name="balance">The balance.</param>
        /// <param name="result">The result.</param>
        private double ProcessEndOfMonth(DateTime currentDate, double monthlyInterest, double balance, LoanCalculationOutput result)
        {
            // add interest charged transaction
            balance += monthlyInterest;
            // calculate the total interest paid
            result.TotalInterestPaid += monthlyInterest;
            LoanTransaction transaction = new LoanTransaction(currentDate, TransactionType.InterestCharged, 0.0d, monthlyInterest, balance);
            result.Transactions.Add(transaction);
            return (balance);
        }

        /// <summary>
        /// Processes the extra repayment.
        /// </summary>
        /// <param name="balance">The balance.</param>
        /// <param name="extraRepaymentAmount">The extra repayment amount.</param>
        /// <param name="currentDate">The current date.</param>
        /// <param name="result">The result.</param>
        private double ProcessExtraRepayment(double balance, double extraRepaymentAmount, DateTime currentDate, LoanCalculationOutput result)
        {
            if(balance >= extraRepaymentAmount)
            {
                // add extra repay transaction (if amount is more than 0)
                balance -= extraRepaymentAmount;
                LoanTransaction transaction = new LoanTransaction(currentDate, TransactionType.ExtraRepayment, extraRepaymentAmount, 0.0d, balance);
                result.Transactions.Add(transaction);
            }
            return (balance);
        }

        /// <summary>
        /// Processes the minimum repayment.
        /// </summary>
        /// <param name="balance">The balance.</param>
        /// <param name="context">The context.</param>
        /// <param name="currentDate">The current date.</param>
        /// <param name="monthlyInterest">The monthly interest.</param>
        /// <param name="result">The result.</param>
        private double ProcessMinRepayment(double balance, double minRepaymentAmount, DateTime currentDate, double monthlyInterest, LoanCalculationOutput result)
        {
            // add min repay transaction
            if ((balance + monthlyInterest) <= minRepaymentAmount)
            {
                double finalRepayment = 0.0d;
                balance += monthlyInterest;
                finalRepayment = balance;
                balance -= finalRepayment;
                LoanTransaction transaction = new LoanTransaction(currentDate, TransactionType.FinalRepayment, finalRepayment, 0.0d, balance);
                result.Transactions.Add(transaction);
            }
            else
            {
                balance -= minRepaymentAmount;
                LoanTransaction transaction = new LoanTransaction(currentDate, TransactionType.MinimumRepayment, minRepaymentAmount, 0.0d, balance);
                result.Transactions.Add(transaction);
            }
            return (balance);
        }

        /// <summary>
        /// Calculates the daily interest.
        /// </summary>
        /// <param name="balance">The balance.</param>
        /// <param name="interestRate">The interest rate.</param>
        /// <returns></returns>
        private double CalculateDailyInterest(double balance, double interestRate)
        {
            double result = 0.0d;
            result = (balance * (interestRate / 100)) / Constants.NUM_DAYS_IN_YEAR;
            return (result);
        }

        /// <summary>
        /// Sets the target end date accuracy.
        /// </summary>
        /// <param name="actualEndDate">The actual end date.</param>
        /// <param name="targetEndDate">The target end date.</param>
        /// <param name="result">The result.</param>
        private void SetTargetEndDateAccuracy(DateTime actualEndDate, DateTime targetEndDate, LoanCalculationOutput result)
        {
            TimeSpan difference = actualEndDate - targetEndDate;
            result.TargetEndDateMissedInDays = Math.Abs((int)difference.TotalDays);
        }

    }
}
