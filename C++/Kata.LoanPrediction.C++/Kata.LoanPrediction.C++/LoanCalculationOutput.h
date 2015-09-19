//
//  LoanCalculationOutput.h
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanCalculationOutput__
#define __Kata_LoanPrediction_C____LoanCalculationOutput__

#include <stdio.h>
#include <vector>
#include "Global.h"
#include "LoanTransaction.h"

using namespace std;

/*
 ***************************************
 ** Output from the loan calculator.
 ***************************************
 */
class LoanCalculationOutput
{
public:
    LoanCalculationOutput();
    LoanCalculationOutput(dateTime interestStartDate, dateTime loanEndsDate, double totalInterestPaid, bool targetEndDateHit, int targetEndDateMissedInDays);
    dateTime getInterestStartDate();
    void setInterestStartDate(dateTime source);
    dateTime getLoanEndsDate();
    void setLoanEndsDate(dateTime source);
    double getTotalInterestPaid();
    void setTotalInterestPaid(double source);
    bool getTargetEndDateHit();
    void setTargetEndDateHit(bool source);
    int getTargetEndDateMissedInDays();
    void setTargetEndDateMissedInDays(int source);
    void addTransaction(LoanTransaction transaction);
    const vector<LoanTransaction>* const getTransactionList();
    
private:
    dateTime interestStartDate;
    dateTime loanEndsDate;
    double totalInterestPaid;
    bool targetEndDateHit;
    int targetEndDateMissedInDays;
    void addTransaction();
    vector<LoanTransaction> transactions;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanCalculationOutput__) */
