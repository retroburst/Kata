using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kata.LoanPrediction.CSharp.Common.Extensions
{
    /// <summary>
    /// String builder extensions methods.
    /// </summary>
    public static class StringBuilderExtensions
    {
        /// <summary>
        /// Appends a line with format.
        /// </summary>
        /// <param name="target">The target.</param>
        /// <param name="format">The format.</param>
        /// <param name="args">The arguments.</param>
        public static void AppendLineFormat(this StringBuilder target, string format, params object[] args)
        {
            target.AppendFormat(format, args);
            target.AppendLine();
        }
    }
}
