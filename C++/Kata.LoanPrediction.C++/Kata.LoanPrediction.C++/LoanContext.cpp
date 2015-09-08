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

LoanContext::LoanContext(dateTime startDate, dateTime targetEndDate, dateTime todaysDate, float balance, float interestRate, float minRepaymentAmount, int minRepaymentDay, float extraRepaymentAmount, int extraRepaymentDay)
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

LoanContext::~LoanContext()
{ }

dateTime LoanContext::getStartDate()
{
    return(startDate);
}

void LoanContext::setStartDate(dateTime source)
{
    startDate = source;
}


dateTime LoanContext::getTargetEndDate()
{
    return(targetEndDate);
}

void LoanContext::setTargetEndDate(dateTime source)
{
    targetEndDate = source;
}

dateTime LoanContext::getTodaysDate()
{
    return(todaysDate);
}

void LoanContext::setTodaysDate(dateTime source)
{
    todaysDate = source;
}

float LoanContext::getBalance()
{
    return(balance);
}

void LoanContext::setBalance(float source)
{
    balance = source;
}

float LoanContext::getInterestRate()
{
    return(interestRate);
}

void LoanContext::setInterestRate(float source)
{
    interestRate = source;
}

float LoanContext::getMinRepaymentAmount()
{
    return(minRepaymentAmount);
}

void LoanContext::setMinRepaymentAmount(float source)
{
    minRepaymentAmount = source;
}

int LoanContext::getMinRepaymentDay()
{
    return(minRepaymentDay);
}

void LoanContext::setMinRepaymentDay(int source)
{
    minRepaymentDay = source;
}

float LoanContext::getExtraRepaymentAmount()
{
    return(extraRepaymentAmount);
}

void LoanContext::setExtraRepaymentAmount(float source)
{
    extraRepaymentAmount = source;
}

int LoanContext::getExtraRepaymentDay()
{
    return(extraRepaymentDay);
}

void LoanContext::setExtraRepaymentDay(int source)
{
    extraRepaymentDay = source;    
}
