//
//  main.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "Global.h"
#include "LoanContext.h"
#include "LoanCalculationOutput.h"
#include "LoanCalculator.h"
#include "LoanCalculationOuputWriter.h"

using namespace std;

// function prototypes
void processArguments(int argc, const char* argv[], LoanContext *context);
void printUsage();

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
    LoanCalculationOuputWriter *writer = NULL;
    
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
        calculator = new LoanCalculator(*context);
        output = new LoanCalculationOutput();
        *output = calculator->calculateLoan();

        writer = new LoanCalculationOuputWriter(*context, *output);
        writer->OutputConsole();
        writer->OutputFile();
    
        // cleanup dynamically allocated variables
        delete(todaysDate);
        delete(context);
        delete(calculator);
        delete(output);
        delete(writer);
        
    } catch (exception ex) {
        cout << "Unhandled exception occurred. " << ex.what() << endl;
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
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
    context->setBalance((double) atof(argv[3]));
    context->setInterestRate((double) atof(argv[4]));
    context->setMinRepaymentAmount((double) atof(argv[5]));
    context->setMinRepaymentDay((int) atoi(argv[6]));
    context->setExtraRepaymentAmount((double) atof(argv[7]));
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