# julian_to_date

## Introduction

This method converts a Julian date to date and time.

## Function Prototype

The function prototype of this function is:

double *julian_to_date(double julian_date);
 
### The parameters:
The function of the parameters is:

julian_date	- The Julian date
 
### The output: 

The output is a pointer to an array of six doubles. The value of each element in the array is:

		Field		Content
		  0		    Year
		  1		    Month
		  2		    Day
		  3		    Hours
		  4		    Minutes
		  5		    Seconds

## Example code

The example is example-004.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)