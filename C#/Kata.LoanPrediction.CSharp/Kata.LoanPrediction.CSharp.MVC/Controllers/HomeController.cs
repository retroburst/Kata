using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Kata.LoanPrediction.CSharp.MVC.Models;

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

            return (new EmptyResult());
        }

    }
}