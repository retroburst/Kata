//
//  LoanContext.h
//  Kata.LoanPrediction.C++
//
//  Created by retroburst [Andrew D] on 3/09/2015.
//  Copyright (c) 2015 retroburst [Andrew D]. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanContext__
#define __Kata_LoanPrediction_C____LoanContext__

#include <stdio.h>
#include "Global.h"

/*
 ***************************************
 ** Context information of a loan.
 ***************************************
 */
class LoanContext {

public:
    LoanContext();
    LoanContext(dateTime startDate, dateTime targetEndDate, dateTime todaysDate, double balance, double interestRate, double minRepaymentAmount, int minRepaymentDay, double extraRepaymentAmount, int extraRepaymentDay);
    dateTime getStartDate();
    void setStartDate(dateTime source);
    dateTime getTargetEndDate();
    void setTargetEndDate(dateTime source);
    dateTime getTodaysDate();
    void setTodaysDate(dateTime source);
    double getBalance();
    void setBalance(double source);
    double getInterestRate();
    void setInterestRate(double source);
    double getMinRepaymentAmount();
    void setMinRepaymentAmount(double source);
    int getMinRepaymentDay();
    void setMinRepaymentDay(int source);
    double getExtraRepaymentAmount();
    void setExtraRepaymentAmount(double source);
    int getExtraRepaymentDay();
    void setExtraRepaymentDay(int source);

private:
    dateTime startDate;
    dateTime targetEndDate;
    dateTime todaysDate;
    double balance;
    double interestRate;
    double minRepaymentAmount;
    int minRepaymentDay;
    double extraRepaymentAmount;
    int extraRepaymentDay;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanContext__) */
