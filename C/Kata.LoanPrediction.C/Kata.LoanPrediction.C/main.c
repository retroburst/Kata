//
//  main.c
//  Kata.LoanPrediction.C
//
//  Created by A.J.Dowding on 2/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

//TODO: remove pointer arguments to functions where function does not change the value and a copy is not costly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"
#include "transactionLinkedList.h"

// constants
const char* PROGRAM_NAME = "Kata.LoanPrediction.C";
const int EXPECTED_ARGUMENT_COUNT = 8;
const char* USAGE_DIRECTIVE =  "Usage: %s startDate-{dd/mm/yyyy} principalAmount interestRate minRepayAmount "
                                "minRepayDay extraRepayAmount extraRepayDay\n"
                                "Example: %s 23/12/2015 20000.00 5.74 1500.00 18 1200.00 15";
const int NUM_DAYS_IN_YEAR = 365;
const char *TX_TYPE_MIN_REPAYMENT = "Minimum Repayment";
const char *TX_TYPE_EXTRA_REPAYMENT = "Extra Repayment";
const char *TX_TYPE_INTEREST_CHARGED = "Interest Charged";
const char *TX_FINAL_REPAYMENT = "Final Repayment";
const char *DATE_FORMAT = "%d/%m/%Y";
const char *DATE_FORMAT_FOR_FILENAME = "%d.%m.%Y";
const char *TRANSACTION_FORMAT_PATTERN = "%s - %-17s - Credit: $%-10.2f Debit: $%-10.2f Prinicpal Balance: $%-10.2f\n";
const char *LOAN_PAID_OFF_FORMAT_PATTERN = "\nLoan is paid off on %s, total interest paid from %s to %s is $%.2f.\n";
const char *OUTPUT_HEADER_PATTERN_FORMAT = "%s\n\nToday's Date: %s\nStart Date: %s\nPrincipal: $%.2f\nInterest Rate: %.2f%%\nMin. Repayment Amount: $%.2f\nMin. Repayment Day: %d\nExtra Repayment: $%.2f\nExtra Repayment Day: %d\n\n";

// structs
struct context
{
    dateTime startDate;
    dateTime todaysDate;
    float principalAmount;
    float interestRate;
    float minRepayAmount;
    int minRepayDay;
    float extraRepayAmount;
    int extraRepayDay;
};

struct calculationOutput
{
    dateTime interestStartDate;
    dateTime loanEndsDate;
    float totalInterestPaid;
};

// type definitions
typedef struct context context;
typedef struct tm dateTime;
typedef struct calculationOutput calculationOutput;

// function prototypes
void printUsage();
context* processArguments(int argc, const char *argv[]);
calculationOutput* calculateLoan(context *runningContext);
float calculateDailyInterest(float principal, float interestRate);
transaction* createTransaction(const char *type, dateTime *date, float repayment, float charge, float remainPrincipal);
void printCalculations(calculationOutput *output);
char* formatDate(dateTime *target, const char *dateFormat);
void processMinRepayment(float *principal, context *runningContext, dateTime *currentDate, float monthlyInterest, calculationOutput *output);
void processExtraRepayment(float *principal, context *runningContext, dateTime *currentDate);
char* buildOutputFilename(dateTime *currentDate);
void printOutputToFile(dateTime *currentDate, calculationOutput *output);
void printOutputHeader(context *runningContext);
void processEndOfMonth(dateTime *currentDate, float *monthlyInterest, float *principal, calculationOutput *output);
bool checkAllocation(void *target);

// variables
transactionNode *rootTransactionNode = NULL;
transactionNode *headTransactionNode = NULL;
context *runningContext = NULL;
dateTime *todaysDate = NULL;
calculationOutput *output = NULL;

/*
***************************************
** Entry point of program. Expects 6
** user supplied arguments.
***************************************
*/
int main(int argc, const char * argv[]) {
    // get today's date
    time_t localTime = time(NULL);
    todaysDate = localtime(&localTime);
    
    if(argc != EXPECTED_ARGUMENT_COUNT)
    {
        printUsage();
        return(EXIT_FAILURE);
    }
    else
    {
        runningContext = processArguments(argc, argv);
        runningContext->todaysDate = *todaysDate;
    }
    printOutputHeader(runningContext);
    output = calculateLoan(runningContext);
    printCalculations(output);
    printOutputToFile(todaysDate, output);
    // free dynamically allocated memory
    free(runningContext);
    free(output);
    freeAllNodes(rootTransactionNode, headTransactionNode);
    free(todaysDate);
    return (EXIT_SUCCESS);
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
    if(!checkAllocation(tmp)) return (NULL);
    strptime(argv[1], DATE_FORMAT, &tmp->startDate);
    tmp->principalAmount = (float) atof(argv[2]);
    tmp->interestRate =  (float) atof(argv[3]);
    tmp->minRepayAmount =  (float) atof(argv[4]);
    tmp->minRepayDay = (int) atoi(argv[5]);
    tmp->extraRepayAmount =  (float) atof(argv[6]);
    tmp->extraRepayDay = (int) atoi(argv[7]);
    return(tmp);
}

/*
 ***************************************
 ** Prints the program name, 
 ** arguments provided by the user etc.
 ***************************************
 */
void printOutputHeader(context *runningContext)
{
    printf(OUTPUT_HEADER_PATTERN_FORMAT,
           PROGRAM_NAME,
           formatDate(&(runningContext->todaysDate), DATE_FORMAT),
           formatDate(&(runningContext->startDate), DATE_FORMAT),
           runningContext->principalAmount,
           runningContext->interestRate,
           runningContext->minRepayAmount,
           runningContext->minRepayDay,
           runningContext->extraRepayAmount,
           runningContext->extraRepayDay
           );
}

/*
 ***************************************
 ** Calculates the transactions on the
 ** loan from now to the time it will be
 ** paid off.
 ***************************************
 */
calculationOutput* calculateLoan(context *runningContext)
{
    calculationOutput* output = malloc(sizeof(calculationOutput));
    if(!checkAllocation(output)) return (NULL);
    dateTime nextDate;
    bool firstIteration = true;
    float principal = runningContext->principalAmount;
    float monthlyInterest = 0.0f;
    dateTime *currentDate = malloc(sizeof(dateTime));
    if(!checkAllocation(currentDate)) return (NULL);
    *currentDate = runningContext->startDate;
    // we will calculate interest from the first of the month
    output->interestStartDate = runningContext->startDate;
    output->interestStartDate.tm_mday = 1;
    // loop through dates, caculating interest daily etc
    while(true)
    {
        // if min repay day
        if(currentDate->tm_mday == runningContext->minRepayDay && principal > 0.0f)
        {
            processMinRepayment(&principal, runningContext, currentDate, monthlyInterest, output);
        }
        // if extra repay day
        if(currentDate->tm_mday == runningContext->extraRepayDay && runningContext->extraRepayAmount > 0.0f && principal > 0.0f)
        {
            processExtraRepayment(&principal, runningContext, currentDate);
        }
        
        // if principal is zero or less - we are done!
        if(principal <= 0.0f) break;
        // calculate the daily interest
        monthlyInterest += calculateDailyInterest(principal, runningContext->interestRate);
        // if this is the first iteration and we did not start on the first of the month
        // let's calculate the interest for the days back to the first
        if(firstIteration && runningContext->startDate.tm_mday != 1)
        {
            int daysToMonthStart = currentDate->tm_mday - 1;
            monthlyInterest += (monthlyInterest * daysToMonthStart);
            firstIteration = false;
        }
        // move date forward
        nextDate = *currentDate;
        nextDate.tm_mday = nextDate.tm_mday + 1;
        mktime(&nextDate);
        // if end of month
        if(currentDate->tm_mon != nextDate.tm_mon)
        {
            processEndOfMonth(currentDate, &monthlyInterest, &principal, output);
        }
        *currentDate = nextDate;
    }
    return(output);
}

/*
 ***************************************
 ** Processes the end of month, adds
 ** interest to the principal.
 ***************************************
 */
void processEndOfMonth(dateTime *currentDate, float *monthlyInterest, float *principal, calculationOutput *output)
{
    // add interest charged transaction
    *principal += *monthlyInterest;
    // calculate the total interest paid
    output->totalInterestPaid += *monthlyInterest;
    addTransactionNode(&rootTransactionNode, &headTransactionNode, createTransaction(TX_TYPE_INTEREST_CHARGED, currentDate, 0.0f, *monthlyInterest, *principal));
    // reset for new month
    *monthlyInterest = 0.0f;
}

/*
 ***************************************
 ** Processes the extra repayment for the
 ** current date if applicable.
 ***************************************
 */
void processExtraRepayment(float *principal, context *runningContext, dateTime *currentDate)
{
    if(currentDate->tm_mday == runningContext->extraRepayDay && runningContext->extraRepayAmount > 0.0f && *principal > 0.0f)
    {
        // add extra repay transaction (if amount is more than 0)
        *principal -= runningContext->extraRepayAmount;
        addTransactionNode(&rootTransactionNode, &headTransactionNode, createTransaction(TX_TYPE_EXTRA_REPAYMENT, currentDate, runningContext->extraRepayAmount, 0.0f, *principal));
    }
}

/*
 ***************************************
 ** Processes the min repayment for the
 ** current date if applicable.
 ***************************************
 */
void processMinRepayment(float *principal, context *runningContext, dateTime *currentDate, float monthlyInterest, calculationOutput *output)
{
    // add min repay transaction
    if((*principal + monthlyInterest) <= runningContext->minRepayAmount)
    {
        float finalRepayment = 0.0f;
        output->loanEndsDate = *currentDate;
        *principal += monthlyInterest;
        finalRepayment = *principal;
        *principal -= finalRepayment;
        addTransactionNode(&rootTransactionNode, &headTransactionNode, createTransaction(TX_FINAL_REPAYMENT, currentDate, finalRepayment, monthlyInterest, *principal));
    }
    else
    {
        *principal -= runningContext->minRepayAmount;
        addTransactionNode(&rootTransactionNode, &headTransactionNode, createTransaction(TX_TYPE_MIN_REPAYMENT, currentDate, runningContext->minRepayAmount, 0.0f, *principal));
    }
}

/*
 ***************************************
 ** Calculates the interest for a day.
 ***************************************
 */
float calculateDailyInterest(float principal, float interestRate)
{
    float result = 0.0f;
    result = (principal * (interestRate / 100)) / NUM_DAYS_IN_YEAR;
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
    if(!checkAllocation(tmp)) return (NULL);
    tmp->transactionType = type;
    tmp->debit = charge;
    tmp->remainPrincipalAmount = remainPrincipal;
    tmp->credit = repayment;
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
void printCalculations(calculationOutput *output)
{
    transactionNode *current = rootTransactionNode;
    while(current != NULL)
    {
        printf(TRANSACTION_FORMAT_PATTERN,
               formatDate(&(current->item->transactionDate), DATE_FORMAT),
               current->item->transactionType,
               current->item->credit,
               current->item->debit,
               current->item->remainPrincipalAmount);
        current = current->next;
    }
    printf(LOAN_PAID_OFF_FORMAT_PATTERN,
           formatDate(&(output->loanEndsDate), DATE_FORMAT),
           formatDate(&(output->interestStartDate), DATE_FORMAT),
           formatDate(&(output->loanEndsDate), DATE_FORMAT),
           output->totalInterestPaid);
}

/*
 ***************************************
 ** Prints the program output to a file.
 ***************************************
 */
void printOutputToFile(dateTime *currentDate, calculationOutput *output)
{
    transactionNode *current = rootTransactionNode;
    char *filename = buildOutputFilename(currentDate);
    FILE *outputFile = fopen(filename, "w+");
    
    fprintf(outputFile, OUTPUT_HEADER_PATTERN_FORMAT,
           PROGRAM_NAME,
           formatDate(&(runningContext->todaysDate), DATE_FORMAT),
           formatDate(&(runningContext->startDate), DATE_FORMAT),
           runningContext->principalAmount,
           runningContext->interestRate,
           runningContext->minRepayAmount,
           runningContext->minRepayDay,
           runningContext->extraRepayAmount,
           runningContext->extraRepayDay
           );
    
    while(current != NULL)
    {
        fprintf(outputFile, TRANSACTION_FORMAT_PATTERN,
               formatDate(&(current->item->transactionDate), DATE_FORMAT),
               current->item->transactionType,
               current->item->credit,
               current->item->debit,
               current->item->remainPrincipalAmount);
        current = current->next;
    }
    
    fprintf(outputFile, LOAN_PAID_OFF_FORMAT_PATTERN,
           formatDate(&(output->loanEndsDate), DATE_FORMAT),
           formatDate(&(output->interestStartDate), DATE_FORMAT),
           formatDate(&(output->loanEndsDate), DATE_FORMAT),
           output->totalInterestPaid);
    
    printf("Results output to file '%s'.", filename);

    fclose(outputFile);
}

/*
 ***************************************
 ** Builds the filename for program output.
 ***************************************
 */
char* buildOutputFilename(dateTime *currentDate)
{
    char *date = formatDate(currentDate, DATE_FORMAT_FOR_FILENAME);
    unsigned long size = strlen(PROGRAM_NAME) + 1 + strlen(date) + 1;
    char *result = malloc(sizeof(char) * size);
    if(!checkAllocation(result)) return (NULL);
    strcat(result, PROGRAM_NAME);
    strcat(result, ".");
    strcat(result, date);
    strcat(result, ".out.txt");
    return(result);
}

/*
 ***************************************
 ** Formats a date as a string.
 ***************************************
 */
char* formatDate(dateTime *target, const char *dateFormat)
{
    char *result = malloc(sizeof(char) * 11);
    if(!checkAllocation(result)) return (NULL);
    strftime(result, 11, dateFormat, target);
    return(result);
}

/*
 ***************************************
 ** Check memory was allocated as expected.
 ***************************************
 */
bool checkAllocation(void *target)
{
    if(target != NULL) return (true);
    else {
        printf("Out of memory, could not allocate.");
        return(true);
    }
}
