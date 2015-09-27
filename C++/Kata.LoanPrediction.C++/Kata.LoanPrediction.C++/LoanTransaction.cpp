//
//  LoanTransaction.cpp
//  Kata.LoanPrediction.C++
//
//  Created by retroburst [Andrew D] on 3/09/2015.
//  Copyright (c) 2015 retroburst [Andrew D]. All rights reserved.
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
    credit = 0.0;
    debit = 0.0;
    balance = 0.0;
}

/*
 ***************************************
 ** Constructor with arguments.
 ***************************************
 */
LoanTransaction::LoanTransaction(dateTime date, string type, double credit, double debit, double balance)
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
double LoanTransaction::getCredit()
{
    return(credit);
}

/*
 ***************************************
 ** Sets the credit portion of the
 ** transaction.
 ***************************************
 */
void LoanTransaction::setCredit(double source)
{
    credit = source;
}

/*
 ***************************************
 ** Gets the debit portion of the
 ** transaction.
 ***************************************
 */
double LoanTransaction::getDebit()
{
    return(debit);
}

/*
 ***************************************
 ** Sets the debit portion of the
 ** transaction.
 ***************************************
 */
void LoanTransaction::setDebit(double source)
{
    debit = source;
}

/*
 ***************************************
 ** Gets the balance of the
 ** transaction.
 ***************************************
 */
double LoanTransaction::getBalance()
{
    return(balance);
}

/*
 ***************************************
 ** Sets the balance of the
 ** transaction.
 ***************************************
 */
void LoanTransaction::setBalance(double source)
{
    balance = source;
}
