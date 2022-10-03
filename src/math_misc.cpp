// Handles misc maths functions.
#include <math.h> 
#include "math_misc.hpp" 
#include "time_details.hpp"
#include "constants.hpp" 
#include "sun.hpp"
#include "moon.hpp"
#include "planets.hpp"
#include "comet_details.hpp"
#include "coord_conversion.hpp"
#include "astronomy_object.hpp"
#include <stdbool.h>
#include <iostream>

using namespace std;
using namespace constants;

// Make sure that the angle given is withing the rangel from 0 to 360 degrees.
double math_misc::angle_in_range(double angle)
{
  while ( (angle > 360.0) || (angle < 0.0) )
  {
    if (angle > 360.0)
    {
      angle -= 360.0;
    }
				
    if (angle < 0.0)
    {
      angle += 360.0;
    }
				
  }
			
  return angle;
}
	
// Work out the tan of x,y and then make sure the angle is between 0 -360 degrees.
double math_misc::tan_correct_quadrant(double x,double y)
{
  double angle;
		
  if ((x == 0) && (y == 0))
  {
    angle = 90.0;
  }
  else
  {
    angle = atan2(y, x);
    angle = to_degrees(angle);
		
    if (angle < 0)
    {
      angle += 360.0;
    }
  }
		
  // If the quandrant is x = +ve and y = +ve then in range 0-90 degrees.
  if ( (y >= 0) && (x >= 0) )
  {			
    if (angle != 90.0)
    {
      if (angle < 0)
      {
        angle += 90.0;
      }
			
      if (angle > 90)
      {
        angle -= 90.0;
      }
    }
  }

  // If the quadrant is x = -ve and y = +ve then in range 90-180 degrees.
  if ( (y > 0) && (x < 0) )
  {
    if (angle < 0) // Since x = y = 0 is 90 degrees.
    {
      angle = -angle + 90.0;
    }
			
    if (angle > 180)
    {
      angle -= 180.0;
    }
  }

  // If the quadrant is x = -ve and y = -ve then in range 180-270 degrees.
  if ( (y < 0) && (x < 0) )
  {	
    if ((angle < 0) || (angle < 180))
    {
      angle += 180.0;
    }
			
    if (angle > 270)
    {
      angle -= 180.0;
    }
  }
		
  // If the quadrant is x = +ve and y = -ve then in range 270-360 degrees.
  if ( (y < 0) && (x > 0) )
  {
    if ((angle < 0) || (angle < 270))
    {
      angle += 360.0;
    }
			
    if (angle > 360)
    {
      angle -= 360.0;
    }
  }

  return angle;
}

// Convert degrees to radians
double math_misc::to_radians(double degrees)
{
  double radians;

  radians = degrees * (PI / 180.0);

  return radians;
}

// Convert radians to degreesns
double math_misc::to_degrees(double radians)
{
	double degrees;
	
	degrees = radians * (180.0 / PI);
	
	return degrees;
}

// Work out Kepler's equation.
// Input parameters - error
//                  - initial value (this MUST be in radians)
//                  - eccentricity 
// Ouput            - The answer to Kepler's equation.
double math_misc::solveKeplers(double initial_value,double ecc,double error)
{
  double delta,delta_E,E;
  bool flag;
        	
  // Initialise.
  delta = 0.0;
  E = initial_value;
  flag = true;
        	
  while (flag)
  {
    delta = E - (ecc*sin(E)) - initial_value;  
        	
    if (abs(delta) > error )
    {
      delta_E = delta / ( 1 - (ecc*cos(E)));
      E = E - delta_E;
    }
    else
      flag = false;
  }
        	       	
  return E;
}

// Work out the nutation
// @input:
// Julian_date	= Julian date
//
// @output:
// output[0]	= nutation in longitude
// output[1]	= nutation in obliquity
double *math_misc::nutation(double julian_date)
{
  double t,a,l,b,moon_node;
  static double output[2];
	
  t = (julian_date - 2415020.0)/36525.0;
	
  a = 100.002136 * t;
	
  l = 279.6967 + 360.0 * (a - (double)int(a));
  l = angle_in_range(l);
	
  b = 5.372617 * t;
	
  moon_node = 259.1833 - 360.0 * (b - (double)int(b));
  moon_node = angle_in_range(moon_node);
	
  output[0] = -17.2 * sin(to_radians(moon_node)) - 1.3 * sin(to_radians(2*l));
  output[1] = 9.2 * cos(to_radians(moon_node)) + 0.5 * cos(to_radians(2*l));
	
  // Convert the values from arc seconds to degrees.
  output[0] /= 3600.0;
  output[1] /= 3600.0;

  return output;
}

// Work out the aberration
// @input:
// sun_lambda	= ecliptic longitude of the Sun
// lambda	= ecliptic longitude of the object
// beta	= ecliptic latitude of the object
//
// @output:
// output[0] = effect on the ecliptic longitude
// output[1] = effect of the ecliptic latitude
double *math_misc::aberration(double sun_lambda,double lambda,double beta)
{
  static double output[2];
  double delta_lambda,delta_beta;
	
  delta_lambda = -20.5 * cos(to_radians((sun_lambda - lambda)));
  delta_lambda /= cos(to_radians(beta));
	
  delta_beta = -20.5 * sin(to_radians((sun_lambda - lambda)));
  delta_beta *= sin(to_radians(beta));
	
  // Convert delta_lambda and delta_beta to degrees.
  delta_lambda /= 3600.0;
  delta_beta /= 3600.0;
	
  output[0] = delta_lambda;
  output[1] = delta_beta;
	
  return output;
}

// Work out an approximation for atmospheric refraction.
// The default temperature is 25 degrees Centigrade.
// The default pressure is 1000mb.
// Input  - latitude			- Latitude in degrees (south is negative).
//        - temperature         - temperature in degrees Celcius.
//        - pressure            - pressure in mb
//        - altitude_angle      - the angle betwwen the horizen an the object.
// Output - co_ords.get_coord_a	- change in RA
//          co_ords.get_coord_b - change in dec
double math_misc::refaction(double latitude,double temp, double pressure,double altitude_angle)
{
  double refraction;
        	
  // Work out the effect on the altitude.
  if (latitude >= 15)
  {
    refraction = (0.00452 * pressure * tan(to_radians( (90 - altitude_angle) )) ) / (273 + temp);
  }
  else
  {
    refraction = 1008 * (0.1594 + (0.0196*altitude_angle) + (0.00002* altitude_angle*altitude_angle));
    refraction = refraction / ((273+13)*(1+(0.505*altitude_angle) +(0.0845*altitude_angle*altitude_angle)) );
  }
        	
  return refraction;
}

// Rise and set via interpolation
// See Atronomical Algorithums ch14
// Input:
// Julian_date	- The date in Julian date
// Longitude   - Longitude of the user (degrees)  pos values are East, neg values are west.
// Latitude    - Latitude of the user (degrees).
// Object      - Which object the rise and set refers to.
//					0 - star
//					1 - Sun
//					2 - Moon
//					3 - Mercury
//					4 - Venus
//					5 - Mars
//					6 - Jupiter
//					7 - Saturn
//					8 - Uranus
//					9 - Neptune
// position[]    - The RA and DEC of a star
//      position[0] = RA
//      position[1] = DEC
//
// Output:
// Output[0] - Azimuth of the selected object to rise.
// Output[1] - Azimuth of the selected object to set.		 
// Output[2] - Time of the object rising (Julian date).
// Output[3] - Time of the object setting (Julian date).
// Output[4] - Time of when the object is in transit.
double *math_misc::rise_and_set_interpolate(double julian_date,
                                            double longitude,
                                            double latitude,
                                            int object,
                                            double *pos_star,
                                            double *comet_orbit_elements,
                                            double epoch_perihelion_of_Earth)
{
  sun sun_details;
  moon moon_details;
  planets planet;
  //comet_details comet;
  time_details time_details;
  co_ord_conversion coord_conversion;
  static double output[5];
  double *ecl_pos;
  double *equ_pos;
  double ho,apparent_siderial_time,Ho;
  double delta_t,a1,b1,c1,a2,b2,c2;
  double alpha_int0,alpha_int1,alpha_int2;
  double delta_int1,delta_int2;
  double H0,H1,H2;
  double delta_m0,delta_m1,delta_m2;
  double h1,h2;
  double n0,n1,n2;
  int julian_date_int,index,loop1;
  double ar,as,phi,delta_a;
  double alpha[3];
  double delta[3];
  double Julian_at_midnight[3];
  double m[3];
  double m_old[3];
  double theta[3];
			 
  const double limit = 0.0001;
			 
  // Default values - to shut the compiler up.
  ho = -0.5667; // Default value.
  delta_int1 = 0;
  delta_int2 = 0;
			 			 
  // Find apparent Siderial time at oh on day.
  julian_date_int = (int) julian_date;
  Julian_at_midnight[1] = ((double) julian_date_int) + 0.5;
			 
  //apparent_siderial_time = gst(midnight_Julian);
  apparent_siderial_time = time_details.gst(Julian_at_midnight[1]);
  apparent_siderial_time *= 15.0;
	 
  // Work out the Julian dates.
  Julian_at_midnight[0] = Julian_at_midnight[1] - 1;
  Julian_at_midnight[2] = Julian_at_midnight[1] + 1;
			 
  // Find RA and Dec of object at 0h D - 1
  // Find RA and Dec of object at 0h D
  switch (object)
  {
    case OBJECT_ID_SUN:	// Sun
      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = sun_details.sun_details(Julian_at_midnight[index]);
				    	
	    equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
	    alpha[index] = equ_pos[0] * 15;
	    delta[index] = equ_pos[1];
      }
				    				    
      ho = -0.8333;
      break;
    case OBJECT_ID_MOON:	// Moon
      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = moon_details.moon_details(Julian_at_midnight[index]);
				    	
	    equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
	    alpha[index] = equ_pos[0] * 15;
	    delta[index] = equ_pos[1];
      }
				    				    
      ho = -0.125; 
      break;
    case OBJECT_ID_MERCURY: // Mercury
      
      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = planet.planet_details(Julian_at_midnight[index],0);
				    	
        equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
        alpha[index] = equ_pos[0] * 15;
        delta[index] = equ_pos[1];
      }
      ho = -0.5667;
      break;
    case OBJECT_ID_VENUS: // Venus
      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = planet.planet_details(Julian_at_midnight[index],1);
				    	
        equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
        alpha[index] = equ_pos[0] * 15;
        delta[index] = equ_pos[1];
      }
      ho = -0.5667;
      break;
    case OBJECT_ID_MARS: // Mars
 
      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = planet.planet_details(Julian_at_midnight[index],3);
				    	
        equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
        alpha[index] = equ_pos[0] * 15;
        delta[index] = equ_pos[1];
      }
      ho = -0.5667;
      break;
    case OBJECT_ID_JUPITER: // Jupiter

      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = planet.planet_details(Julian_at_midnight[index],4);
				    	
        equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
        alpha[index] = equ_pos[0] * 15;
        delta[index] = equ_pos[1];
      }
      ho = -0.5667;
      break;
    case OBJECT_ID_SATURN: // Saturn
        
      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = planet.planet_details(Julian_at_midnight[index],5);
				    	
        equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
        alpha[index] = equ_pos[0] * 15;
        delta[index] = equ_pos[1];
      }
      ho = -0.5667;
      break;
    case OBJECT_ID_URANUS: // Uranus
        
      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = planet.planet_details(Julian_at_midnight[index],6);
				    	
        equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
        alpha[index] = equ_pos[0] * 15;
        delta[index] = equ_pos[1];
      }
      ho = -0.5667;
      break;
    case OBJECT_ID_NEPTUNE: // Neptune
                              
      for (index = 0;index < 3;index++)
      {						    	
        ecl_pos = planet.planet_details(Julian_at_midnight[index],7);
				    	
        equ_pos = coord_conversion.ecl_to_equ(&ecl_pos[0],Julian_at_midnight[index]);
        alpha[index] = equ_pos[0] * 15;
        delta[index] = equ_pos[1];
      }
      ho = -0.5667;
      break;
    case OBJECT_ID_STAR: // star
      alpha[0] = pos_star[0] * 15;
      alpha[1] = pos_star[0] * 15;
      alpha[2] = pos_star[0] * 15;

      delta[0] = pos_star[1];
      delta[1] = pos_star[1];
      delta[2] = pos_star[1];
      ho = -0.5667;
      break;
    default:
      ho = -0.5667;
      break;
  }
			 
  // Find Ho
  Ho = sin(to_radians(ho)) - (sin(to_radians(latitude))) * sin(to_radians(delta[1]));
  Ho = Ho / (cos(to_radians(latitude)) * cos(to_radians(delta[1])));
  Ho = to_degrees(acos(Ho));
	    	
  // Find m0,m1 and m2
  // Find the Siderial times at m0,m1 and m2
  // The time of the transit.
  m[0] = (alpha[1] + longitude - apparent_siderial_time) / 360;
	    	
  // The time for the rising.
  m[1] = m[0] - (Ho/360);

  // The time for the setting.
  m[2] = m[0] + (Ho/360);
	    	
  // Make sure the value of m0,m1 and m2 is within -1 and 1.
  for (loop1 = 0;loop1 < 3;loop1++)
  {
    if (m[loop1] < 0)
      m[loop1] += 1;
		    	
    if (m[loop1] > 1)
      m[loop1] -= 1;
  }
	    	
  // Find the Siderial time at Greenwich in degrees.
  theta[0] = apparent_siderial_time + (360.985647 * m[0]);	    	
  theta[1] = apparent_siderial_time + (360.985647 * m[1]);	
  theta[2] = apparent_siderial_time + (360.985647 * m[2]);
	    	    	
  // Interpulate Ra and dec.
  delta_t = 56;	// Guess estimation
	    	
  // Initalise the old values for the times of transit,rise and set.
  m_old[0] = 999;
  m_old[1] = 999;
  m_old[2] = 999;
	    	
  while ( ((m_old[0] - m[0]) > limit) && ((m_old[1] - m[1]) > limit) && ((m_old[2] - m[2]) > limit) ) 
  {    		
    // Interpolate RA
    n0 = m[0] + (delta_t/86400); 
    n1 = m[1] + (delta_t/86400);
    n2 = m[2] + (delta_t/86400);
			    
    // Store the old times for the rise,set and transit.
    m_old[0] = m[0];
    m_old[1] = m[1];
    m_old[2] = m[2];
			
    a1 = alpha[1] - alpha[0];
    b1 = alpha[2] - alpha[1];
    c1 = alpha[0] + alpha[2] - (2 * alpha[1]);
	    	
    alpha_int0 = alpha[1] + (n0/2) * (a1 + b1 + (n0*c1));
    alpha_int1 = alpha[1] + (n1/2) * (a1 + b1 + (n1*c1));
    alpha_int2 = alpha[1] + (n2/2) * (a1 + b1 + (n2*c1));
	    	
    // Interpolate DEC
    a2 = delta[1] - delta[0];
    b2 = delta[2] - delta[1];
    c2 = delta[0] + delta[2] - (2 * delta[1]);
	    	
    delta_int1 = delta[1] + (n1/2) * (a2 + b2 + (n2*c2));
    delta_int2 = delta[1] + (n2/2) * (a2 + b2 + (n2*c2));
	    	
    // Find the hour angle.
    H0 = theta[0] - longitude - alpha_int0; 
    H1 = theta[1] - longitude - alpha_int1;
    H2 = theta[2] - longitude - alpha_int2;
	    	
    h1  = sin(to_radians(latitude))*sin(to_radians(delta_int1));
    h1 += cos(to_radians(latitude))*cos(to_radians(delta_int1))*cos(to_radians(H1)); 
    h1 = to_degrees(asin(h1));
	    	
    h2  = sin(to_radians(latitude))*sin(to_radians(delta_int2));
    h2 += cos(to_radians(latitude))*cos(to_radians(delta_int2))*cos(to_radians(H2)); 
    h2 = to_degrees(asin(h2));
			
    // Find the delta m - for transit
    delta_m0 = H0/360; 
			
    // Find the delta m for rise and set.
    delta_m1 = 360*cos(to_radians(delta_int1))*cos(to_radians(latitude))*sin(to_radians(H1));
    delta_m1 = (h1-ho)/ delta_m1;  

    delta_m2 = 360*cos(to_radians(delta_int2))*cos(to_radians(latitude))*sin(to_radians(H2));
    delta_m2 = (h2-ho)/ delta_m2;  

    // For transit
    m[0] = m[0] + delta_m0;
			
    // rise and set
    m[1] = m[1] + delta_m1;
    m[2] = m[2] + delta_m2;
			    
    for (loop1 = 0;loop1 < 3;loop1++)
    {
      if (m[loop1] < 0)
        m[loop1] += 1;
			    	
      if (m[loop1] > 1)
	m[loop1] -= 1;
    }
  }
	    				
  // Now find the azimuth values for the rise and set.
  phi = sin(to_radians(latitude)) / cos(to_radians(delta_int1));
  phi = to_degrees(acos(phi));
			
  delta_a = tan(to_radians(ho)) / tan(to_radians(phi));
  delta_a = to_degrees(asin(delta_a));
			
  ar = sin(to_radians(delta_int1)) / cos(to_radians(latitude));
  ar = to_degrees(acos(ar));
  as = 360 - ar;
			
  ar = ar + delta_a;
  as = as - delta_a;
			
  // Place the details into the output array.
  // Output:
  // Output[0] - Azimuth of the selected object to rise.
  // Output[1] - Azimuth of the selected object to set.
  // Output[2] - Time of the object rising (Julian date).
  // Output[3] - Time of the object setting (Julian date).
  // Output[4] - Time of when the object is in transit.
  output[0] = ar;
  output[1] = as;
  output[2] = julian_date + m[1];
  output[3] = julian_date + m[2];		
  output[4] = julian_date + m[0];
  
  return output;
}

