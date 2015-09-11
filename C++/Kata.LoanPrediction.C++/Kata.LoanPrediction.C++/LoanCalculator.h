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
    void printOutputHeader(LoanContext *context, ostream& out);
    void printCalculations(LoanContext *context, LoanCalculationOutput *output, ostream& out);
    string buildOutputFilename(dateTime currentDate);
private:
    LoanContext context;
    LoanCalculationOutput output;
    void processEndOfMonth(dateTime currentDate, float &monthlyInterest, float &balance, LoanCalculationOutput &output);
    void processExtraRepayment(float &balance, LoanContext context, dateTime currentDate, LoanCalculationOutput &output);
    void processMinRepayment(float &balance, LoanContext context, dateTime &currentDate, float monthlyInterest, LoanCalculationOutput &output);
    float calculateDailyInterest(float balance, float interestRate);
    LoanTransaction createTransaction(string type, dateTime date, float repayment, float charge, float balance);
    void setTargetEndDateAccuracy(dateTime actualEndDate, dateTime targetEndDate, LoanCalculationOutput &output);
    
    void formatDate(dateTime target, const char *dateFormat, char *buffer, int bufferSize);

    
};

#endif /* defined(__Kata_LoanPrediction_C____LoanCalculator__) */
