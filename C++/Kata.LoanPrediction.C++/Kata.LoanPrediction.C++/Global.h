//
//  Global.h
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____Global__
#define __Kata_LoanPrediction_C____Global__

#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

typedef struct tm dateTime;

// constants
static const string PROGRAM_NAME = "Kata.LoanPrediction.C++";
static const int EXPECTED_ARGUMENT_COUNT = 9;
static const char* USAGE_DIRECTIVE =  "Usage: %s startDate-{dd/mm/yyyy} principalAmount interestRate minRepayAmount "
"minRepayDay extraRepayAmount extraRepayDay\n"
"Example: %s 23/12/2015 20000.00 5.74 1500.00 18 1200.00 15";
static const int NUM_DAYS_IN_YEAR = 365;
static const string TX_TYPE_MIN_REPAYMENT = "Minimum Repayment";
static const string TX_TYPE_EXTRA_REPAYMENT = "Extra Repayment";
static const string TX_TYPE_INTEREST_CHARGED = "Interest Charged";
static const string TX_FINAL_REPAYMENT = "Final Repayment";
static const char *DATE_FORMAT = "%d/%m/%Y";
static const char *DATE_FORMAT_FOR_FILENAME = "%d.%m.%Y";
static const char *TRANSACTION_FORMAT_PATTERN = "%s - %-17s - Credit: $%-10.2f Debit: $%-10.2f Prinicpal Balance: $%-10.2f\n";
static const char *LOAN_PAID_OFF_FORMAT_PATTERN = "\nLoan is paid off on %s, total interest paid from %s to %s is $%.2f.\n";
static const char *OUTPUT_HEADER_PATTERN_FORMAT = "%s\n\nToday's Date: %s\nStart Date: %s\nPrincipal: $%.2f\nInterest Rate: %.2f%%\nMin. Repayment Amount: $%.2f\nMin. Repayment Day: %d\nExtra Repayment: $%.2f\nExtra Repayment Day: %d\n\n";

#endif /* defined(__Kata_LoanPrediction_C____Global__) */
