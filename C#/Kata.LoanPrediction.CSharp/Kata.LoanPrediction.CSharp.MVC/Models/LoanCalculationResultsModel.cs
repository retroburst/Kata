using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Kata.LoanPrediction.CSharp.Common.Models;

namespace Kata.LoanPrediction.CSharp.MVC.Models
{
    /// <summary>
    /// Bundles context and output as
    /// a calculation results model.
    /// </summary>
    public class LoanCalculationResultsModel
    {
        public LoanContextModel Context { get; set; }
        public LoanCalculationOutput Output { get; set; }

        /// <summary>
        /// Default constructor.
        /// </summary>
        /// <param name="context"></param>
        /// <param name="output"></param>
        public LoanCalculationResultsModel(LoanContextModel context, LoanCalculationOutput output)
        {
            Context = context;
            Output = output;
        }
    }
}
