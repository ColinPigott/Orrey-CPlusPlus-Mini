# star_rise_set

## Introduction

This method works out the rise,transit and set times and their azimuth angles of a star of a user at a set date and time.

## Function prototype

The function prototype of this function is:
 		       
  double *star_rise_set(double julian_date,double longitude,double latitude,double *star_eq_coords);
  
### The parameters:  
The function of the parameters is:

| Parameter | Purpose |
| --------- | ------- |
| julian_date | The date and time of the user as a Julian date. |
| longitude | Longitude of the user (degrees). |
| latitude | The latitude of the user (degrees). |
| star_eq_coords | A pointer to the array that holds the equatorial co-ordinates of the star: |
	
			star_eq_coords[0] = RA in decimal hours
			star_eq_coords[1] = DEC in decimal degrees 

### The output:   
The output is a pointer to an array of five doubles.  
The value of each element in the array is:

| Element | Value held |
| :-------: | :---------- |
| 0 | Azimuth of the selected object to rise (degrees). |
| 1 | Azimuth of the selected object to set (degrees). |		 
| 2 | Time of the object rising (Julian date). |
| 3 | Time of the object setting (Julian date). |
| 4 | Time of when the object is in transit (Julian date). |

## Example code

The example is example-002.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)