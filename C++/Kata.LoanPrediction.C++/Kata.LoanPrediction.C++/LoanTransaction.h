//
//  LoanTransaction.h
//  Kata.LoanPrediction.C++
//
//  Created by Andrew Dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanTransaction__
#define __Kata_LoanPrediction_C____LoanTransaction__

#include <string>
#include <stdio.h>
#include "Global.h"

using namespace std;

class LoanTransaction
{
public:
    LoanTransaction();
    ~LoanTransaction();
    LoanTransaction(dateTime date, string type, float credit, float debit, float principalBalance);
    dateTime getDate();
    void setDate(dateTime source);
    string getType();
    void setType(string source);
    float getCredit();
    void setCredit(float source);
    float getDebit();
    void setDebit(float source);
    float getPrincipalBalance();
    void setPrincipleBalance(float source);
    
private:
    dateTime date;
    string type;
    float credit;
    float debit;
    float principalBalance;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanTransaction__) */
