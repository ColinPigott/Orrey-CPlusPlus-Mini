# lst

## Introduction

This method is used to work out the Local Siderial Time(LST).

## Function Prototype
 
The function prototype of this function is:

	double lst(int year, int month, int day,int hour,int min,double secs,double time_offset,double longitude);

### The parameters:
The function of the parameters is:

	year				--: 
	month				  : 
	day				      :-- The date and time of the observer.
	hour				  :
	min				      :
	secs				--:
	longitude		- Longitude of the observer (degrees).
					  	- West is negative, i.e. 64 W is -64.
					  	- East is positive, i.e. 64 E is 64

### The output: 

The output is a double and is the Local Siderial Time(LST).

## Example code

The example is example-007.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)