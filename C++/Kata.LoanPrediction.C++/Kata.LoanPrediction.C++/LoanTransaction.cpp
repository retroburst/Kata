//
//  LoanTransaction.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "LoanTransaction.h"

LoanTransaction::LoanTransaction()
{
    date = *DATETIME_EMPTY;
    type = *STRING_EMPTY;
    credit = 0.0f;
    debit = 0.0f;
    balance = 0.0f;
}

LoanTransaction::~LoanTransaction()
{
    
}

LoanTransaction::LoanTransaction(dateTime date, string type, float credit, float debit, float balance)
{
    this->date = date;
    this->type = type;
    this->credit = credit;
    this-> debit = debit;
    this->balance = balance;
}

dateTime LoanTransaction::getDate()
{
    return(date);
}

void LoanTransaction::setDate(dateTime source)
{
    date = source;
}

string LoanTransaction::getType()
{
    return(type);
}

void LoanTransaction::setType(string source)
{
    type = source;
}

float LoanTransaction::getCredit()
{
    return(credit);
}

void LoanTransaction::setCredit(float source)
{
    credit = source;
}

float LoanTransaction::getDebit()
{
    return(debit);
}

void LoanTransaction::setDebit(float source)
{
    debit = source;
}

float LoanTransaction::getBalance()
{
    return(balance);
}

void LoanTransaction::setBalance(float source)
{
    balance = source;
}
