using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Kata.LoanPrediction.CSharp.Common.Helpers;
using Kata.LoanPrediction.CSharp.Common.Models;

namespace Kata.LoanPrediction.CSharp.MVC.Application
{
    /// <summary>
    /// Helper methods for Razor views.
    /// </summary>
    public class RazorViewHelpers
    {
        /// <summary>
        /// Combines a view title and a base site title safely.
        /// The view title can safely be null or empty.
        /// </summary>
        /// <param name="viewTitle"></param>
        /// <param name="titleJoiner"></param>
        /// <param name="baseTitle"></param>
        /// <returns></returns>
        public static string CombineTitle(string viewTitle, string titleJoiner, string baseTitle)
        {
            string result = baseTitle;
            if(!string.IsNullOrEmpty(viewTitle))
            {
                result = viewTitle + titleJoiner + result;
            }
            return (result);
        }

        /// <summary>
        /// Formats a date for output.
        /// </summary>
        /// <param name="target"></param>
        /// <returns></returns>
        public static string FormatDate(DateTime target)
        {
            string result = target.ToShortDateString();
            return (result);
        }

        /// <summary>
        /// Formats a number as currency for output.
        /// </summary>
        /// <param name="target"></param>
        /// <returns></returns>
        public static string FormatCurrency(double target)
        {
            string result = target.ToString("c");
            return (result);
        }

        /// <summary>
        /// Formats a transaction type for output.
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        public static string FormatTransactionType(TransactionType type)
        {
            return(EnumerationHelpers.GetDescription(type));
        }
    }
}
