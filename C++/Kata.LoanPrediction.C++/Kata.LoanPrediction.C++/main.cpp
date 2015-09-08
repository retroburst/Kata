//
//  main.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Global.h"
#include "LoanContext.h"
#include "LoanCalculationOutput.h"
#include "LoanCalculator.h"

using namespace std;

// function prototypes
void processArguments(int argc, const char* argv[], LoanContext *context);
void printUsage();
void formatDate(dateTime target, const char *dateFormat, char *buffer, int bufferSize);
void printOutputHeader(LoanContext *context, ostream& out);
void printCalculations(LoanContext *context, LoanCalculationOutput *output, ostream& out);
string buildOutputFilename(dateTime currentDate);

/*
 ***************************************
 ** Entry point for program.
 ***************************************
 */
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
        printOutputHeader(context, cout);
        calculator = new LoanCalculator(*context);
        output = new LoanCalculationOutput();
        *output = calculator->calculateLoan();
        printCalculations(context, output, cout);
        
        ofstream outFile;
        outFile.open(buildOutputFilename(*todaysDate));
        printOutputHeader(context, outFile);
        printCalculations(context, output, outFile);
        outFile.close();
        
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
void printCalculations(LoanContext *context, LoanCalculationOutput *output, ostream& out)
{
    const vector<LoanTransaction> *transactions = output->getTransactionList();
    out.precision(2);
    out << fixed;
    char *interestCalcStartDateString = new char[11];
    formatDate(output->getInterestStartDate(), DATE_FORMAT, interestCalcStartDateString, 11);
    char *loanEndDateString = new char[11];
    formatDate(output->getLoanEndsDate(), DATE_FORMAT, loanEndDateString, 11);
    char *targetEndDateString = new char[11];
    formatDate(context->getTargetEndDate(), DATE_FORMAT, targetEndDateString, 11);
    
    int i=0;
    for(i=0; i < transactions->size(); i++)
    {
        LoanTransaction t = transactions->at(i);
        dateTime targetEndDate = context->getTargetEndDate();
        dateTime transactionDate = t.getDate();
        char *transactionDateString = new char[11];
        formatDate(transactionDate, DATE_FORMAT, transactionDateString, 11);
        bool isTargetDate = transactionDate.tm_year == targetEndDate.tm_year && transactionDate.tm_mon == targetEndDate.tm_mon;
        
        if(isTargetDate) out << setw(3) << "^T ";
        else out << setw(3) << "";
        out << setw(11) << transactionDateString;
        out << setw(3) << " - " << setw(17) << left << t.getType() << setw(2) << " -" << right
                << " Credit: " << setw(8) << t.getCredit()
                << " Debit: " << setw(8) << t.getDebit()
                << " Balance: " << setw(10) << t.getBalance() << endl;
        
        delete(transactionDateString);
    }
    out << endl << "Loan is paid off on " << loanEndDateString << ", total interest paid from " << interestCalcStartDateString << " to " << loanEndDateString << " is $" << output->getTotalInterestPaid() << "." << endl;
    
    if(output->getTargetEndDateHit()) out << endl << "Target end date of " << targetEndDateString << " was hit perfectly." << endl;
    else out << endl << "Target end date of " << targetEndDateString << " was missed by " << output->getTargetEndDateMissedInDays() << " days." << endl;
    
    delete(interestCalcStartDateString);
    delete(loanEndDateString);
    delete(targetEndDateString);
}

/*
 ***************************************
 ** Builds the filename for program output.
 ***************************************
 */
string buildOutputFilename(dateTime currentDate)
{
    char *date = new char[11];
    formatDate(currentDate, DATE_FORMAT_FOR_FILENAME, date, 11);
    string result;
    result.append(PROGRAM_NAME);
    result.append(".");
    result.append(date);
    result.append(".out.txt");
    delete(date);
    return(result);
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
    context->setBalance((float) atof(argv[3]));
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
            << "balance interestRate minRepayAmount "
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
void printOutputHeader(LoanContext *context, ostream& out)
{
    char *todaysDateString = new char[11];
    formatDate(context->getTodaysDate(), DATE_FORMAT, todaysDateString, 11);
    char *startDateString = new char[11];
    formatDate(context->getStartDate(), DATE_FORMAT, startDateString, 11);
    char *targetEndDateString = new char[11];
    formatDate(context->getTargetEndDate(), DATE_FORMAT, targetEndDateString, 11);
    
    out.precision(2);
    out << fixed;
    out << PROGRAM_NAME
            << "\n\nToday's Date: " << todaysDateString << endl
            << "Start Date: " << startDateString << endl
            << "Target End Date: " << targetEndDateString << endl
            << "Balance: " << context->getBalance() << endl
            << "Interest Rate: " << context->getInterestRate() << endl
            << "Min. Repayment Amount: " << context->getMinRepaymentAmount() << endl
            << "Min. Repayment Day: " << context->getMinRepaymentDay() << endl
            << "Extra Repayment: " << context->getExtraRepaymentAmount() << endl
            << "Extra Repayment Day: " << context->getExtraRepaymentDay() << endl << endl;
    
    delete(todaysDateString);
    delete(startDateString);
    delete(targetEndDateString);
}




