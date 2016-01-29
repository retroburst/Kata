using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Kata.LoanPrediction.CSharp.MVC.Models;
using Kata.LoanPrediction.CSharp.Common.Calculator;
using Kata.LoanPrediction.CSharp.Common.Models;

namespace Kata.LoanPrediction.CSharp.MVC.Controllers
{
    //TODO: store last used values on form per user (IP Address)
    //TODO: comment the code and refactor / make pretty

    /// <summary>
    /// Home controller, used by default index routes.
    /// </summary>
    public class HomeController : Controller
    {
        /// <summary>
        /// Returns the index - initial page.
        /// </summary>
        /// <returns></returns>
        public ActionResult Index()
        {
            return View(new LoanContextModel());
        }

        /// <summary>
        /// Calculate loan action.
        /// </summary>
        /// <param name="model"></param>
        /// <returns></returns>
        public ActionResult CalculateLoan(LoanContextModel model)
        {
            if (ModelState.IsValid)
            {
                LoanCalculator calculator = new LoanCalculator(model.ToLoanContext());
                LoanCalculationOutput output = calculator.Calculate();
                return (View(new LoanCalculationResultsModel(model, output)));
            }
            else
            {
                return (View("Index", model));
            }
        }

    }
}