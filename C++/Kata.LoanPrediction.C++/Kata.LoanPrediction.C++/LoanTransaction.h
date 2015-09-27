//
//  LoanTransaction.h
//  Kata.LoanPrediction.C++
//
//  Created by retroburst [Andrew D] on 3/09/2015.
//  Copyright (c) 2015 retroburst [Andrew D]. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanTransaction__
#define __Kata_LoanPrediction_C____LoanTransaction__

#include <string>
#include <stdio.h>
#include "Global.h"

using namespace std;

/*
 ***************************************
 ** Represents a loan transaction. An
 ** example being an interest charged
 ** transaction or a monthly repayment
 ** transaction.
 ***************************************
 */
class LoanTransaction
{
public:
    LoanTransaction();
    LoanTransaction(dateTime date, string type, double credit, double debit, double balance);
    dateTime getDate();
    void setDate(dateTime source);
    string getType();
    void setType(string source);
    double getCredit();
    void setCredit(double source);
    double getDebit();
    void setDebit(double source);
    double getBalance();
    void setBalance(double source);
    
private:
    dateTime date;
    string type;
    double credit;
    double debit;
    double balance;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanTransaction__) */
