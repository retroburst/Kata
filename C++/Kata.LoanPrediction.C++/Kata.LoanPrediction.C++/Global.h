//
//  Global.h
//  Kata.LoanPrediction.C++
//
//  Created by retroburst [Andrew D] on 3/09/2015.
//  Copyright (c) 2015 retroburst [Andrew D]. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____Global__
#define __Kata_LoanPrediction_C____Global__

#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

typedef struct tm dateTime;

// constants
static const string* STRING_EMPTY = new string();
static const dateTime* DATETIME_EMPTY = new dateTime();
static const string PROGRAM_NAME = "Kata.LoanPrediction.C++";
static const int EXPECTED_ARGUMENT_COUNT = 9;
static const int NUM_DAYS_IN_YEAR = 365;
static const string TX_TYPE_MIN_REPAYMENT = "Minimum Repayment";
static const string TX_TYPE_EXTRA_REPAYMENT = "Extra Repayment";
static const string TX_TYPE_INTEREST_CHARGED = "Interest Charged";
static const string TX_FINAL_REPAYMENT = "Final Repayment";
static const char *DATE_FORMAT = "%d/%m/%Y";
static const char *DATE_FORMAT_FOR_FILENAME = "%Y.%m.%d";

// function prototypes
int compareDates(dateTime x, dateTime y);
int daysInMonth(int month, int year);
bool isLeapYear(int year);
void addDay(dateTime *target);
void minusDay(dateTime *target);

#endif /* defined(__Kata_LoanPrediction_C____Global__) */
