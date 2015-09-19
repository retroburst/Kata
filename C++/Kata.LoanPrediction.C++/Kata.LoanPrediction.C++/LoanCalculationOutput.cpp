//
//  LoanCalculationOutput.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "LoanCalculationOutput.h"

/*
 ***************************************
 ** Default constructor.
 ***************************************
 */
LoanCalculationOutput::LoanCalculationOutput()
{
    this->interestStartDate = *DATETIME_EMPTY;
    this->loanEndsDate = *DATETIME_EMPTY;
    this->totalInterestPaid = 0.0;
    this->targetEndDateHit = false;
    this->targetEndDateMissedInDays = 0;
}

/*
 ***************************************
 ** Constructor with initial arguments.
 ***************************************
 */
LoanCalculationOutput::LoanCalculationOutput(dateTime interestStartDate, dateTime loanEndsDate, double totalInterestPaid, bool targetEndDateHit, int targetEndDateMissedInDays)
{
    this->interestStartDate = interestStartDate;
    this->loanEndsDate = loanEndsDate;
    this->totalInterestPaid = totalInterestPaid;
    this->targetEndDateHit = targetEndDateHit;
    this->targetEndDateMissedInDays = targetEndDateMissedInDays;
}

/*
 ***************************************
 ** Gets the interest start date.
 ***************************************
 */
dateTime LoanCalculationOutput::getInterestStartDate()
{
    return(interestStartDate);
}

/*
 ***************************************
 ** Set the interest start date.
 ***************************************
 */
void LoanCalculationOutput::setInterestStartDate(dateTime source)
{
    interestStartDate = source;
}

/*
 ***************************************
 ** Gets the loan end date.
 ***************************************
 */
dateTime LoanCalculationOutput::getLoanEndsDate()
{
    return(loanEndsDate);
}

/*
 ***************************************
 ** Sets the loan end date.
 ***************************************
 */
void LoanCalculationOutput::setLoanEndsDate(dateTime source)
{
    loanEndsDate = source;
}

/*
 ***************************************
 ** Gets the total interest paid.
 ***************************************
 */
double LoanCalculationOutput::getTotalInterestPaid()
{
    return(totalInterestPaid);
}

/*
 ***************************************
 ** Sets the total interest paid.
 ***************************************
 */
void LoanCalculationOutput::setTotalInterestPaid(double source)
{
    totalInterestPaid = source;
}

/*
 ***************************************
 ** Gets the target end date hit.
 ***************************************
 */
bool LoanCalculationOutput::getTargetEndDateHit()
{
    return(targetEndDateHit);
}

/*
 ***************************************
 ** Sets the target end date hit.
 ***************************************
 */
void LoanCalculationOutput::setTargetEndDateHit(bool source)
{
    targetEndDateHit = source;
}

/*
 ***************************************
 ** Gets the number of days the target
 ** end date missed.
 ***************************************
 */
int LoanCalculationOutput::getTargetEndDateMissedInDays()
{
    return(targetEndDateMissedInDays);
}

/*
 ***************************************
 ** Sets the number of days the target 
 ** end date missed.
 ***************************************
 */
void LoanCalculationOutput::setTargetEndDateMissedInDays(int source)
{
    targetEndDateMissedInDays = source;
}

/*
 ***************************************
 ** Adds a transaction.
 ***************************************
 */
void LoanCalculationOutput::addTransaction(LoanTransaction transaction)
{
    transactions.push_back(transaction);
}

/*
 ***************************************
 ** Gets a const pointer to a const 
 ** vector of transactions.
 ***************************************
 */
const vector<LoanTransaction>* const LoanCalculationOutput::getTransactionList()
{
    return(&transactions);
}
