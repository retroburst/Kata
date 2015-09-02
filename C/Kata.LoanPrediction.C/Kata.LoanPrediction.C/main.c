//
//  main.c
//  Kata.LoanPrediction.C
//
//  Created by Andrew Dowding on 2/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"
#include "transactionLinkedList.h"

// constants
const char* PROGRAM_NAME = "Kata.LoanPrediction.C";
const int EXPECTED_ARGUMENT_COUNT = 7;
const char* USAGE_DIRECTIVE =  "Usage: %s principalAmount interestRate minRepayAmount "
                                "minRepayDay extraRepayAmount extraRepayDay\n"
                                "Example: %s 20000.00 5.74 1500.00 18 1200.00 15";
const int DAYS = 365;
const char *TX_TYPE_MIN_REPAYMENT = "Minimum Repayment";
const char *TX_TYPE_EXTRA_REPAYMENT = "Extra Repayment";
const char *TX_TYPE_INTEREST_CHARGED = "Interest Charged";
const char *TX_FINAL_REPAYMENT = "Final Repayment";

// structs
struct context{
    float principalAmount;
    float interestRate;
    float minRepayAmount;
    int minRepayDay;
    float extraRepayAmount;
    int extraRepayDay;
};

// type definitions
typedef struct context context;
typedef struct tm dateTime;

// function prototypes
void printUsage();
context* processArguments(int argc, const char *argv[]);
bool calculateLoan(context *runningContext, dateTime *startDate, dateTime **finalDate);
float calculateDailyInterest(float principal, float interestRate);
transaction* createTransaction(const char *type, dateTime *date, float repayment, float charge, float remainPrincipal);
void printCalculations(dateTime *finalDate);
char* formatDate(dateTime *target);

// variables
transactionNode *rootTransactionNode = NULL;
transactionNode *headTransactionNode = NULL;
context *runningContext = NULL;
dateTime *startDate = NULL;
dateTime *finalDate = NULL;

/*
***************************************
** Entry point of program. Expects 6
** user supplied arguments.
***************************************
*/
int main(int argc, const char * argv[]) {
    if(argc != EXPECTED_ARGUMENT_COUNT)
    {
        printUsage();
        return(EXIT_FAILURE);
        
    }
    else
    {
        runningContext = processArguments(argc, argv);
    }
    time_t localTime = time(NULL);
    startDate = localtime(&localTime);
    bool result = calculateLoan(runningContext, startDate, &finalDate);
    printCalculations(finalDate);
    if(result == true) return (EXIT_SUCCESS);
    else return (EXIT_FAILURE);
}

/*
 ***************************************
 ** Prints the usage directive to the 
 ** console.
 ***************************************
 */
void printUsage()
{
    printf(USAGE_DIRECTIVE, PROGRAM_NAME, PROGRAM_NAME);
}

/*
 ***************************************
 ** Process the command line arguments
 ** and bundles them in a context struct.
 ***************************************
 */
context* processArguments(int argc, const char* argv[])
{
    context* tmp = malloc(sizeof(context));
    tmp->principalAmount = (float) atof(argv[1]);
    tmp->interestRate =  (float) atof(argv[2]);
    tmp->minRepayAmount =  (float) atof(argv[3]);
    tmp->minRepayDay = (int) atoi(argv[4]);
    tmp->extraRepayAmount =  (float) atof(argv[5]);
    tmp->extraRepayDay = (int) atoi(argv[6]);
    return(tmp);
}

/*
 ***************************************
 ** Calculates the transactions on the
 ** loan from now to the time it will be
 ** paid off.
 ***************************************
 */
bool calculateLoan(context *runningContext, dateTime* startDate, dateTime **finalDate)
{
    float principal = runningContext->principalAmount;
    float monthlyInterest = 0.0f;
    int currentMonth = startDate->tm_mon;
    
    while(true)
    {
        // if min repay day
        if(startDate->tm_mday == runningContext->minRepayDay && principal > 0.0f)
        {
            // add min repay transaction
            if((principal + monthlyInterest) <= runningContext->minRepayAmount)
            {
                float finalRepayment = 0.0f;
                *finalDate = malloc(sizeof(dateTime));
                **finalDate = *startDate;
                principal += monthlyInterest;
                finalRepayment = principal;
                principal -= finalRepayment;
                AddTransactionNode(&rootTransactionNode, &headTransactionNode, createTransaction(TX_FINAL_REPAYMENT, startDate, finalRepayment, monthlyInterest, principal));
            }
            else
            {
                principal -= runningContext->minRepayAmount;
                AddTransactionNode(&rootTransactionNode, &headTransactionNode, createTransaction(TX_TYPE_MIN_REPAYMENT, startDate, runningContext->minRepayAmount, 0.0f, principal));
            }
        }
        // if extra repay day
        if(startDate->tm_mday == runningContext->extraRepayDay && runningContext->extraRepayAmount > 0.0f && principal > 0.0f)
        {
            // add extra repay transaction (if amount is more than 0)
            principal -= runningContext->extraRepayAmount;
            AddTransactionNode(&rootTransactionNode, &headTransactionNode, createTransaction(TX_TYPE_EXTRA_REPAYMENT, startDate, runningContext->extraRepayAmount, 0.0f, principal));
        }
        
        if(principal <= 0.0f) break;
        
        // calculate the daily interest
        monthlyInterest += calculateDailyInterest(principal, runningContext->interestRate);
        
        startDate->tm_mday = startDate->tm_mday + 1;
        mktime(startDate);
        if(currentMonth != startDate->tm_mon)
        {
            // add interest charged transaction
            principal += monthlyInterest;
            AddTransactionNode(&rootTransactionNode, &headTransactionNode, createTransaction(TX_TYPE_INTEREST_CHARGED, startDate, 0.0f, monthlyInterest, principal));
            monthlyInterest = 0.0f;
            currentMonth = startDate->tm_mon;
        }
    }
    return(true);
}

/*
 ***************************************
 ** Calculates the interest for a day.
 ***************************************
 */
float calculateDailyInterest(float principal, float interestRate)
{
    float result = 0.0f;
    result = (principal * (interestRate / 100)) / DAYS;
    return(result);
}

/*
 ***************************************
 ** Creates a transaction struct to be
 ** added to a linked list.
 ***************************************
 */
transaction* createTransaction(const char* type, dateTime* date, float repayment, float charge, float remainPrincipal)
{
    transaction *tmp = malloc(sizeof(transaction));
    tmp->transactionType = type;
    tmp->charge = charge;
    tmp->remainPrincipalAmount = remainPrincipal;
    tmp->repayment = repayment;
    tmp->transactionDate = *date;
    return(tmp);
}

/*
 ***************************************
 ** Prints the calculations to the console
 ** and the date on which the loan
 ** will be paid off.
 ***************************************
 */
void printCalculations(dateTime *finalDate)
{
    transactionNode *current = rootTransactionNode;
    while(current != NULL)
    {
        printf("%s - %-17s - Payment: $%-10.2f Charge: $%-10.2f Prinicpal: $%-10.2f\n",
               formatDate(&current->item->transactionDate),
               current->item->transactionType,
               current->item->repayment,
               current->item->charge,
               current->item->remainPrincipalAmount);
        current = current->next;
    }
    printf("Loan is paid off on %s", formatDate(finalDate));
}

/*
 ***************************************
 ** Formats a date as a string.
 ***************************************
 */
char* formatDate(dateTime *target)
{
    char *result = malloc(sizeof(char) * 26);
    strftime(result, 26, "%d/%m/%Y", target);
    return(result);
}
