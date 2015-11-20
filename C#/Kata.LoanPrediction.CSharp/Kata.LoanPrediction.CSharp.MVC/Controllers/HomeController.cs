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
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View(new LoanContextModel());
        }

        public ActionResult CalculateLoan(LoanContextModel model)
        {
            LoanCalculator calculator = new LoanCalculator(model.ToLoanContext());
            LoanCalculationOutput output = calculator.Calculate();
            return (View(new LoanCalculationResultsModel(model, output)));
        }

    }
}