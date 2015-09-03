//
//  LoanCalculator.h
//  Kata.LoanPrediction.C++
//
//  Created by Andrew Dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C____LoanCalculator__
#define __Kata_LoanPrediction_C____LoanCalculator__

#include <stdio.h>
#include "Global.h"
#include "LoanContext.h"
#include "LoanCalculationOutput.h"

class LoanCalculator
{
public:
    LoanCalculator(LoanContext *context);
    ~LoanCalculator();
    LoanCalculationOutput* CalculateLoan();
private:
    LoanContext *context;
    LoanCalculationOutput *output;
};

#endif /* defined(__Kata_LoanPrediction_C____LoanCalculator__) */
