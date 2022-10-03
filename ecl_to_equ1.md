# ecl_to_equ

## Introduction

This method converts geo ecliptic co_ordinates to equatorial co-ordinates.

## Function Prototype

The function prototype of this function is:
  
double *ecl_to_equ(double ecl[],int year,int month,int day,int hour,int minute,double sec,double offset); 
 
### The parameters:
The function of the parameters is:

	ecl			- Pointer to the array that hold the geo ecliptic co-ordinates.
				  The elements in this array are:

				  ecl[0] 		= lambda (degrees)
				  ecl[1] 		= beta (degrees)				 

	year			--: 
	month			  : 
	day			      :-- The date and time of the observer.
	hour			  :
	min			      :
	secs			  :
	time_offset		--:

### The output: 
The output is a pointer to an array of two doubles. The value of each element in the array is:

	element 0 = RA (decimal hours)
	element 1 = DEC (in degrees)

## Example code

The example is example-016.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)