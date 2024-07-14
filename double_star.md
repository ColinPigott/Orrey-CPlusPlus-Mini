# Double star

## Introduction

This method works out the position of a binary star around it's origin.

## Function prototype

The function prototype of this function is:
  
  double* double_star(int year,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int month,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int day,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int hour,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int min,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double secs,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double time_offset,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double period,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double periastron,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double semi_major,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double e,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double i,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double w,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double pa);  
 
### The parameters:  
The function of the parameters is:

| <div style="width:200px">Parameter</div> | Purpose |
| --------- | ------- |
| year | The year of the user. |
| month	| The month of the user. |
| day |	The day of the user. |
| hour | The hour of the user. |
| min | The minute of the user. |
| secs | The seconds of the user. |
| time_offset | The time offset of the user from UT. |
| period | The period of the binary star (mean solar years). |
| periastron | Epoch of periastron. |
| semi_major | Semi-major axis of orbit (arcsec). |
| e | Eccentricity. |
| i | Inclination or orbit (degrees). |
| w | Longitude of periastron (degrees).
| pa | Position angle of ascending node (degrees). |
 
### The output: 
The output is a pointer to an array of two doubles.   
The value of each element in the array is:

| <div style="width:200px">Element</div> | Value held |
| :-------: | :---------- |
|    0 | Angle from north (degrees). |
|    1  | Distance from the central star (arc seconds). | 

## Example code

The example is example-001.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)
 