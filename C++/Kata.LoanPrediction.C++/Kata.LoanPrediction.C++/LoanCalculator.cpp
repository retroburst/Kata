//
//  LoanCalculator.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "LoanCalculator.h"
#include "Global.h"

LoanCalculator::LoanCalculator(LoanContext context)
{
    this->context = context;
}

LoanCalculator::~LoanCalculator()
{
    
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
    // todo: calculations
    LoanCalculationOutput output;
    dateTime nextDate;
    bool firstIteration = true;
    float principal = context.getPrincipal();
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
        if(currentDate.tm_mday == context.getMinRepaymentDay() && principal > 0.0f)
        {
            processMinRepayment(principal, context, currentDate, monthlyInterest, output);
        }
        // if extra repay day
        if(currentDate.tm_mday == context.getExtraRepaymentDay() && context.getExtraRepaymentAmount() > 0.0f && principal > 0.0f)
        {
            processExtraRepayment(principal, context, currentDate, output);
        }
        
        // if principal is zero or less - we are done!
        if(principal <= 0.0f) break;
        // calculate the daily interest
        monthlyInterest += calculateDailyInterest(principal, context.getInterestRate());
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
            processEndOfMonth(currentDate, monthlyInterest, principal, output);
        }
        currentDate = nextDate;
    }
    return(output);
}

/*
 ***************************************
 ** Processes the end of month, adds
 ** interest to the principal.
 ***************************************
 */
void LoanCalculator::processEndOfMonth(dateTime currentDate, float &monthlyInterest, float &principal, LoanCalculationOutput &output)
{
    // add interest charged transaction
    principal += monthlyInterest;
    // calculate the total interest paid
    output.setTotalInterestPaid(output.getTotalInterestPaid() + monthlyInterest);
    output.addTransaction(createTransaction(TX_TYPE_INTEREST_CHARGED, currentDate, 0.0f, monthlyInterest, principal));
    // reset for new month
    monthlyInterest = 0.0f;
}

/*
 ***************************************
 ** Processes the extra repayment for the
 ** current date if applicable.
 ***************************************
 */
void LoanCalculator::processExtraRepayment(float &principal, LoanContext context, dateTime currentDate, LoanCalculationOutput &output)
{
    if(currentDate.tm_mday == context.getExtraRepaymentDay() && context.getExtraRepaymentAmount() > 0.0f && principal > 0.0f)
    {
        // add extra repay transaction (if amount is more than 0)
        principal -= context.getExtraRepaymentAmount();
        output.addTransaction(createTransaction(TX_TYPE_EXTRA_REPAYMENT, currentDate, context.getExtraRepaymentDay(), 0.0f, principal));
    }
}

/*
 ***************************************
 ** Processes the min repayment for the
 ** current date if applicable.
 ***************************************
 */
void LoanCalculator::processMinRepayment(float &principal, LoanContext context, dateTime &currentDate, float monthlyInterest, LoanCalculationOutput &output)
{
    // add min repay transaction
    if((principal + monthlyInterest) <= context.getMinRepaymentAmount())
    {
        float finalRepayment = 0.0f;
        output.setLoanEndsDate(currentDate);
        principal += monthlyInterest;
        finalRepayment = principal;
        principal -= finalRepayment;
        output.addTransaction(createTransaction(TX_FINAL_REPAYMENT, currentDate, finalRepayment, monthlyInterest, principal));
    }
    else
    {
        principal -= context.getMinRepaymentAmount();
        output.addTransaction(createTransaction(TX_TYPE_MIN_REPAYMENT, currentDate, context.getMinRepaymentAmount(), 0.0f, principal));
    }
}

/*
 ***************************************
 ** Calculates the interest for a day.
 ***************************************
 */
float LoanCalculator::calculateDailyInterest(float principal, float interestRate)
{
    float result = 0.0f;
    result = (principal * (interestRate / 100)) / NUM_DAYS_IN_YEAR;
    return(result);
}

/*
 ***************************************
 ** Creates a transaction using the 
 ** provided values.
 ***************************************
 */
LoanTransaction LoanCalculator::createTransaction(string type, dateTime date, float repayment, float charge, float remainPrincipal)
{
    LoanTransaction transaction;
    transaction.setType(type);
    transaction.setDate(date);
    transaction.setCredit(repayment);
    transaction.setDebit(charge);
    transaction.setPrincipleBalance(remainPrincipal);
    return(transaction);
}
