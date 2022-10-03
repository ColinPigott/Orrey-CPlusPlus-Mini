# equ_to_hor

## Introduction

This method converts equatorial co_ordinates to horizon co-ordinates.

## Function Prototype

The function prototype of this function is:
  
  double *equ_to_hor(double julian_date,double ra,double dec,double latitude,double longitude);
 
### The parameters:
The function of the parameters is:

	julian_date = The date and time of the observer (Julian days).
	ra          = The RA of the object (decimal hours).
	dec         = The DEC of the object (decimal degrees).
	latitude    = The latitude of the observer (degrees).
    longitude   = The longitude of the observer (degrees)
	
### The output: 
The output is a pointer to an array of two doubles.  
The value of each element in the array is:

	element 0 = altitude (in degrees)
	element 1 = azimuth (in degrees) 
 
## Example code

The example is example-012.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)
 