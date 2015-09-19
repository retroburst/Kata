//
//  transaction.h
//  Kata.LoanPrediction.C
//
//  Created by A.J.Dowding on 2/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C__transaction__
#define __Kata_LoanPrediction_C__transaction__

#include <stdio.h>
#include <time.h>

typedef struct tm dateTime;

struct transaction {
    dateTime transactionDate;
    const char *transactionType;
    double credit;
    double debit;
    double balance;
};

typedef struct transaction transaction;


#endif /* defined(__Kata_LoanPrediction_C__transaction__) */
