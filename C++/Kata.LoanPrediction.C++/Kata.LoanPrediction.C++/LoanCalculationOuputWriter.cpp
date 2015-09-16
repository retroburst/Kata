//
//  LoanCalculationOuputWriter.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 11/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "LoanCalculationOuputWriter.h"

/*
 ***************************************
 ** Default constructor.
 ***************************************
 */
LoanCalculationOuputWriter::LoanCalculationOuputWriter(LoanContext context, LoanCalculationOutput output, dateTime todaysDate)
{
    this->context = context;
    this->output = output;
    this->todaysDate = todaysDate;
}

/*
 ***************************************
 ** Outputs the calculations to the
 ** console out stream.
 ***************************************
 */
void LoanCalculationOuputWriter::OutputConsole()
{
    printOutputHeader(context, cout);
    printCalculations(context, output, cout);
}

/*
 ***************************************
 ** Outputs the calculations to an
 ** output file stream.
 ***************************************
 */
void LoanCalculationOuputWriter::OutputFile()
{
    ofstream outFile;
    outFile.open(buildOutputFilename(todaysDate));
    printOutputHeader(context, outFile);
    printCalculations(context, output, outFile);
    outFile.close();
}

/***************************************
 ** Prints the calculations to the console
 ** and the date on which the loan
 ** will be paid off.
 ***************************************
 */
void LoanCalculationOuputWriter::printCalculations(LoanContext &context, LoanCalculationOutput &output, ostream &out)
{
    const vector<LoanTransaction> *transactions = output.getTransactionList();
    out.precision(2);
    out << fixed;
    char *interestCalcStartDateString = new char[11];
    formatDate(output.getInterestStartDate(), DATE_FORMAT, interestCalcStartDateString, 11);
    char *loanEndDateString = new char[11];
    formatDate(output.getLoanEndsDate(), DATE_FORMAT, loanEndDateString, 11);
    char *targetEndDateString = new char[11];
    formatDate(context.getTargetEndDate(), DATE_FORMAT, targetEndDateString, 11);
    
    int i=0;
    for(i=0; i < transactions->size(); i++)
    {
        LoanTransaction t = transactions->at(i);
        dateTime targetEndDate = context.getTargetEndDate();
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
    out << endl << "Loan is paid off on " << loanEndDateString << ", total interest paid from " << interestCalcStartDateString << " to " << loanEndDateString << " is $" << output.getTotalInterestPaid() << "." << endl;
    
    if(output.getTargetEndDateHit()) out << endl << "Target end date of " << targetEndDateString << " was hit perfectly." << endl;
    else out << endl << "Target end date of " << targetEndDateString << " was missed by " << output.getTargetEndDateMissedInDays() << " days." << endl;
    
    delete(interestCalcStartDateString);
    delete(loanEndDateString);
    delete(targetEndDateString);
}

/*
 ***************************************
 ** Builds the filename for program output.
 ***************************************
 */
string LoanCalculationOuputWriter::buildOutputFilename(dateTime currentDate)
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
 ** Formats a date as a string.
 ***************************************
 */
void LoanCalculationOuputWriter::formatDate(dateTime target, const char *dateFormat, char *buffer, int bufferSize)
{
    strftime(buffer, bufferSize, dateFormat, &target);
}

/*
 ***************************************
 ** Prints the program name,
 ** arguments provided by the user etc.
 ***************************************
 */
void LoanCalculationOuputWriter::printOutputHeader(LoanContext &context, ostream &out)
{
    char *todaysDateString = new char[11];
    formatDate(context.getTodaysDate(), DATE_FORMAT, todaysDateString, 11);
    char *startDateString = new char[11];
    formatDate(context.getStartDate(), DATE_FORMAT, startDateString, 11);
    char *targetEndDateString = new char[11];
    formatDate(context.getTargetEndDate(), DATE_FORMAT, targetEndDateString, 11);
    
    out.precision(2);
    out << fixed;
    out << PROGRAM_NAME
    << "\n\nToday's Date: " << todaysDateString << endl
    << "Start Date: " << startDateString << endl
    << "Target End Date: " << targetEndDateString << endl
    << "Balance: " << context.getBalance() << endl
    << "Interest Rate: " << context.getInterestRate() << endl
    << "Min. Repayment Amount: " << context.getMinRepaymentAmount() << endl
    << "Min. Repayment Day: " << context.getMinRepaymentDay() << endl
    << "Extra Repayment: " << context.getExtraRepaymentAmount() << endl
    << "Extra Repayment Day: " << context.getExtraRepaymentDay() << endl << endl;
    
    delete(todaysDateString);
    delete(startDateString);
    delete(targetEndDateString);
}