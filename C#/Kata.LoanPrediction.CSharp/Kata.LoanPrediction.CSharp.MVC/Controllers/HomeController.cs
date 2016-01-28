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
    //TODO: extra repayment info should be optional - in core model and MVC models - defaults for extra should be removed
    //TODO: default dates in model are not showing in the combodate fields on initial load
    //TODO: mandatory field marks e.g. (*)

    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View(new LoanContextModel());
        }

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