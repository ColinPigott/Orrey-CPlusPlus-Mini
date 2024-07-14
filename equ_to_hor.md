# equ_to_hor

## Introduction

This method converts equatorial co_ordinates to horizon co-ordinates.

## Function Prototype

The function prototype of this function is:
  
  double *equ_to_hor(double hour_angle,double dec,double latitude);
 
### The parameters:
The function of the parameters is:

	hour_angle = The RA as an hour angle (degrees).
	dec        = The DEC of the object.
	latitude   = The latitude of the observer (degrees).
	
### The output: 
The output is a pointer to an array of two doubles.  
The value of each element in the array is:

	element 0 = altitude (in degrees)
	element 1 = azimuth (in degrees) 
 
## Example code

The example is example-012.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)
 