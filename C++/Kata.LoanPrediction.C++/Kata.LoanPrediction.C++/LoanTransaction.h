//
//  LoanTransaction.h
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
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
    LoanTransaction(dateTime date, string type, float credit, float debit, float balance);
    dateTime getDate();
    void setDate(dateTime source);
    string getType();
    void setType(string source);
    float getCredit();
    void setCredit(float source);
    float getDebit();
    void setDebit(float source);
    float getBalance();
    void setBalance(float source);
    
private:
    dateTime date;
    string type;
    float credit;
    float debit;
    float balance;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanTransaction__) */
