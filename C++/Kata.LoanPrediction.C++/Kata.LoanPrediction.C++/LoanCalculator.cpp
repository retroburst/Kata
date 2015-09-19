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
	bool firstIteration = true;
	double balance = context.getBalance();
	double monthlyInterest = 0.0;
	dateTime currentDate = context.getStartDate();
	// we will calculate interest from the first of the month
	dateTime calcInterestStartDate = currentDate;
	calcInterestStartDate.tm_mday = 1;
	output.setInterestStartDate(calcInterestStartDate);
	// loop through dates, caculating interest daily etc
	while (true)
	{
		// if min repay day
		if (currentDate.tm_mday == context.getMinRepaymentDay() && balance > 0.0)
		{
			processMinRepayment(balance, context.getMinRepaymentAmount(), currentDate, monthlyInterest, output);
		}
		// if extra repay day
		if (currentDate.tm_mday == context.getExtraRepaymentDay() && context.getExtraRepaymentAmount() > 0.0 && balance > 0.0)
		{
			processExtraRepayment(balance, context.getExtraRepaymentAmount(), currentDate, output);
		}

		// if balance is zero or less - we are done!
		if (balance <= 0.0)
        {
            output.setLoanEndsDate(currentDate);
            break;
        }
		// calculate the daily interest
		monthlyInterest += calculateDailyInterest(balance, context.getInterestRate());
		// if this is the first iteration and we did not start on the first of the month
		// let's calculate the interest for the days back to the first
		if (firstIteration && context.getStartDate().tm_mday != 1)
		{
			int daysToMonthStart = currentDate.tm_mday - 1;
			monthlyInterest += (monthlyInterest * daysToMonthStart);
			firstIteration = false;
		}
		// move date forward
		dateTime nextDate = currentDate;
		nextDate.tm_mday = nextDate.tm_mday + 1;
		mktime(&nextDate);
		// if end of month
		if (currentDate.tm_mon != nextDate.tm_mon)
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
void LoanCalculator::processEndOfMonth(dateTime currentDate, double &monthlyInterest, double &balance, LoanCalculationOutput &output)
{
	// add interest charged transaction
	balance += monthlyInterest;
	// calculate the total interest paid
	output.setTotalInterestPaid(output.getTotalInterestPaid() + monthlyInterest);
	output.addTransaction(createTransaction(TX_TYPE_INTEREST_CHARGED, currentDate, 0.0, monthlyInterest, balance));
	// reset for new month
	monthlyInterest = 0.0;
}

/*
 ***************************************
 ** Processes the extra repayment for the
 ** current date if applicable.
 ***************************************
 */
void LoanCalculator::processExtraRepayment(double &balance, double extraRepaymentAmount, dateTime currentDate, LoanCalculationOutput &output)
{
	// add extra repay transaction (if amount is more than 0)
	balance -= extraRepaymentAmount;
	output.addTransaction(createTransaction(TX_TYPE_EXTRA_REPAYMENT, currentDate, extraRepaymentAmount, 0.0, balance));
}

/*
 ***************************************
 ** Processes the min repayment for the
 ** current date if applicable.
 ***************************************
 */
void LoanCalculator::processMinRepayment(double &balance, double minRepaymentAmount, dateTime &currentDate, double monthlyInterest, LoanCalculationOutput &output)
{
	// add min repay transaction
	if ((balance + monthlyInterest) <= minRepaymentAmount)
	{
		double finalRepayment = 0.0;
		balance += monthlyInterest;
		finalRepayment = balance;
		balance -= finalRepayment;
		output.addTransaction(createTransaction(TX_FINAL_REPAYMENT, currentDate, finalRepayment, monthlyInterest, balance));
	}
	else
	{
		balance -= context.getMinRepaymentAmount();
		output.addTransaction(createTransaction(TX_TYPE_MIN_REPAYMENT, currentDate, minRepaymentAmount, 0.0, balance));
	}
}

/*
 ***************************************
 ** Calculates the interest for a day.
 ***************************************
 */
double LoanCalculator::calculateDailyInterest(double balance, double interestRate)
{
	double result = 0.0;
	result = (balance * (interestRate / 100)) / NUM_DAYS_IN_YEAR;
	return(result);
}

/*
 ***************************************
 ** Creates a transaction using the
 ** provided values.
 ***************************************
 */
LoanTransaction LoanCalculator::createTransaction(string type, dateTime date, double repayment, double charge, double balance)
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
	if (compareResult == 0)
	{
		output.setTargetEndDateHit(true);
		return;
	}
	if (compareResult == 1)
	{
		searchForwards = false;
	}
	else if (compareResult == -1)
	{
		searchForwards = true;
	}
	while (compareDates(*search, targetEndDate) != 0)
	{
		if (searchForwards)
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

