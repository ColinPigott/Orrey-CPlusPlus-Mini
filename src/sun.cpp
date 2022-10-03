// Methods for working out the details for the Sun.
#include <iostream>
#include "sun.hpp"
#include "math.h"
#include "math_misc.hpp"
#include "constants.hpp"
#include "time_details.hpp"
#include <iomanip> // Test only

using namespace constants;
using namespace std;

/*
 * Calculate the Sun's details.
 *
 * @input:
 * julian_date = Julian date of the user.
 *
 * @output:
 * output[0] = Geo ecliptic co-ord lambda.
 * output[1] = Geo ecliptic co-ord beta.
 * output[2] = Sun-Earth distance (AU).
 * output[3] = Angular size (arc seconds)
 * output[4] = Light travel time (seconds)
 * output[5] = Mean anomaly of the Sun (degrees)
 */
double *sun::sun_details(double julian_date)
{
  time_details time_details;
  math_misc math_misc;
  static double output[6];
  double fractional_year;
  double no_days;
  double date_year;
  double number_of_leap_years;
  double d;
  double n;
  double m_sun;
  double m_sun_degrees;
  double eccentric_anomaly;
  double v;
  double *details;
  
  // Find the number of days since the start of the year.
  fractional_year = time_details.decimal_year(julian_date);
  modf(fractional_year, &date_year);

  no_days = time_details.julian_date(date_year,1.0,1.0,0.0,0.0,0.0);
  
  no_days = julian_date - no_days;

  // Add the number of days for each year since 1990.
  no_days += ((date_year - 1990) * 365);

  // Add a day for every leap year between date and 1990.
  number_of_leap_years = (double)(time_details.number_of_leap_years((double)(date_year - 1)) - time_details.number_of_leap_years(1990));
  
  d = no_days + number_of_leap_years;
   
  n = (360/365.242191) * d;
  
  n = math_misc.angle_in_range(n);
  
  m_sun = n + sun::epsilon_g - sun::omega_g;
  
  if (m_sun < 0)
    m_sun += 360.0;
    
  m_sun_degrees = m_sun;  
  m_sun = math_misc.to_radians(m_sun);
  
  eccentric_anomaly = math_misc.solveKeplers(m_sun,sun::e,1e-6);
  
  v = (1 + sun::e) / (1 - sun::e);
  v = sqrt(v);
  v = v * tan((eccentric_anomaly/2));
  
  //cout << "v (initial)       = " << v << endl;
  
  v = atan(v);
  v = v * 2;
  v = math_misc.to_degrees(v);
    
  output[0] = v + sun::omega_g;
  
  // Sun's position in geo ecliptic co-ords
  if ( output[0] > 360.0)
    output[0] -= 360.0;
    
  if (output[0] < 0)
    output[0] += 360.0;
    
  output[1] = 0.0;
  
  // Now work out the Sun details, i.e. distance,angular size and light travel time.
  details = sun_distance_size_light_time(v);
  
  output[2] = details[0];	// Distance in AU.
  output[3] = details[1];	// Angular size (arc seconds)
  output[4] = details[2];	// Light travel time (sec)
  output[5] = m_sun_degrees;	// Mean anomaly of the sun (degrees)
  	
  return output;
}

/*
 * Calculate the Sun's distance and angular size.
 *
 * @input:
 * v	- true anomaly (degrees)
 *
 * @output:
 * output[0] = Sun-Earth distance (AU).
 * output[1] = Angular size (arc seconds)
 * output[2] = Light travel time (seconds)
 */
double *sun::sun_distance_size_light_time(double v)
{
  static double output[3];
  double f;
  math_misc math_misc; 
  
  v = math_misc.to_radians(v);
  
  f = (1 + sun::e*cos(v)) / (1-(sun::e*sun::e));
  
  // Work out the Sun-Earth distance.
  output[0] = sun::ro / f;
  
  // Work out the light travel time (sec)
  output[2] = output[0] / SPEEDOFLIGHT;
  
  // Convert the distance to the Sun into AU.
  output[0] = output[0] / KM_IN_AU;
  
  // Work out the singular size.
  output[1] = f * sun::thetao;
  output[1] = output[1] * ARCSECONDS_IN_A_DEGREE;
   
  return output;
}

