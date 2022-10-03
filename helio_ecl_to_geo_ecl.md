# helio_ecl_to_geo_ecl

## Introduction

This method can be used to convert helio ecliptic co_ordinates to geo ecliptic co_ordinates and visa versa.

## Function Prototype

The function prototype of this function is:
  
  double *helio_ecl_to_geo_ecl(double lambda_o,double beta_o,double dist_o,double lambda_e,double beta_e,double dist_e);
 
### The parameters:
The function of the parameters and the output depends on which way the conversion is being done.

Finding the helio ecliptic co-ord of the Earth from the geo ecliptic of the Sun:
1. Find the geo co-ord of the Sun
2. helio ecliptic longitude = geo ecliptic longitude + 180
3. helio ecliptic latitude  = - geo ecliptic latitude
4. helio ecliptic distance  = distance between the the Sun and the Earth.	

For everything else, the conversion is more complex.	
	
### Convert helio ecliptic co-ords to geo ecliptic co-ords:
 
The function of the parameters is:

	lambda_o	= helio ecliptic longitude of object (degrees)
	beta_o		= helio ecliptic latitude of object (degrees)
	dist_o		= distance of object from Sun (AU)
	lambda_e	= helio ecliptic longitude of Earth (degrees)
	beta_e		= helio ecliptic latitude of Earth (degrees)
	dist_e		= distance between Earth and the Sun (AU).

The output is in the form of pointer to an array of three doubles.  
The value of each element in the array is:

	element 0	= geo ecliptic longitude of object (degrees) 
	element 1	= geo ecliptic latitude of object (degrees)
	element 2	= distance of object from the Earth (AU)


### Convert geo ecliptic co-ords to helio ecliptic co-ords:

The function of the parameters is:
 
	lambda_o	= geo ecliptic longitude of object (degrees)
	beta_o		= geo ecliptic latitude of object (degrees)
	dist_o		= distance of object from Earth (AU)
	lambda_e	= geo ecliptic longitude of the Sun (degrees)
	beta_e		= geo ecliptic latitude of the Sun (degrees)
	dist_e		= distance between Earth and the Sun (AU).

The output is in the form of pointer to an array of three doubles.  
The value of each element in the array is:

	element 0	= helio ecliptic longitude of object (degrees) 
	element 1	= helio ecliptic latitude of object (degrees)
	element 2	= distance of object from the Sun (AU)

## Example code

An example of helio to geo co-ord converstion is example-019.cpp.  
An example of geo to helio coord conversion is example-018.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)
