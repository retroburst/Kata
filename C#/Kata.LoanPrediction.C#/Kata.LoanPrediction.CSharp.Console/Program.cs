using Kata.LoanPrediction.CSharp.Common;
using Kata.LoanPrediction.CSharp.Common.Calculator;
using Kata.LoanPrediction.CSharp.Common.Models;
using Kata.LoanPrediction.CSharp.Common.Output;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Kata.LoanPrediction.CSharp.Console
{
    /// <summary>
    /// Represents the console program.
    /// </summary>
    public class Program
    {
        private const int EXPECTED_ARGUMENT_COUNT = 8;
        private static string programName = System.AppDomain.CurrentDomain.FriendlyName;

        /// <summary>
        /// Entry point for program.
        /// </summary>
        /// <param name="args">The arguments.</param>
        public static void Main(string[] args)
        {
            LoanContext context = null;
            LoanCalculator calculator = null;
            LoanCalculationOutput output = null;
            LoanCalculationOutputStreamWriter writer = null;
            try
            {
            	// clean the program name
            	programName = programName.Replace(".exe",  string.Empty);
            	// check we have the required number of arguments
                if(args.Length != EXPECTED_ARGUMENT_COUNT)
                {
                    PrintUsage();
                    return;
                }
				string outputFilename = BuildOutputFilename();
                context = new LoanContext();
                ProcessArguments(args, context);
                context.TodaysDate = DateTime.Now;
                calculator = new LoanCalculator(context);
                output = calculator.Calculate();
                writer = new LoanCalculationOutputStreamWriter(context, output);

                using(StreamWriter fs = new StreamWriter(new FileStream(outputFilename, FileMode.Create)))
                {
                    writer.WriteOutputHeader(fs, programName);
                    writer.WritetCalculations(fs);
                }

                writer.WriteOutputHeader(System.Console.Out, programName);
                writer.WritetCalculations(System.Console.Out);
                System.Console.WriteLine(string.Format("Ouput written to file '{0}'.", outputFilename));
            }
            catch (Exception ex)
            {
                System.Console.WriteLine(string.Format("Exception occurred: {0}", ex.Message));
                System.Console.WriteLine(string.Format("\n\n{0}", ex.StackTrace));
            }
        }

        /// <summary>
        /// Processes the arguments.
        /// </summary>
        /// <param name="args">The arguments.</param>
        /// <param name="context">The context.</param>
        private static void ProcessArguments(string[] args, LoanContext context)
        {
            context.StartDate = DateTime.ParseExact(args[0], Constants.DATE_FORMAT, CultureInfo.InvariantCulture);
            context.TargetEndDate = DateTime.ParseExact(args[1], Constants.DATE_FORMAT, CultureInfo.InvariantCulture);
            context.Balance = double.Parse(args[2]);
            context.InterestRate = double.Parse(args[3]);
            context.MinRepaymentAmount = double.Parse(args[4]);
            context.MinRepaymentDay = int.Parse(args[5]);
            context.ExtraRepaymentAmount = double.Parse(args[6]);
            context.ExtraRepaymentDay = int.Parse(args[7]);
        }

        /// <summary>
        /// Prints the usage.
        /// </summary>
        private static void PrintUsage()
        {
            System.Console.WriteLine(string.Format("Usage: {0} startDate(dd/mm/yyyy) targetEndDate(dd/mm/yyyy) "
                   + "balance interestRate minRepayAmount "
                   + "minRepayDay extraRepayAmount extraRepayDay\n"
                   + "Example: {0} 23/12/2015 23/12/2018 20000.00 5.74 1500.00 18 1200.00 15", programName));
        }
		
		/// <summary>
		/// Builds the output filename.
		/// </summary>
		/// <returns>The output filename.</returns>
		private static string BuildOutputFilename()
		{
			return(string.Format("{0}.{1}.{2}.{3}.out.txt", 
			              programName, 
			              DateTime.Now.Year.ToString("0000"), 
			              DateTime.Now.Month.ToString("00"), 
			              DateTime.Now.Day.ToString("00")));
		}

    }
}
