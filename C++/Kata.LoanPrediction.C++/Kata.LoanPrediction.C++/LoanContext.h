//
//  LoanContext.h
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanContext__
#define __Kata_LoanPrediction_C____LoanContext__

#include <stdio.h>
#include "Global.h"

class LoanContext {
    
public:
    LoanContext();
    ~LoanContext();
    LoanContext(dateTime startDate, dateTime targetEndDate, dateTime todaysDate, float balance, float interestRate, float minRepaymentAmount, int minRepaymentDay, float extraRepaymentAmount, int extraRepaymentDay);
    dateTime getStartDate();
    void setStartDate(dateTime source);
    dateTime getTargetEndDate();
    void setTargetEndDate(dateTime source);
    dateTime getTodaysDate();
    void setTodaysDate(dateTime source);
    float getBalance();
    void setBalance(float source);
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

private:
    dateTime startDate;
    dateTime targetEndDate;
    dateTime todaysDate;
    float balance;
    float interestRate;
    float minRepaymentAmount;
    int minRepaymentDay;
    float extraRepaymentAmount;
    int extraRepaymentDay;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanContext__) */
