# hor_to_eq

## Introduction

This method converts horizon co_ordinates to equatorial co-ordinates.

## Function Prototype

The function prototype of this function is:
  
    double *hor_to_equ(double altitude, double azimuth, double latitude,double longitude,double time);
 
### The parameters:
The function of the parameters is:

	altitude	= elevation of the object from the horizon (degrees) (hor co-ord).
	azimuth	    = angle from north to the object (degrees) (hor co-ord).
	latitude	= latitude of the observer (degrees).
	time		= Time of the observation (Julian date).

### The output: 
The output is a pointer to an array of three doubles. The value of each element in the array is:

	element 0 = RA (decimal hours)
	element 1 = DEC (in degrees)
	element 2 = hour angle (decimal hours)

## Example code

The example is example-013.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)
 