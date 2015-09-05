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

class LoanCalculator
{
public:
    LoanCalculator(LoanContext context);
    ~LoanCalculator();
    LoanCalculationOutput calculateLoan();
private:
    LoanContext context;
    LoanCalculationOutput output;
    void processEndOfMonth(dateTime currentDate, float &monthlyInterest, float &principal, LoanCalculationOutput &output);
    void processExtraRepayment(float &principal, LoanContext context, dateTime currentDate, LoanCalculationOutput &output);
    void processMinRepayment(float &principal, LoanContext context, dateTime &currentDate, float monthlyInterest, LoanCalculationOutput &output);
    float calculateDailyInterest(float principal, float interestRate);
    LoanTransaction createTransaction(string type, dateTime date, float repayment, float charge, float remainPrincipal);
};

#endif /* defined(__Kata_LoanPrediction_C____LoanCalculator__) */
