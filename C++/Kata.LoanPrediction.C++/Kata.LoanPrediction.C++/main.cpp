//
//  main.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include <time.h>
#include <iostream>
#include <string>
#include <iomanip>
#include "Global.h"
#include "LoanContext.h"
#include "LoanCalculationOutput.h"
#include "LoanCalculator.h"

//TODO: principal should be renamed balance (as principal is just the original amout lent)

using namespace std;

// function prototypes
void processArguments(int argc, const char* argv[], LoanContext *context);
void printUsage();
void formatDate(dateTime target, const char *dateFormat, char *buffer, int bufferSize);
void printOutputHeader(LoanContext *context);
void printCalculations(LoanCalculationOutput *output);

int main(int argc, const char * argv[]) {
    // variables
    dateTime *todaysDate = NULL;
    LoanContext *context = NULL;
    LoanCalculationOutput *output = NULL;
    LoanCalculator *calculator = NULL;
    
    try {
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
            context = new LoanContext();
            processArguments(argc, argv, context);
            context->setTodaysDate(*todaysDate);
        }
        printOutputHeader(context);
        calculator = new LoanCalculator(*context);
        output = new LoanCalculationOutput();
        *output = calculator->calculateLoan();
        printCalculations(output);
        delete(todaysDate);
        delete(context);
        delete(calculator);
        delete(output);
    } catch (exception ex) {
        cout << "Unhandled exception occurred. " << ex.what() << endl;
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

/* TODO move this and the file output into a CalcOutputWriter class
 ***************************************
 ** Prints the calculations to the console
 ** and the date on which the loan
 ** will be paid off.
 ***************************************
 */
void printCalculations(LoanCalculationOutput *output)
{
    const vector<LoanTransaction> *transactions = output->getTransactionList();
    cout.precision(2);
    cout << fixed;
    int i=0;
    for(i=0; i < transactions->size(); i++)
    {
        LoanTransaction t = transactions->at(i);
        char *transactionDate = new char[11];
        formatDate(t.getDate(), DATE_FORMAT, transactionDate, 11);
        
        // todo indicate where the target end date comes if it exists in transactions
        // targetEndDate <= transactionDate
        
        cout << transactionDate  << " - " << setw(17) << t.getType() << " -"
        << " Credit: " << setw(8) << t.getCredit()
        << " Debit: " << setw(8) << t.getDebit()
        << " Balance: " << setw(8) << t.getPrincipalBalance() << endl;
        
        //<< "Loan is paid off on " << " total interest paid from %s to %s is $%.2f.
        
        delete(transactionDate);
    }
    
    
    
    /*
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
     */
}

/*
 ***************************************
 ** Process the command line arguments
 ** and bundles them in a context struct.
 ***************************************
 */
void processArguments(int argc, const char* argv[], LoanContext *context)
{
    dateTime *startDate = new dateTime();
    dateTime *targetEndDate = new dateTime();
    strptime(argv[1], DATE_FORMAT, startDate);
    strptime(argv[2], DATE_FORMAT, targetEndDate);
    context->setStartDate(*startDate);
    context->setTargetEndDate(*targetEndDate);
    context->setPricipal((float) atof(argv[3]));
    context->setInterestRate((float) atof(argv[4]));
    context->setMinRepaymentAmount((float) atof(argv[5]));
    context->setMinRepaymentDay((int) atoi(argv[6]));
    context->setExtraRepaymentAmount((float) atof(argv[7]));
    context->setExtraRepaymentDay((int) atoi(argv[8]));
    delete(startDate);
    delete(targetEndDate);
}

/*
 ***************************************
 ** Prints the usage directive to the
 ** console.
 ***************************************
 */
void printUsage()
{
    cout << "Usage: " << PROGRAM_NAME << " startDate(dd/mm/yyyy) targetEndDate(dd/mm/yyyy) "
            << "principalAmount interestRate minRepayAmount "
            << "minRepayDay extraRepayAmount extraRepayDay\n"
            << "Example: " << PROGRAM_NAME << " 23/12/2015 23/12/2018 20000.00 5.74 1500.00 18 1200.00 15"
            << endl;
}

/*
 ***************************************
 ** Formats a date as a string.
 ***************************************
 */
void formatDate(dateTime target, const char *dateFormat, char *buffer, int bufferSize)
{
    strftime(buffer, bufferSize, dateFormat, &target);
}

/*
 ***************************************
 ** Prints the program name,
 ** arguments provided by the user etc.
 ***************************************
 */
void printOutputHeader(LoanContext *context)
{
    char *todaysDateString = new char[11];
    formatDate(context->getTodaysDate(), DATE_FORMAT, todaysDateString, 11);
    char *startDateString = new char[11];
    formatDate(context->getStartDate(), DATE_FORMAT, startDateString, 11);
    char *targetEndDateString = new char[11];
    formatDate(context->getTargetEndDate(), DATE_FORMAT, targetEndDateString, 11);

    cout.precision(2);
    cout << fixed;
    cout << PROGRAM_NAME
            << "\n\nToday's Date: " << todaysDateString << endl
            << "Start Date: " << startDateString << endl
            << "Target End Date: " << targetEndDateString << endl
            << "Principal: " << context->getPrincipal() << endl
            << "Interest Rate: " << context->getInterestRate() << endl
            << "Min. Repayment Amount: " << context->getMinRepaymentAmount() << endl
            << "Min. Repayment Day: " << context->getMinRepaymentDay() << endl
            << "Extra Repayment: " << context->getExtraRepaymentAmount() << endl
            << "Extra Repayment Day: " << context->getExtraRepaymentDay() << endl;
    
    delete(todaysDateString);
    delete(startDateString);
    delete(targetEndDateString);
}




