# Solar system objects

## Introduction

This function works out the details of the Sun, Moon and planets at the user's position and time. 

## Function prototype

The function prototype of this function is:

  struct astronomical_object *object_details(double julian_date,double longitude,double latitude);
  
### The parameters:
The function of the parameters is:

	julian_date	The date and time of the observer as a Julian date.
	longitude	Longitude of the observer (degrees).
			- West is negative, i.e. 64 W is -64.
			- East is positive, i.e. 64 E is 64
	latitude	The latitude of the observer (degrees).
			- North is positive, i.e. 51 N is 51.
			- South is negative, i.e. 51 S is -51.	
	
### The output: 
The output is a pointer to an array of ten astronomical_object structures that hold the details of the object.  
The definition of the astronomical_object structure is:

	struct astronomical_object
	{
	  double actual_geo_ecliptic_lambda;
	  double actual_geo_ecliptic_beta;
	  double actual_helio_ecliptic_lambda;
	  double actual_helio_ecliptic_beta;  
	  double apparent_geo_ecliptic_lambda;
	  double apparent_geo_ecliptic_beta;
	  double equ_ra;
	  double equ_dec;
	  double hor_altitude;
	  double hor_azimuth;
	  double sun_object_distance;
	  double earth_object_distance;
	  double light_travel_time;
	  double phase;
	  double magnitude;
	  double angular_size;
	  double azimuth_rise;
	  double azimuth_set;
	  double rise_time;
	  double transit_time;
	  double set_time;
	};
	
The above structure is defined in astronomy_object.h.  
The purpose of the fields is:

| Field | Purpose | Units |
| :---- | :------ | :---: |
| actual_geo_ecliptic_lambda | Actual Geo ecliptic co-ordinate - lambda | degrees |
| actual_geo_ecliptic_beta | Actual Geo ecliptic co-ordinate - beta | degrees |
| actual_helio_ecliptic_lambda | Helio ecliptic co-ordinate - lamda | degrees |
| actual_helio_ecliptic_beta | Helio ecliptic co-ordinate - beta | degrees |
| apparent_geo_ecliptic_lambda | Apparent Geo ecliptic co-ordinate - lambda | degrees |
| apparent_geo_ecliptic_beta | Apparent Geo ecliptic co-ordinate - beta | degrees |
| equ_ra | Equatorial co-ordinate - RA | Hours |
| equ_dec | Equatorial co-ordinate - Dec | degrees |
| hor_altitude | Horizon co-ordinate - altitude | degrees |
| hor_azimuth | Horizon co-ordinate - azimuth | degrees | 
| sun_object_distance | Sun object distance | AU |
| earth_object_distance | Earth object distance | AU |
| light_travel_time	| The time taken for light from the object to reach the user. |	seconds |
| phase | Phase 0 being New to 1 being full | N/A |
| magnitude | Magnitude of the object | N/A |
| angular_size | Angular size of the object. | Arc seconds |
| azimuth_rise | Azimuth where the object rises. | degrees |
| azimuth_set | Azimuth where the object sets. | degrees |
| rise_time	| The time when object rises(NaN = never rises). | Julian date |
| transit_time | The time when object is in transit. | Julian date |
| set_time | The time when object sets(NaN = never sets). | Julian date |

The object in each element of the output array is:

| Element | Value held |
| :-------: | :---------- |
| 0 | Sun |
| 1 | Moon |
| 2 | Mercury |
| 3 | Venus |
| 4 | Earth | 		
| 5 | Mars |
| 6 | Jupiter |
| 7 | Saturn |
| 8 | Uranus |
| 9 | Neptune |

## Example code

The example is example-024.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)