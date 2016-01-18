var kataLoanPredictionApp = function() {
    
    ///////////////////////////////////////////////////////
    // models
    var kataLoanPredictionModels = function() {
        
        function loanContext() {
            this.todaysDate = null;
            this.startDate = null;
            this.targetEndDate = null;
            this.balance = 0.0;
            this.interestRate = 0.0;
            this.minRepaymentAmount = 0.0;
            this.minRepaymentDay = 0;
            this.extraRepaymentAmount = 0.0;
            this.extraRepaymentDay = 0;
        }
        
        function loanTransaction() {
            this.date = null;
            this.type = null;
            this.credit = 0.0;
            this.debit = 0.0;
            this.balance = 0.0;
        }
        
        function loanCalculationOutput() {
            this.transactions = null;
            this.interestStartDate = null;
            this.loanEndsDate = null;
            this.totalInterestPaid = null;
            this.targetEndDateHit = false;
            this.targetEndDateMissedInDays = 0;
        }
        
        return  ({
                 loanContext: loanContext,
                 loanTransaction: loanTransaction,
                 loanCalculationOutput: loanCalculationOutput
                 });
    }();
    
    ///////////////////////////////////////////////////////
    // constants
    var kataLoanPredictionConstants = function() {
        
        var constants = {
            NUM_DAYS_IN_YEAR : 365,
            DATE_FORMAT : "dd/MM/yyyy"
        };
        
        return  ({
                 get : function(constantName){
                 return(constants[constantName]);
                 }
                 });
    }();
    
    ///////////////////////////////////////////////////////
    // enums
    var kataLoanPredicitionEnums = function() {
        
        var transactionTypes = {
        minimumRepayment: {
        code: 100,
        description: "Minimum Repayment"
        },
        extraRepayment: {
        code: 101,
        description: "Extra Repayment"
        },
        interestCharged: {
        code: 102,
        description: "Interest Charged"
        },
        finalRepayment: {
        code: 103,
        description: "Final Repayment"
        }
        };
        
        return ({
                transactionTypes: transactionTypes
                });
    }();
    
    ///////////////////////////////////////////////////////
    // calculator
    var kataLoanPredictionCalculator = function()
    {
        var calculate = function(context){
            var result = new kataLoanPredictionModels.loanCalculationOutput();
            var firstIteration = true;
            var balance = context.balance;
            var monthlyInterest = 0.0;
            
            
            
            
            
        };
        
        return({
                calculate : calculate
                });
    }();
    
    ///////////////////////////////////////////////////////
    // returns public interface to the app
    return({
           calculator : kataLoanPredictionCalculator
            });
}();