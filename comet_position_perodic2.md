# comet_position_perodic

## Introduction

This method is used to work out the details of a comet with a peroidic orbit. 

## Function Prototype

The function prototype of this function is:

  struct astronomical_object comet_position_perodic(double *comet_orbit_elements,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double julian_date,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double longitude,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double latitude,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double absolute_mag,  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double slope_param);  


 
### The parameters:
The function of the parameters is:

	comet_orbit_elements	- Is a pointer to the array that holds the details of the orbit.
				              The elements in this array are:  

    Field    Content                            Units                    Symbol 	
   	  0	     Period                             mean Solar years            T
 	  1	     Epoch of periastron                Years                       t
 	  2	     Longitude of periastron            degrees                     w
 	  3	     Eccentricity	                                                e
 	  4	     Semi-major axis of orbit           arcsec                      a
 	  5	     Inclination of orbit               degrees                     i
 	  6	     Position angle of ascending node   degrees                     o
	
	julian_date		- The Julian date of the observer.
	longitude		- Longitude of the observer (degrees).
	latitude		- Latitude of the observer (degrees).
	absolute_mag    - Intrinsic magnitude of the comet (H) (see note 1).  
	slope_mag       - How the comet brightens as it gets closer to the Sun (n) (see note 1). 	

Note 1:
The values for the absolute_mag and slope_mag can be found at:

https://in-the-sky.org/data/comets.php  
https://people.ast.cam.ac.uk/~jds/  

### The output: 
The output is a pointer to an array of ten astronomical_object structures that hold the details of the object.  
The definition of the astronomical_object structure is:

	struct astronomical_object
	{ (always nan)
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
The prupose of the fields is:

| Field | Purpose | Units |
| :---- | :------ | :---: |         
| actual_geo_ecliptic_lambda | Actual Geo ecliptic co-ordinate - lambda | degrees |
| actual_geo_ecliptic_beta | Actual Geo ecliptic co-ordinate - beta	| degrees |
| actual_helio_ecliptic_lambda | Helio ecliptic co-ordinate - lamda | degrees |
| actual_helio_ecliptic_beta | Helio ecliptic co-ordinate - beta | degrees |
| apparent_geo_ecliptic_lambda | Apparent Geo ecliptic co-ordinate - lambda | degrees |
| apparent_geo_ecliptic_beta | Apparent Geo ecliptic co-ordinate - beta | degrees |
| equ_ra | Equatorial co-ordinate - RA | Hours |
| equ_dec | Equatorial co-ordinate - Dec | degrees |
| hor_altitude | Horizon co-ordinate - altitude | degrees |
| hor_azimuth | Horizon co-ordinate - azimuth | degrees |  
| sun_object_distance | Sun object distance	| AU | 
| earth_object_distance | Earth object distance | AU | 
| light_travel_time | The time taken for light from the object to reach the user. | seconds |
| phase	| Phase 0 being New to 1 being full | N/A |
| magnitude	| Magnitude of the object	| N/A | 
| angular_size | Angular size of the object. | Arc seconds (always nan) |
| azimuth_rise | Azimuth where the object rises. | degrees |
| azimuth_set | Azimuth where the object sets. | degrees |
| rise_time	| The time when object rises(NaN = never rises). | Julian date |
| transit_time | The time when object is in transit. | Julian date |
| set_time | The time when object sets(NaN = never sets). | Julian date |

## Finding comet details

To use the comet routines the following data is needed:

- The orbit details
- The visual magnitude details.

The comet orbit details can be found from the following websites:

https://ssd.jpl.nasa.gov/tools/sbdb_lookup.html#
https://theskylive.com/comets

N.B. The Longitude of periastron is the sum of Argument of perihelion (peri) and Longitude of the ascending node (node).

The visual magnitude parameters can be found on the following websites:

https://people.ast.cam.ac.uk/~jds/
https://in-the-sky.org/data/comets.php

### Limitations:
Comets are dynamic environment as they approach the Sun, as a result the above data will change over time.  
Added to that, the model used by this library does not take the gavitaional effects of the rest of the bodies in the solar system into account.

## Example code

The example is example-021.cpp.

[Home](readme.md)  
[Back to sections page](Sections.md)