//
//  LoanCalculator.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "LoanCalculator.h"
#include "Global.h"

/*
 ***************************************
 ** Default constructor.
 ***************************************
 */
LoanCalculator::LoanCalculator(LoanContext context)
{
    this->context = context;
}

/*
 ***************************************
 ** Calculates the transactions on the
 ** loan from now to the time it will be
 ** paid off.
 ***************************************
 */
LoanCalculationOutput LoanCalculator::calculateLoan()
{
    LoanCalculationOutput output;
    dateTime nextDate;
    bool firstIteration = true;
    float balance = context.getBalance();
    float monthlyInterest = 0.0f;
    dateTime currentDate = context.getStartDate();
    // we will calculate interest from the first of the month
    dateTime calcInterestStartDate = currentDate;
    calcInterestStartDate.tm_mday = 1;
    output.setInterestStartDate(calcInterestStartDate);
    // loop through dates, caculating interest daily etc
    while(true)
    {
        // if min repay day
        if(currentDate.tm_mday == context.getMinRepaymentDay() && balance > 0.0f)
        {
            processMinRepayment(balance, context, currentDate, monthlyInterest, output);
        }
        // if extra repay day
        if(currentDate.tm_mday == context.getExtraRepaymentDay() && context.getExtraRepaymentAmount() > 0.0f && balance > 0.0f)
        {
            processExtraRepayment(balance, context, currentDate, output);
        }
        
        // if balance is zero or less - we are done!
        if(balance <= 0.0f) break;
        // calculate the daily interest
        monthlyInterest += calculateDailyInterest(balance, context.getInterestRate());
        // if this is the first iteration and we did not start on the first of the month
        // let's calculate the interest for the days back to the first
        if(firstIteration && context.getStartDate().tm_mday != 1)
        {
            int daysToMonthStart = currentDate.tm_mday - 1;
            monthlyInterest += (monthlyInterest * daysToMonthStart);
            firstIteration = false;
        }
        // move date forward
        nextDate = currentDate;
        nextDate.tm_mday = nextDate.tm_mday + 1;
        mktime(&nextDate);
        // if end of month
        if(currentDate.tm_mon != nextDate.tm_mon)
        {
            processEndOfMonth(currentDate, monthlyInterest, balance, output);
        }
        currentDate = nextDate;
    }
    setTargetEndDateAccuracy(output.getLoanEndsDate(), context.getTargetEndDate(), output);
    return(output);
}

/*
 ***************************************
 ** Processes the end of month, adds
 ** interest to the balance.
 ***************************************
 */
void LoanCalculator::processEndOfMonth(dateTime currentDate, float &monthlyInterest, float &balance, LoanCalculationOutput &output)
{
    // add interest charged transaction
    balance += monthlyInterest;
    // calculate the total interest paid
    output.setTotalInterestPaid(output.getTotalInterestPaid() + monthlyInterest);
    output.addTransaction(createTransaction(TX_TYPE_INTEREST_CHARGED, currentDate, 0.0f, monthlyInterest, balance));
    // reset for new month
    monthlyInterest = 0.0f;
}

/*
 ***************************************
 ** Processes the extra repayment for the
 ** current date if applicable.
 ***************************************
 */
void LoanCalculator::processExtraRepayment(float &balance, LoanContext context, dateTime currentDate, LoanCalculationOutput &output)
{
    if(currentDate.tm_mday == context.getExtraRepaymentDay() && context.getExtraRepaymentAmount() > 0.0f && balance > 0.0f)
    {
        // add extra repay transaction (if amount is more than 0)
        balance -= context.getExtraRepaymentAmount();
        output.addTransaction(createTransaction(TX_TYPE_EXTRA_REPAYMENT, currentDate, context.getExtraRepaymentDay(), 0.0f, balance));
    }
}

/*
 ***************************************
 ** Processes the min repayment for the
 ** current date if applicable.
 ***************************************
 */
void LoanCalculator::processMinRepayment(float &balance, LoanContext context, dateTime &currentDate, float monthlyInterest, LoanCalculationOutput &output)
{
    // add min repay transaction
    if((balance + monthlyInterest) <= context.getMinRepaymentAmount())
    {
        float finalRepayment = 0.0f;
        output.setLoanEndsDate(currentDate);
        balance += monthlyInterest;
        finalRepayment = balance;
        balance -= finalRepayment;
        output.addTransaction(createTransaction(TX_FINAL_REPAYMENT, currentDate, finalRepayment, monthlyInterest, balance));
    }
    else
    {
        balance -= context.getMinRepaymentAmount();
        output.addTransaction(createTransaction(TX_TYPE_MIN_REPAYMENT, currentDate, context.getMinRepaymentAmount(), 0.0f, balance));
    }
}

/*
 ***************************************
 ** Calculates the interest for a day.
 ***************************************
 */
float LoanCalculator::calculateDailyInterest(float balance, float interestRate)
{
    float result = 0.0f;
    result = (balance * (interestRate / 100)) / NUM_DAYS_IN_YEAR;
    return(result);
}

/*
 ***************************************
 ** Creates a transaction using the 
 ** provided values.
 ***************************************
 */
LoanTransaction LoanCalculator::createTransaction(string type, dateTime date, float repayment, float charge, float balance)
{
    LoanTransaction transaction;
    transaction.setType(type);
    transaction.setDate(date);
    transaction.setCredit(repayment);
    transaction.setDebit(charge);
    transaction.setBalance(balance);
    return(transaction);
}

/*
 ***************************************
 ** Sets the accuracy of the target end
 ** end date with respect to the actual
 ** end date.
 ***************************************
 */
void LoanCalculator::setTargetEndDateAccuracy(dateTime actualEndDate, dateTime targetEndDate, LoanCalculationOutput &output)
{
    int daysMissed = 0;
    bool searchForwards = false;
    output.setTargetEndDateHit(false);
    dateTime *search = new dateTime(actualEndDate);
    int compareResult = compareDates(actualEndDate, targetEndDate);
    if(compareResult == 0)
    {
        output.setTargetEndDateHit(true);
        return;
    }
    if(compareResult == 1)
    {
        searchForwards = false;
    }
    else if(compareResult == -1)
    {
        searchForwards = true;
    }
    while(compareDates(*search, targetEndDate) != 0)
    {
        if(searchForwards)
        {
            search->tm_mday = search->tm_mday + 1;
            daysMissed--;
        }
        else
        {
            search->tm_mday = search->tm_mday - 1;
            daysMissed++;
        }
        mktime(search);
    }
    output.setTargetEndDateMissedInDays(daysMissed);
    delete(search);
}

