// Class for calculating the Moon's position and details.
#include <iostream>
#include "moon.hpp"
#include "sun.hpp"
#include "math.h"
#include "math_misc.hpp"
#include "constants.hpp"
#include "time_details.hpp"

using namespace std;
using namespace constants;

/*
 * Calculate the Moon's details.
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
 * output[5] = phase
 */  
double *moon::moon_details(double julian_date)
{
  static double output[6];
  sun sun;
  time_details time_details;
  math_misc math_misc;
  double *sun_details;
  double *moon_details;
  double fractional_year;
  double temp;
  double no_days;
  double date_year;
  double number_of_leap_years;
  double d;
  double l;
  double mm;
  double n;
  double ev;
  double ae,a3,a4;
  double mm_comp;
  double ec;
  double l_comp;
  double v;
  double l_comp_comp;
  double n_comp;
  double x,y;
  
  fractional_year = time_details.decimal_year(julian_date);
  temp = modf(fractional_year, &date_year);
  
  no_days = time_details.julian_date(date_year,1.0,1.0,0.0,0.0,0.0);
  
  no_days = julian_date - no_days;

  // Add the number of days for each year since 1990.
  no_days += ((date_year - 1990) * 365);

  // Add a day for every leap year between date and 1990.
  number_of_leap_years = (double)(time_details.number_of_leap_years((double)(date_year)) - time_details.number_of_leap_years(1990));
  
  //number_of_leap_years = abs(number_of_leap_years);
  
  d = no_days + number_of_leap_years;
  
  //d = -3960.332755;	// +++++ Debug
  
  // Obtain the details for the Sun.
  // sun_details[0] = geo ecliptic lambda co-ord (degrees)
  // sun_details[5] = mean Mean anomaly of the Sun (degrees)
  sun_details = sun.sun_details(julian_date);
    
  l = 13.176396 * d + moon::lo;
  
  l = math_misc.angle_in_range(l);
   
  mm = l-0.1114041*d-po;
  
  mm = math_misc.angle_in_range(mm);
  
  n = no-0.0529539*d;
  
  n = math_misc.angle_in_range(n);
  
  ev = 1.2739 * sin( math_misc.to_radians( (2*(l-sun_details[0]) - mm) ));
  
  ae = 0.1858*sin(math_misc.to_radians(sun_details[5]));
  a3 = 0.37 * sin(math_misc.to_radians(sun_details[5]));
  
  mm_comp = mm + ev - ae-a3;
  
  ec = 6.2886*sin(math_misc.to_radians(mm_comp));  
  
  a4 = 0.214*sin(math_misc.to_radians( (2*mm_comp) ));
  
  l_comp = l + ev + ec - ae + a4;
  
  v = 0.6583*sin(math_misc.to_radians( (2*(l_comp - sun_details[0])) ));   
  
  l_comp_comp = l_comp + v;
  
  n_comp = n -0.16*sin(math_misc.to_radians(sun_details[5]));
  
  y = sin(math_misc.to_radians((l_comp_comp - n_comp)))*cos(math_misc.to_radians(i));
  x = cos(math_misc.to_radians((l_comp_comp - n_comp)));
  
  temp = math_misc.tan_correct_quadrant(x,y);
 
  output[0] = n_comp + temp;
  output[0] = math_misc.angle_in_range(output[0]);
  
  output[1] = sin(math_misc.to_radians((l_comp_comp - n_comp))) * sin(math_misc.to_radians(i));
  output[1] = math_misc.to_degrees(asin(output[1]));
    
  // Work out the Earth-Moon distance, angular size and light travel time
  moon_details = moon_distance_size_light_travel(mm_comp, ec);
  
  output[2] = moon_details[0];
  output[3] = moon_details[1];
  output[4] = moon_details[2]; 
    
  // Work out the phase of the Moon.
  output[5] = moon_phase(sun_details[0],l_comp_comp);
  
  return output;
}

/*
 * Calculate the Moon phase of the Moon..
 *
 * @input:
 * lambda                 = The geo-centric ecliptic lambda co-ord (degrees)
 * true_orbital_longitude = True orbital longitude of the Moon (degrees).
 *
 * @output:
 * phase = the phase of the Moon 0.0 = New Moon
 */  
double moon::moon_phase(double lambda,double true_orbital_longitude)
{
  double d,f;
  math_misc math_misc;
  
  d = true_orbital_longitude - lambda;
  
  f = 0.5 *(1 - cos(math_misc.to_radians(d)) );  
   
  return f;
}

/*
 * Calculate the Moon phase of the Moon..
 *
 * @input:
 * moon_corrected_anomaly = Moon's corrected anomaly (degrees).
 * equation_centre        = Equation of the centre of the Moon (degrees).
 *
 * @output:
 * output[0] = The Earth-Moon distance in AU.
 * output[1] = Angular size (arc seconds).
 * output[2] = Light travel time (seconds).
 */  
double *moon::moon_distance_size_light_travel(double moon_corrected_anomaly,double equation_centre)
{
  static double output[3];
  double p_comp;
  double angle_size;
  double light_travel_time;
  math_misc math_misc;
  
  // Work out the Earth-Moon distance.
  p_comp = (1-moon::e)*(1-moon::e);
  p_comp = p_comp / (1+moon::e*cos( math_misc.to_radians((moon_corrected_anomaly + equation_centre)) ));
  
  // Work out the angular size.
  angle_size = moon::moon_angular_dia / p_comp;
  
  // Now convert the angular size into arc seconds.
  angle_size *= ARCSECONDS_IN_A_DEGREE;
  
  // work out the light ravel time
  light_travel_time = (p_comp * moon::a) / SPEEDOFLIGHT;
    
  // Convert the Earth-Moon distance to AU.
  p_comp = (p_comp * moon::a) / KM_IN_AU;
  
  // Send the details to the rest of the system.
  output[0] = p_comp;
  output[1] = angle_size;
  output[2] = light_travel_time; 
    
  return output;
}

