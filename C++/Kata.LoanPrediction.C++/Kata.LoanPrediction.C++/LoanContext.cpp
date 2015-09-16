//
//  LoanContext.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
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
                         float balance, float interestRate, float minRepaymentAmount,
                         int minRepaymentDay, float extraRepaymentAmount, int extraRepaymentDay)
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
float LoanContext::getBalance()
{
    return(balance);
}

/*
 ***************************************
 ** Set balance.
 ***************************************
 */
void LoanContext::setBalance(float source)
{
    balance = source;
}

/*
 ***************************************
 ** Get interest rate.
 ***************************************
 */
float LoanContext::getInterestRate()
{
    return(interestRate);
}

/*
 ***************************************
 ** Set interest rate.
 ***************************************
 */
void LoanContext::setInterestRate(float source)
{
    interestRate = source;
}

/*
 ***************************************
 ** Get min. repayment amount.
 ***************************************
 */
float LoanContext::getMinRepaymentAmount()
{
    return(minRepaymentAmount);
}

/*
 ***************************************
 ** Set min. repayment amount.
 ***************************************
 */
void LoanContext::setMinRepaymentAmount(float source)
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
float LoanContext::getExtraRepaymentAmount()
{
    return(extraRepaymentAmount);
}

/*
 ***************************************
 ** Set extra repayment amount.
 ***************************************
 */
void LoanContext::setExtraRepaymentAmount(float source)
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
