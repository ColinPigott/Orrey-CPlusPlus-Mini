// Class for calculating the details of the planets.
#include "planets.hpp"
#include "sun.hpp"
#include "math.h"
#include "math_misc.hpp"
#include "constants.hpp"
#include "astronomy_object.hpp"
#include <iostream>

using namespace std;

using namespace constants;

/*
 * @input:
 * julian_date	= the julian date 
 * planet_id	= which planet to work the position detaild for.
 *
 * @output:
 * np	        = longitude of the ascending node for the planet (degrees) 
 * mp	        = mean anomaly of the planet (degrees)
 * l	        = heliocentric longitude of the planet. (degrees)
 * vp	        = true anomaly of the planet (degrees)
 * r	        = Sun-Planet distance (AU)
 */
double *planets::planet_position_values(double julian_date, int planet_id)
{
  math_misc math_misc;
  static double output[5];
  double d;
  double np,mp,l,vp,r;
  int loop; 
   
  // Get out of this method, if the planet_id is invalid.
  if ((planet_id < 0) || (planet_id > 8))
  {
    // Set the elements in the output array to a known value.
    for (loop = 0;loop < 5;loop++)
    {
      output[loop] = 0.0;
    } 
  
    return output;
  }
  
  // Find the number of days since 1990 Jan 0.0
  d = julian_date - JULIAN1990JAN0 + 1;

  // Work out the details for the planet.
  np = 0.985647356*(d/planet_constants[planet_id].period);
  np = math_misc.angle_in_range(np);
  
  mp = np + planet_constants[planet_id].longitude_at_epoch - planet_constants[planet_id].longitude_of_perihelion;
  mp = math_misc.angle_in_range(mp);
  
  //l = np + (360/constants::PI)*planet_constants[planet_id].eccentricity * sin(math_misc.to_radians(mp));
  l = np + 114.59156*planet_constants[planet_id].eccentricity * sin(math_misc.to_radians(mp));
  l += planet_constants[planet_id].longitude_at_epoch;
  l = math_misc.angle_in_range(l);
  
  vp = l - planet_constants[planet_id].longitude_of_perihelion;
  
  r = planet_constants[planet_id].semi_major_axis * ( 1 - planet_constants[planet_id].eccentricity * planet_constants[planet_id].eccentricity);
  r = r / (1 + planet_constants[planet_id].eccentricity * cos(math_misc.to_radians(vp))); 

  // Send out the details to the system.
  output[0] = np;
  output[1] = mp;
  output[2] = l;
  output[3] = vp;
  output[4] = r;
   
  return output;
}

/* 
 * Calculate the geo ecliptic co-ordindates for a specified planet.
 *
 * @input:
 * julian_date    = Julian date
 * planet_id      = id of the planet in question
 *
 * @output:
 * lambda         = geo ecliptic longitude (degrees)
 * beta           = geo ecliptic latitude (degrees)
 */
double *planets::planet_details(double julian_date, int planet_id)
{ 
  math_misc math_misc;
  sun sun;  
  static double output[2];
  double planet_values[5];
  double earth_values[5];
  double *values;
  double phi,y,x,l_comp,r_comp,a;
  double lambda = 0.0,beta;
  double delta_phi,delta_epsilion;
  
  // Check that the planet selected is not Earth.
  if (planet_id == PLANET_INTERNAL_EARTH_ID)
  {
    output[0] = 0.0;
    output[1] = 0.0;
    
    return output;
  }
  
  // Find the nutation.
  values = math_misc.nutation(julian_date);
  
  delta_phi      = values[0];
  delta_epsilion = values[1];
   
  // Work out the details for the planet.
  values = planet_position_values(julian_date, planet_id);
  planet_values[0] = values[0];			        // Np
  planet_values[1] = values[1];			        // mp
  planet_values[2] = values[2] + delta_epsilion;	// l
  planet_values[3] = values[3];			        // vp
  planet_values[4] = values[4];			        // r
  
  // Work out the details for the Earth.
  values = planet_position_values(julian_date, 2);
  earth_values[0] = values[0];	// Ne
  earth_values[1] = values[1];	// me
  earth_values[2] = values[2];	// L
  earth_values[3] = values[3];	// ve
  earth_values[4] = values[4];	// R
  
  phi = sin(math_misc.to_radians((planet_values[2] - planet_constants[planet_id].longitude_of_ascending_node)));
  phi = phi * sin(math_misc.to_radians(planet_constants[planet_id].inclination));
  phi = asin(phi);
  phi = math_misc.to_degrees(phi) + delta_phi;
  
  y = sin(math_misc.to_radians((planet_values[2] - planet_constants[planet_id].longitude_of_ascending_node)));
  y = y*cos(math_misc.to_radians(planet_constants[planet_id].inclination));
  x = cos(math_misc.to_radians((planet_values[2] - planet_constants[planet_id].longitude_of_ascending_node)));
  
  l_comp = math_misc.tan_correct_quadrant(x,y);
  l_comp = l_comp + planet_constants[planet_id].longitude_of_ascending_node;
  
  r_comp = planet_values[4] * cos( math_misc.to_radians(phi) );
  
  a = r_comp * sin(math_misc.to_radians((earth_values[2] - l_comp)));
  a = a / (earth_values[4] - r_comp * cos(math_misc.to_radians((earth_values[2] - l_comp))));
  a = atan(a);
  a = math_misc.to_degrees(a); 
  
  //if (planet_id < 2)
  if (planet_id < PLANET_INTERNAL_EARTH_ID)
  {
    lambda = 180.0 + earth_values[2] + a;
    lambda = math_misc.angle_in_range(lambda);
  } 
  else if (planet_id > PLANET_INTERNAL_EARTH_ID)
  {
    lambda = earth_values[4] * sin(math_misc.to_radians((l_comp - earth_values[2])));
    lambda = lambda / (r_comp - earth_values[4] * cos(math_misc.to_radians((l_comp - earth_values[2]))));
    lambda = atan(lambda);
    lambda = math_misc.to_degrees(lambda) + l_comp;
    lambda = math_misc.angle_in_range(lambda);
  }
  
  beta = r_comp * tan(math_misc.to_radians(phi));
  beta = beta * sin(math_misc.to_radians((lambda - l_comp)));
  beta = beta / (earth_values[4] * sin(math_misc.to_radians((l_comp - earth_values[2]))));
  beta = atan(beta);
  beta = math_misc.to_degrees(beta);
   
  // Return the geo ecliptic co-ordindates to the rest of the system.  
  output[0] = lambda;
  output[1] = beta;  
  
  return output;
}

/* 
 * Obtain the details of all the planets in the solar syustem at a specific time.
 *
 * @input:
 * julian_date    = The julian date
 *
 * @output:
 * pointer to the start of the array of type astronomical_object, which folds the details of each planet.
 * 
 *
 */
struct astronomical_object *planets::planet_all_details(double julian_date)
{ 
  static struct astronomical_object object[8];
  math_misc math_misc;
  double planet_values[5];
  double earth_values[5];
  double *values;
  double phi,y,x,l_comp,r_comp,a;
  double lambda,beta;
  double phase;
  double magnitude;
  int planet_id;
  
  // Work out the details for the Earth.
  values = planet_position_values(julian_date, 2);
  earth_values[0] = values[0];	// Ne
  earth_values[1] = values[1];	// me
  earth_values[2] = values[2];	// L
  earth_values[3] = values[3];	// ve
  earth_values[4] = values[4];	// R

  // Update the object structure.
  object[PLANET_INTERNAL_EARTH_ID].actual_geo_ecliptic_lambda   = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].actual_geo_ecliptic_beta     = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].apparent_geo_ecliptic_lambda = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].apparent_geo_ecliptic_beta   = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].sun_object_distance          = earth_values[4];
  object[PLANET_INTERNAL_EARTH_ID].earth_object_distance        = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].light_travel_time            = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].phase                        = 1.0;
  object[PLANET_INTERNAL_EARTH_ID].magnitude                    = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].angular_size                 = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].rise_time                    = 0.0;
  object[PLANET_INTERNAL_EARTH_ID].set_time                     = 0.0;
    
  for (planet_id = PLANET_INTERNAL_MIN_ID;planet_id < PLANET_INTERNAL_MAX_ID;planet_id++)
  {  
    // If the planet is Earth, then skip
    if (planet_id != PLANET_INTERNAL_EARTH_ID)
    {
      // Work out the details for the planet.
      values = planet_position_values(julian_date, planet_id);
      planet_values[0] = values[0];	// Np
      planet_values[1] = values[1];	// mp
      planet_values[2] = values[2];	// l
      planet_values[3] = values[3];	// vp
      planet_values[4] = values[4];	// r
  
      phi = sin(math_misc.to_radians((planet_values[2] - planet_constants[planet_id].longitude_of_ascending_node)));
      phi = phi * sin(math_misc.to_radians(planet_constants[planet_id].inclination));
      phi = asin(phi);
      phi = math_misc.to_degrees(phi);
      
      y = sin(math_misc.to_radians((planet_values[2] - planet_constants[planet_id].longitude_of_ascending_node)));
      y = y*cos(math_misc.to_radians(planet_constants[planet_id].inclination));
      x = cos(math_misc.to_radians((planet_values[2] - planet_constants[planet_id].longitude_of_ascending_node)));
       
      l_comp = math_misc.tan_correct_quadrant(x,y);
      l_comp = l_comp + planet_constants[planet_id].longitude_of_ascending_node;
        
      r_comp = planet_values[4] * cos(math_misc.to_radians(phi));
        
      a = r_comp * sin(math_misc.to_radians((earth_values[2] - l_comp)));
      a = a / (earth_values[4] - r_comp * cos(math_misc.to_radians((earth_values[2] - l_comp))));
      a = atan(a);
      a = math_misc.to_degrees(a); 
        
      if (planet_id < PLANET_INTERNAL_EARTH_ID)
      {
        lambda = 180.0 + earth_values[2] + a;
      } 
      else if (planet_id > PLANET_INTERNAL_EARTH_ID)
      {
        lambda = earth_values[4] * sin(math_misc.to_radians((l_comp - earth_values[2])));
        lambda = lambda / (r_comp - earth_values[4] * cos(math_misc.to_radians((l_comp - earth_values[2]))));
        lambda = atan(lambda);
        lambda = math_misc.to_degrees(lambda) + l_comp;
      }
      
      lambda = math_misc.angle_in_range(lambda);
  
      beta = r_comp * tan(math_misc.to_radians(phi));
      beta = beta * sin(math_misc.to_radians((lambda - l_comp)));
      beta = beta / (earth_values[4] * sin(math_misc.to_radians((l_comp - earth_values[2]))));
      beta = atan(beta);
      beta = math_misc.to_degrees(beta);
    
      // Setup the output
      values = planet_distance_size_light_travel(planet_values[4],earth_values[4],planet_values[2],earth_values[2],planet_id);
  
      //double temp;
      if (planet_id < PLANET_INTERNAL_EARTH_ID)
      {
        phase = planet_phase(lambda,planet_values[2]);
      }
      else
      {
        phase = 1.0;
      }
  
      magnitude = planet_magnitude(planet_values[4],values[0],phase,planet_id);
      
      // Update the object array.
      object[planet_id].actual_geo_ecliptic_lambda   = lambda;
      object[planet_id].actual_geo_ecliptic_beta     = beta;
      object[planet_id].apparent_geo_ecliptic_lambda = 0.0;
      object[planet_id].apparent_geo_ecliptic_beta   = 0.0;
      object[planet_id].sun_object_distance          = planet_values[4];
      object[planet_id].earth_object_distance        = values[0];
      object[planet_id].light_travel_time            = values[1];
      object[planet_id].phase                        = phase;
      object[planet_id].magnitude                    = magnitude;
      object[planet_id].angular_size                 = values[2];
      object[planet_id].rise_time                    = 0.0;
      object[planet_id].set_time                     = 0.0;
    } 
  }
  
  return object;
}

/*
 * Work out the Earth-planet distance, light travel time and angular_size
 *
 * @input:
 * r         = Sun-Planet distance (AU)
 * R         = Sun-Earth distance (AU)
 * l         = heliocentric longitude of planet (degrees)
 * L         = heliocentric longitude of Earth (degrees)
 * planet_id = id of the specifed planet
 *
 * @output:
 * output[0] = Earth-planet (AU)
 * output[1] = light travel time (seconds)
 * output[2] = anglar size (arcseconds)
 */
double *planets::planet_distance_size_light_travel(double r, double R,double l,double L,int planet_id)
{
  math_misc math_misc;
  static double output[3];
  double p,tau,angle_size;
  
  p = (R*R) + (r*r) - 2*R*r*cos(math_misc.to_radians((l - L)));
  p = sqrt(p);
  
  tau = 0.1386 * p;	// light travel time (hours)
  tau = tau * 3600.0;	// light travel time (seconds)
  
  angle_size = planet_constants[planet_id].angular_diameter_at_1AU / p;
  
  output[0] = p;
  output[1] = tau;
  output[2] = angle_size;
  
  return output;
}

/*
 * Work out the phase of a planet.
 *
 */
double planets::planet_phase(double lambda,double true_orbital_longitude)
{
  math_misc math_misc;
  double d,f;
  
  d = lambda - true_orbital_longitude;
  
  f = 0.5 * (1+ cos(math_misc.to_radians(d)));
  
  return f;
}

/* 
 * Work out the magnitude of a planet.
 *
 * @input:
 * r		= Sun-planet distance (AU)
 * p		= Earth-planet distance (AU)
 * phase	= phase of the planet
 * planet_id	= id of the specified planet
 *
 * @output:
 * magnitude = magnitude of the specified planet
 */
double planets::planet_magnitude(double r,double p,double phase,int planet_id)
{
  double magnitude;
  
  magnitude = (r * p) / sqrt(phase);
  magnitude = 5 * log10(magnitude) + planet_constants[planet_id].visual_mag_at_1AU;
  
  return magnitude;
}
