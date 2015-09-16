//
//  LoanCalculationOuputWriter.h
//  Kata.LoanPrediction.C++
//
//  Created by Andrew Dowding on 11/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanCalculationOuputWriter__
#define __Kata_LoanPrediction_C____LoanCalculationOuputWriter__

#include "Global.h"
#include "LoanContext.h"
#include "LoanCalculationOutput.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

/*
 ***************************************
 ** Writes the calculation output to 
 ** an output stream, such as the console
 ** or a file.
 ***************************************
 */
class LoanCalculationOuputWriter
{
public:
    LoanCalculationOuputWriter(LoanContext context, LoanCalculationOutput output, dateTime currentDate);
    void OutputConsole();
    void OutputFile();
    
private:
    string buildOutputFilename(dateTime currentDate);
    void printOutputHeader(LoanContext &context, ostream &out);
    void printCalculations(LoanContext &context, LoanCalculationOutput &output, ostream &out);
    void formatDate(dateTime target, const char *dateFormat, char *buffer, int bufferSize);
    LoanContext context;
    LoanCalculationOutput output;
    dateTime todaysDate;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanCalculationOuputWriter__) */
