# lst

## Introduction

This method is used to work out the Local Siderial Time(LST).

## Function Prototype
 
The function prototype of this function is:

  	double lst(double julian_date,double longitude);

### The parameters:
The function of the parameters is:

	julian_date		- The date and time of the observer as a Julian date.
	longitude		- Longitude of the observer (degrees).
				  		- West is negative, i.e. 64 W is -64.
				  		- East is positive, i.e. 64 E is 64

### The output: 

The output is a double and is the Local Siderial Time(LST).

## Example code

The example is example-008.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)