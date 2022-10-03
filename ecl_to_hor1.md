# ecl_to_hor

## Introduction

This method converts geo ecliptic co_ordinates to horizon co-ordinates.

## Function Prototype

The function prototype of this function is:
  
  double *ecl_to_hor(double *ecl,
  		     int year, 
  		     int month, 
  		     int day, 
  		     int hour, 
  		     int minute, 
  		     double seconds, 
  		     double time_offset, 
  		     double longitude,
  		     double latitude);
 
### The parameters:
The function of the parameters is:

	ecl			- Pointer to the array that hold the geo ecliptic co-ordinates.
				  The elements in this array are:

				  ecl[0] 		= lambda (degrees)
				  ecl[1] 		= beta (degrees)				 

	year		--: 
	month		  : 
	day			  :-- The date and time of the observer.
	hour		  :
	min			  :
	secs		  :
	time_offset	--:
	longitude	- Longitude of the observer (degrees).
				  - West is negative, i.e. 64 W is -64.
				  - East is positive, i.e. 64 E is 64
	latitude	- Latitude of the observer (degrees).
				  - North is positive, i.e. 51 N is 51.
				  - South is negative, i.e. 51 S is -51.

### The output: 
The output is a pointer to an array of three doubles.  
The value of each element in the array is:

	element 0 = RA (decimal hours)
	element 1 = DEC (in degrees)
	element 2 = hour angle (decimal hours)

## Example code

The example is example-014.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)