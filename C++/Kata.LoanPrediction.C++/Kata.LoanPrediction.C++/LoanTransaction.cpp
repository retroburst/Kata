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
    
}

LoanTransaction::~LoanTransaction()
{
    
}

LoanTransaction::LoanTransaction(dateTime date, string type, float credit, float debit, float principalBalance)
{
    
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

float LoanTransaction::getPrincipalBalance()
{
    return(principalBalance);
}

void LoanTransaction::setPrincipleBalance(float source)
{
    principalBalance = source;
}
