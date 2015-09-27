//
//  Global.cpp
//  Kata.LoanPrediction.C++
//
//  Created by retroburst [Andrew D] on 3/09/2015.
//  Copyright (c) 2015 retroburst [Andrew D]. All rights reserved.
//

#include "Global.h"

/*
 ***************************************
 ** Compares two dates, return codes:
 ** 0 = equal,
 ** 1 = x > y,
 ** -1 = x < y
 ***************************************
 */
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

/*
 ***************************************
 ** Calculates the number of days in a
 ** month of a particular year.
 ***************************************
 */
int daysInMonth(int month, int year)
{
    int leapYear = 0;
    int result = 0;
    if(isLeapYear(year)) leapYear = 1;
    if (month == 2) {
        result = 28 + leapYear;
    } else {
        result = 31 - (month - 1) % 7 % 2;
    }
    return(result);
}

/*
 ***************************************
 ** Calculates if the year is a leap
 ** year.
 ***************************************
 */
bool isLeapYear(int year)
{
    bool result = false;
    int isLeap = ((year % 4) || ((year % 100 == 0) && (year % 400))) ? 0 : 1;
    if(isLeap == 1) result = true;
    return(result);
}

/*
 ***************************************
 ** Add a day to a date, moving the date
 ** to the next month and year where
 ** applicable. This was introduced as
 ** mktime was intermittently returning
 ** dates with a corrupted year.
 ***************************************
 */
void addDay(dateTime *target)
{
    int month = target->tm_mon + 1;
    int year = target->tm_year + 1900;
    int numDaysInMonth = daysInMonth(month, year);
    if(target->tm_mday == numDaysInMonth)
    {
        if(month == 12)
        {
            target->tm_year = target->tm_year + 1;
            target->tm_mon = 0;
            target->tm_mday = 1;
        }
        else
        {
            target->tm_mon = target->tm_mon + 1;
            target->tm_mday = 1;
        }
        return;
    }
    target->tm_mday = target->tm_mday + 1;
}

/*
 ***************************************
 ** Minus a day from date, moving the date
 ** to the previous month and year where
 ** applicable. This was introduced as
 ** mktime was intermittently returning
 ** dates with a corrupted year.
 ***************************************
 */
void minusDay(dateTime *target)
{
    if(target->tm_mday == 1)
    {
        if(target->tm_mon + 1 == 1)
        {
            target->tm_year = target->tm_year - 1;
            target->tm_mon = 11;
            target->tm_mday = daysInMonth(target->tm_mon + 1, target->tm_year + 1900);
        }
        else
        {
            target->tm_mon = target->tm_mon - 1;
            target->tm_mday = daysInMonth(target->tm_mon + 1, target->tm_year + 1900);
        }
        return;
    }
    target->tm_mday = target->tm_mday - 1;
}