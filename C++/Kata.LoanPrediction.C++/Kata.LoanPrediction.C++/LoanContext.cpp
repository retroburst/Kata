//
//  LoanContext.cpp
//  Kata.LoanPrediction.C++
//
//  Created by retroburst [Andrew D] on 3/09/2015.
//  Copyright (c) 2015 retroburst [Andrew D]. All rights reserved.
//

#include "LoanContext.h"

/*
 ***************************************
 ** Default constructor.
 ***************************************
 */
LoanContext::LoanContext()
{ }

/*
 ***************************************
 ** Constructor.
 ***************************************
 */
LoanContext::LoanContext(dateTime startDate, dateTime targetEndDate, dateTime todaysDate,
                         double balance, double interestRate, double minRepaymentAmount,
                         int minRepaymentDay, double extraRepaymentAmount, int extraRepaymentDay)
{
    this->startDate = startDate;
    this->targetEndDate = targetEndDate;
    this->todaysDate = todaysDate;
    this->balance = balance;
    this->interestRate = interestRate;
    this->minRepaymentAmount = minRepaymentAmount;
    this->minRepaymentDay = minRepaymentDay;
    this->extraRepaymentAmount = extraRepaymentAmount;
    this->extraRepaymentDay = extraRepaymentDay;
}

/*
 ***************************************
 ** Get start date.
 ***************************************
 */
dateTime LoanContext::getStartDate()
{
    return(startDate);
}

/*
 ***************************************
 ** Set start date.
 ***************************************
 */
void LoanContext::setStartDate(dateTime source)
{
    startDate = source;
}

/*
 ***************************************
 ** Get target end date.
 ***************************************
 */
dateTime LoanContext::getTargetEndDate()
{
    return(targetEndDate);
}

/*
 ***************************************
 ** Set target end date.
 ***************************************
 */
void LoanContext::setTargetEndDate(dateTime source)
{
    targetEndDate = source;
}

/*
 ***************************************
 ** Get today's date.
 ***************************************
 */
dateTime LoanContext::getTodaysDate()
{
    return(todaysDate);
}

/*
 ***************************************
 ** Set today's date.
 ***************************************
 */
void LoanContext::setTodaysDate(dateTime source)
{
    todaysDate = source;
}

/*
 ***************************************
 ** Get balance.
 ***************************************
 */
double LoanContext::getBalance()
{
    return(balance);
}

/*
 ***************************************
 ** Set balance.
 ***************************************
 */
void LoanContext::setBalance(double source)
{
    balance = source;
}

/*
 ***************************************
 ** Get interest rate.
 ***************************************
 */
double LoanContext::getInterestRate()
{
    return(interestRate);
}

/*
 ***************************************
 ** Set interest rate.
 ***************************************
 */
void LoanContext::setInterestRate(double source)
{
    interestRate = source;
}

/*
 ***************************************
 ** Get min. repayment amount.
 ***************************************
 */
double LoanContext::getMinRepaymentAmount()
{
    return(minRepaymentAmount);
}

/*
 ***************************************
 ** Set min. repayment amount.
 ***************************************
 */
void LoanContext::setMinRepaymentAmount(double source)
{
    minRepaymentAmount = source;
}

/*
 ***************************************
 ** Get min. repayment day.
 ***************************************
 */
int LoanContext::getMinRepaymentDay()
{
    return(minRepaymentDay);
}

/*
 ***************************************
 ** Set min. repayment day.
 ***************************************
 */
void LoanContext::setMinRepaymentDay(int source)
{
    minRepaymentDay = source;
}

/*
 ***************************************
 ** Get extra repayment amount.
 ***************************************
 */
double LoanContext::getExtraRepaymentAmount()
{
    return(extraRepaymentAmount);
}

/*
 ***************************************
 ** Set extra repayment amount.
 ***************************************
 */
void LoanContext::setExtraRepaymentAmount(double source)
{
    extraRepaymentAmount = source;
}

/*
 ***************************************
 ** Get extra repayment day.
 ***************************************
 */
int LoanContext::getExtraRepaymentDay()
{
    return(extraRepaymentDay);
}

/*
 ***************************************
 ** Set extra repayment day.
 ***************************************
 */
void LoanContext::setExtraRepaymentDay(int source)
{
    extraRepaymentDay = source;    
}
