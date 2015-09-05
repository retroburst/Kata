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

}

LoanCalculationOutput::~LoanCalculationOutput()
{

}

LoanCalculationOutput::LoanCalculationOutput(dateTime interestStartDate, dateTime loanEndsDate, float totalInterestPaid)
{
    this->interestStartDate = interestStartDate;
    this->loanEndsDate = loanEndsDate;
    this->totalInterestPaid = totalInterestPaid;
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

void LoanCalculationOutput::addTransaction(LoanTransaction transaction)
{
    transactions.push_back(transaction);
}

const vector<LoanTransaction>* const LoanCalculationOutput::getTransactionList()
{
    return(&transactions);
}
