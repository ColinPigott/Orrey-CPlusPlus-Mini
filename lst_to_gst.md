# lst_to_gst

## Introduction

This method is used to convert Local Siderial Time (LST) to Greenwich Siderial Time (GST).

## Function Prototype

The function prototype of this function is:

  double lst_to_gst(double lst,double longitude);

### The parameters:
The function of the parameters is:

	lst			- The Local Siderial Time (LST) in decimal hours.
	longitude	- Longitude of the observer (degrees).
				  - West is negative, i.e. 64 W is -64.
				  - East is positive, i.e. 64 E is 64

### The output: 

The output is a double and is the Greenwich Siderial Time(LST).

## Example code

The example is example-009.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)

