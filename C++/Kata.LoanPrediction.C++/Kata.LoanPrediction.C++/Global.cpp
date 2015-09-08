//
//  Global.cpp
//  Kata.LoanPrediction.C++
//
//  Created by a.j.dowding on 3/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include "Global.h"

int compareDates(dateTime x, dateTime y)
{
    if(x.tm_year > y.tm_year
       || (x.tm_year == y.tm_year && x.tm_mon > y.tm_mon)
       || (x.tm_year == y.tm_year && x.tm_mon == y.tm_mon && x.tm_mday > y.tm_mday))
    {
        return(1);
    }
    else if(x.tm_year < y.tm_year
            || (x.tm_year == y.tm_year && x.tm_mon < y.tm_mon)
            || (x.tm_year == y.tm_year && x.tm_mon == y.tm_mon && x.tm_mday < y.tm_mday))
    {
        return(-1);
    }
    else
    {
        return(0);
    }
}