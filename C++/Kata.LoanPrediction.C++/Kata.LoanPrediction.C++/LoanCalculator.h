//
//  LoanCalculator.h
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanCalculator__
#define __Kata_LoanPrediction_C____LoanCalculator__

#include <stdio.h>
#include "Global.h"
#include "LoanContext.h"
#include "LoanCalculationOutput.h"

/*
 ***************************************
 ** Calculates the loan from start date
 ** to the point the loan is paid off.
 ** Takes a LoanContext as input and
 ** outputs a LoanCalculationOutput
 ** result object.
 ***************************************
 */
class LoanCalculator
{
public:
    LoanCalculator(LoanContext context);
    LoanCalculationOutput calculateLoan();
private:
    LoanContext context;
    LoanCalculationOutput output;
    void processEndOfMonth(dateTime currentDate, double &monthlyInterest, double &balance, LoanCalculationOutput &output);
    void processExtraRepayment(double &balance, double extraRepaymentAmount, dateTime currentDate, LoanCalculationOutput &output);
    void processMinRepayment(double &balance, double minRepaymentAmount, dateTime &currentDate, double monthlyInterest, LoanCalculationOutput &output);
    double calculateDailyInterest(double balance, double interestRate);
    LoanTransaction createTransaction(string type, dateTime date, double repayment, double charge, double balance);
    void setTargetEndDateAccuracy(dateTime actualEndDate, dateTime targetEndDate, LoanCalculationOutput &output);
    void formatDate(dateTime target, const char *dateFormat, char *buffer, int bufferSize);
};

#endif /* defined(__Kata_LoanPrediction_C____LoanCalculator__) */
