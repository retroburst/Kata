//
//  LoanTransaction.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "LoanTransaction.h"

/*
 ***************************************
 ** Default constructor.
 ***************************************
 */
LoanTransaction::LoanTransaction()
{
    date = *DATETIME_EMPTY;
    type = *STRING_EMPTY;
    credit = 0.0f;
    debit = 0.0f;
    balance = 0.0f;
}

/*
 ***************************************
 ** Constructor with arguments.
 ***************************************
 */
LoanTransaction::LoanTransaction(dateTime date, string type, float credit, float debit, float balance)
{
    this->date = date;
    this->type = type;
    this->credit = credit;
    this-> debit = debit;
    this->balance = balance;
}

/*
 ***************************************
 ** Gets the date of the transaction.
 ***************************************
 */
dateTime LoanTransaction::getDate()
{
    return(date);
}

/*
 ***************************************
 ** Sets the date of the transaction.
 ***************************************
 */
void LoanTransaction::setDate(dateTime source)
{
    date = source;
}

/*
 ***************************************
 ** Gets the type of the transaction.
 ***************************************
 */
string LoanTransaction::getType()
{
    return(type);
}

/*
 ***************************************
 ** Sets the type of the transaction.
 ***************************************
 */
void LoanTransaction::setType(string source)
{
    type = source;
}

/*
 ***************************************
 ** Gets the credit portion of the 
 ** transaction.
 ***************************************
 */
float LoanTransaction::getCredit()
{
    return(credit);
}

/*
 ***************************************
 ** Sets the credit portion of the
 ** transaction.
 ***************************************
 */
void LoanTransaction::setCredit(float source)
{
    credit = source;
}

/*
 ***************************************
 ** Gets the debit portion of the
 ** transaction.
 ***************************************
 */
float LoanTransaction::getDebit()
{
    return(debit);
}

/*
 ***************************************
 ** Sets the debit portion of the
 ** transaction.
 ***************************************
 */
void LoanTransaction::setDebit(float source)
{
    debit = source;
}

/*
 ***************************************
 ** Gets the balance of the
 ** transaction.
 ***************************************
 */
float LoanTransaction::getBalance()
{
    return(balance);
}

/*
 ***************************************
 ** Sets the balance of the
 ** transaction.
 ***************************************
 */
void LoanTransaction::setBalance(float source)
{
    balance = source;
}
