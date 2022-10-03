# ecl_to_equ

## Introduction

This method converts geo ecliptic co_ordinates to equatorial co-ordinates.

## Function Prototype

The function prototype of this function is:
  
double *ecl_to_equ(double *ecl,double julian_date); 
 
### The parameters:
The function of the parameters is:

	ecl			- Pointer to the array that hold the geo ecliptic co-ordinates.
				  The elements in this array are:

				  ecl[0] 		= lambda (degrees)
				  ecl[1] 		= beta (degrees)				 

	julian_date	- The date and time of the observer as a Julian date.

### The output: 
The output is a pointer to an array of two doubles. The value of each element in the array is:

	element 0 = RA (decimal hours)
	element 1 = DEC (in degrees)

## Example code

The example is example-017.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)