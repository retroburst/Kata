//
//  LoanCalculationOutput.h
//  Kata.LoanPrediction.C++
//
//  Created by Andrew Dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanCalculationOutput__
#define __Kata_LoanPrediction_C____LoanCalculationOutput__

#include <stdio.h>
#include <vector>
#include "Global.h"
#include "LoanTransaction.h"

using namespace std;

class LoanCalculationOutput
{
public:
    LoanCalculationOutput();
    ~ LoanCalculationOutput();
    LoanCalculationOutput(dateTime interestStartDate, dateTime loanEndsDate, float totalInterestPaid);
    dateTime getInterestStartDate();
    void setInterestStartDate(dateTime source);
    dateTime getLoanEndsDate();
    void setLoanEndsDate(dateTime source);
    float getTotalInterestPaid();
    void setTotalInterestPaid(float source);
    vector<LoanTransaction> getTransaction();
    
private:
    dateTime interestStartDate;
    dateTime loanEndsDate;
    float totalInterestPaid;
    vector<LoanTransaction> transactions;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanCalculationOutput__) */
