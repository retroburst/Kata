//
//  LoanCalculationOutput.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "LoanCalculationOutput.h"

LoanCalculationOutput::LoanCalculationOutput()
{
    this->interestStartDate = *DATETIME_EMPTY;
    this->loanEndsDate = *DATETIME_EMPTY;
    this->totalInterestPaid = 0.0f;
    this->targetEndDateHit = false;
    this->targetEndDateMissedInDays = 0;
}

LoanCalculationOutput::~LoanCalculationOutput()
{

}

LoanCalculationOutput::LoanCalculationOutput(dateTime interestStartDate, dateTime loanEndsDate, float totalInterestPaid, bool targetEndDateHit, int targetEndDateMissedInDays)
{
    this->interestStartDate = interestStartDate;
    this->loanEndsDate = loanEndsDate;
    this->totalInterestPaid = totalInterestPaid;
    this->targetEndDateHit = targetEndDateHit;
    this->targetEndDateMissedInDays = targetEndDateMissedInDays;
}

dateTime LoanCalculationOutput::getInterestStartDate()
{
    return(interestStartDate);
}

void LoanCalculationOutput::setInterestStartDate(dateTime source)
{
    interestStartDate = source;
}

dateTime LoanCalculationOutput::getLoanEndsDate()
{
    return(loanEndsDate);
}

void LoanCalculationOutput::setLoanEndsDate(dateTime source)
{
    loanEndsDate = source;
}

float LoanCalculationOutput::getTotalInterestPaid()
{
    return(totalInterestPaid);
}

void LoanCalculationOutput::setTotalInterestPaid(float source)
{
    totalInterestPaid = source;
}

bool LoanCalculationOutput::getTargetEndDateHit()
{
    return(targetEndDateHit);
}

void LoanCalculationOutput::setTargetEndDateHit(bool source)
{
    targetEndDateHit = source;
}

int LoanCalculationOutput::getTargetEndDateMissedInDays()
{
    return(targetEndDateMissedInDays);
}

void LoanCalculationOutput::setTargetEndDateMissedInDays(int source)
{
    targetEndDateMissedInDays = source;
}

void LoanCalculationOutput::addTransaction(LoanTransaction transaction)
{
    transactions.push_back(transaction);
}

const vector<LoanTransaction>* const LoanCalculationOutput::getTransactionList()
{
    return(&transactions);
}
