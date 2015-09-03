//
//  LoanContext.cpp
//  Kata.LoanPrediction.C++
//
//  Created by Andrew Dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "LoanContext.h"

LoanContext::LoanContext()
{ }

LoanContext::LoanContext(dateTime startDate, dateTime targetEndDate, dateTime todaysDate, float principal, float interestRate, float minRepaymentAmount, int minRepaymentDay, float extraRepaymentAmount, int extraRepaymentDay)
{
    this->startDate = startDate;
    this->targetEndDate = targetEndDate;
    this->todaysDate = todaysDate;
    this->principal = principal;
    this->interestRate = interestRate;
    this->minRepaymentAmount = minRepaymentAmount;
    this->minRepaymentDay = minRepaymentDay;
    this->extraRepaymentAmount = extraRepaymentAmount;
    this->extraRepaymentDay = extraRepaymentDay;
}


dateTime LoanContext::getStartDate()
{
    return(startDate);
}

void LoanContext::setStartDate(dateTime source)
{
    startDate = source;
}

/*
dateTime getTargetEndDate();
void setTargetEndDate(dateTime source);
dateTime getTodaysDate();
void setTodaysDate(dateTime source);
float getPrincipal();
void setPricipal(float source);
float getInterestRate();
void setInterestRate(float source);
float getMinRepaymentAmount();
void setMinRepaymentAmount(float source);
int getMinRepaymentDay();
void setMinRepaymentDay(int source);
float getExtraRepaymentAmount();
void setExtraRepaymentAmount(float source);
int getExtraRepaymentDay();
void setExtraRepaymentDay(int source);
*/