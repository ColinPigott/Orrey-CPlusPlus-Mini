// This class handles the comet related stuff.
#include "comet_details.hpp"
#include "math_misc.hpp"
#include "math.h"
#include "constants.hpp"
#include "coord_conversion.hpp"
#include "time_details.hpp"
#include "planets.hpp"
#include "sun.hpp"
#include "astronomy_object.hpp"
#include <iostream>

using namespace std;

using namespace constants;

// Position of a perodic comet.
// The order of the orbital elements for the comet are:
//
//       Field	     Content					Units				Symbol
//       =====      =======       				=====				======
//	    0        Period 					(mean Solar years)                T
// 	    1        Epoch of periastron							  t
// 	    2	     Longitude of periastron				 	  	          w
// 	    3        Eccentricity								  e
// 	    4        Semi-major axis of orbit 		        (arcsec)			  a
// 	    5        Inclination of orbit 			(degrees)			  i
//	    6        Position angle of ascending node 	        (degrees)			  o
//
// The output from this function is:
//
//		Field		Content
//		=====		=======
//		  0		position - lambda (geoentric ecliptic)
//		  1		position - beta (geoentric ecliptic)
//	  	  2  		distance from Earth (AU)
//		  3		distance from Sun (AU)
double *comet_details::comet_position_perodic(double *comet_orbit_elements,
                                              int year,
                                              int month,
                                              int day,
                                              int hour,
                                              int min,
                                              double secs,
                                              double time_offset)
{
  double julian_date;
  time_details time_functions;

  julian_date = time_functions.julian_date( year, month, day, hour, min, secs);
  
  // Take account of the time_offset.
  julian_date -= time_offset / 24.0;
  
  return comet_position_perodic(comet_orbit_elements,julian_date);
}

// Position of a perodic comet.
// The order of the orbital elements for the comet are:
//
//       Field		Content				        Units				Symbol
//       =====	        =======       				=====				======
// 	   0		Period 				        (mean Solar years)		   T
// 	   1		Epoch of periastron							   t
// 	   2		Longitude of periastron				  	                   w
// 	   3		Eccentricity								   e
// 	   4		Semi-major axis of orbit 		(arcsec)			   a
// 	   5		Inclination of orbit 			(degrees)			   i
// 	   6		Position angle of ascending node 	(degrees)			   o
//
// The output from this function is:
//
//		Field		Content
//		=====		=======
//		  0		position - lambda (geocentric ecliptic)
//		  1		position - beta (geocentric ecliptic) 
//                2		distance from Earth (AU)
//		  3		distance from Sun (AU)
double *comet_details::comet_position_perodic(double *comet_orbit_elements,double julian_date)
{
  math_misc math_misc;
  time_details time_details;
  static double comet_position[4];		      	
  double decimal_years,m,E,v,r,y,x,angle,l,phi,ll,rl,temp,p;
  double Ne,Me,L,ve,R,no_of_days,lambda,beta;
  double error = 0.0000001;
        	
  // Orbital details for the Earth.
  double Te = 1.00004,Eeta=99.403308,Elong_of_perihelion=102.768413,Ee=0.016713;
        	
  decimal_years = time_details.decimal_year(julian_date);
        	
  y = decimal_years - comet_orbit_elements[1];
        	      	
  m = (360.0 * y) / comet_orbit_elements[0];

  while ( !( ( m >= 0.0) && (m <= 360.0)) )
  {
    if ( m < 0.0)
      m += 360.0;
    else
      m -= 360.0;
  }
        	
  m = math_misc.to_radians(m);
           	
  E = math_misc.solveKeplers(m,comet_orbit_elements[3],error);
            
  v = sqrt(((1+comet_orbit_elements[3])/(1-comet_orbit_elements[3]))) * tan((E/2));
        	
  v = atan(v);
        	
  v *= 2.0;
        	
  v = math_misc.to_degrees(v);
            
  l = v + comet_orbit_elements[2];
        	
  r =  comet_orbit_elements[4]*(1 - (comet_orbit_elements[3] * comet_orbit_elements[3]));
  r = r / (1 + comet_orbit_elements[3]*cos(math_misc.to_radians(v)) );
        	        	
  phi = asin(sin(math_misc.to_radians( (l - comet_orbit_elements[6]) ))*sin(math_misc.to_radians(comet_orbit_elements[5])));
  phi = math_misc.to_degrees(phi);        	
        	
  y = sin(math_misc.to_radians( (l - comet_orbit_elements[6])) )*cos(math_misc.to_radians(comet_orbit_elements[5]));
  x = cos(math_misc.to_radians( (l - comet_orbit_elements[6])) );
        	
  angle = math_misc.tan_correct_quadrant(x, y);
        	
  ll = angle + comet_orbit_elements[6];
        	
  rl = r * cos(math_misc.to_radians(phi));
        	
  // Work out the position of the Earth.
  // Now do the calculations for the Earth
  no_of_days = julian_date - JULIAN1990JAN0;
       	
  Ne = (360.0/365.242191) * (no_of_days/Te);
        	        	      
  // Make sure n is within the range 0-360.
  while ( !( ( Ne >= 0.0) && (Ne <= 360.0)) )
  {
    if ( Ne < 0.0)
      Ne += 360.0;
    else
      Ne -= 360.0;
  }
        	
  Me = Ne + Eeta - Elong_of_perihelion;

  L  = Ne + ((360.0/PI)*Ee*sin(math_misc.to_radians(Me))) + Eeta;
       	
  // Make sure the value of L is correct.
  if (L > 360.0)
    L -= 360.0;
        	
  if (L < 0.0)
    L += 360.0;
        
  ve = L - Elong_of_perihelion;  // Initial approx in the book.
       	        	
  R  = (1-(Ee*Ee))/(1+(Ee*cos(math_misc.to_radians(ve))));	
        	
  if (rl < R)
  {
    temp=(rl*sin(math_misc.to_radians( (L-ll) ))) / (R-(rl*cos(math_misc.to_radians( (ll-L)))));
    lambda=180+L+math_misc.to_degrees(atan(temp));
  }
  else
  {
    temp=(R*sin(math_misc.to_radians((ll-L))))/(rl-(R*cos(math_misc.to_radians( (ll-L) ))));
    lambda=math_misc.to_degrees(atan(temp))+ll;
  }
        	
  if (lambda < 0.0)
    lambda += 360.0;
        	
  beta=rl*tan(math_misc.to_radians(phi))*sin(math_misc.to_radians( (lambda-ll) ));
  beta=atan( (beta/(R*sin(math_misc.to_radians( (ll-L))))) );
  beta = math_misc.to_degrees(beta);
        	     	
  // Now work out the distance from Earth.
  p=(R*R)+(r*r)-(2*R*r*cos(math_misc.to_radians( (l-L) )));
  p=sqrt(p);
        	
  comet_position[0] = lambda;
  comet_position[1] = beta;
  comet_position[2] = p;
  comet_position[3] = r;
       
  return comet_position;
}
      
// Position of a parabolic comet.
// Input parameters:
// comet_orbit_elements			- See below
// year					- --:
// month					-	:
// day						-	:-- Required date and time.
// hour					-	:
// min						-	:
// secs					-	:
// time_offset					- --:
// epoch_perihelion_of_Earth	- The epoch of perihelion for Earth in Julian date.
//
// The order of the orbital elements for the comet are:
//
//       Field	    Content					Units			Symbol
//       =====     =======       				=====			======
// 	   0	    The epoch of the perihelion		        Julian date		  t0
// 	   1	    Perihelion distance			        AU			  q
// 	   2	    Inclination of the orbit			degrees			  i
// 	   3	    Argument of the perihelion		        degrees			  w
// 	   4	    Longitude of the ascending node		degrees			  O
//
// The output from this function is:
//
//		Field		Content
//		=====		=======
//		  0		position - geo ecliptic lambda
//		  1		position - geo ecliptic beta
//  	  	  2		distance to Earth (AU)
//		  3		distance to Sun (AU)
double *comet_details::comet_position_parabolic(double *comet_orbit_elements,
                                                int year,
                                                int month,
                                                int day,
                                                int hour,
                                                int min,
                                                double secs,
                                                double time_offset,
                                                double epoch_perihelion_of_Earth)
{
  double julian_date;
  time_details time_functions;

  julian_date = time_functions.julian_date( year, month, day, hour, min, secs);
  
  // Take account of the time_offset.
  julian_date -= time_offset / 24.0;

  return comet_position_parabolic(comet_orbit_elements,julian_date,epoch_perihelion_of_Earth);
}


// Position of a parabolic comet.
// Input parameters:
// comet_orbit_elements	- See below
// julian_date			- The date and time of the observer as a Julian date.	
// epoch_perihelion_of_Earth	- The epoch of perihelion for Earth in Julian date.
//
// The order of the orbital elements for the comet are:
//
//       Field		Content					Units			Symbol
//       =====      	=======       				=====			======
// 	   0  		The epoch of the perihelion		Julian date		  t0
// 	   1            Perihelion distance			AU			  q
// 	   2	    	Inclination of the orbit		degrees			  i
// 	   3            Argument of the perihelion		degrees			  w
// 	   4	   	Longitude of the ascending node		degrees			  O
//
// The output from this function is:
//
//		Field		Content
//		=====		=======
//		  0		position - geo ecliptic lambda
//		  1		position - geo ecliptic beta
//  	  	  2	  	distance from Earth (AU)
//		  3		distance from Sun (AU)
double *comet_details::comet_position_parabolic(double *comet_orbit_elements,
                                                double julian_date,
                                                double epoch_perihelion_of_Earth)
{
  math_misc maths_misc;
  double w,d,s,stemp,sd;
  static double comet_position[4];	
  double v,r,y,x,angle,l,phi,ll,rl,temp,p;
  double Ne,Me,L,ve,R,no_of_days,lambda,beta;
        	
  double error = 0.0000001;
        	
  // Orbital details for the Earth.comet_details
  double Te = 1.00004,Eeta=99.403308,Elong_of_perihelion=102.768413,Ee=0.016713;
        		
  // Find d
  d = julian_date - comet_orbit_elements[0];
  
  w = ( 0.0364911624/(comet_orbit_elements[1] * sqrt(comet_orbit_elements[1])) ) * d;
        	
  // Solve s^3 + 3s - W = 0
  s = stemp = w/3;
  sd = s*s*s + 3*s - w;
        	
  while (abs(sd) >= error)
  {
    stemp = (2*(s*s*s) + w) / ( 3*(s*s + 1));
        		
    s = stemp;
        	
    sd = s*s*s + 3*s - w;
  }
     
  v = maths_misc.to_degrees( (2 * atan(s)) );
  r = comet_orbit_elements[1] * (1 + s*s );   	 	
        	
  l = v + (comet_orbit_elements[3] + comet_orbit_elements[4]);
        	
  phi = asin(sin(maths_misc.to_radians( (l - comet_orbit_elements[4]) ))*sin(maths_misc.to_radians(comet_orbit_elements[2])));
  phi = maths_misc.to_degrees(phi);        	
        	
  y = sin(maths_misc.to_radians( (l - comet_orbit_elements[4])) )*cos(maths_misc.to_radians(comet_orbit_elements[2]));
  x = cos(maths_misc.to_radians( (l - comet_orbit_elements[4])) );
        	
  angle = maths_misc.tan_correct_quadrant(x, y);
        	
  ll = angle + comet_orbit_elements[4];
  ll = maths_misc.angle_in_range(ll);
        	
  rl = r * cos(maths_misc.to_radians(phi));
        	
  // Work out the position of the Earth.
  no_of_days = epoch_perihelion_of_Earth - julian_date;
      	
  Ne = (360.0/365.242191) * (no_of_days/Te);

  // Make sure n is within the range 0-360.
  while ( !( ( Ne >= 0.0) && (Ne <= 360.0)) )
  {
    if ( Ne < 0.0)
      Ne += 360.0;
    else
      Ne -= 360.0;
  }
        	
  Me = Ne + Eeta - Elong_of_perihelion;

  L  = Ne + ((360.0/PI)*Ee*sin(maths_misc.to_radians(Me))) + Eeta;
       	
  // Make sure the value of L is correct.
  if (L > 360.0)
    L -= 360.0;
        	
  if (L < 0.0)
    L += 360.0;
        	    
  ve = L - Elong_of_perihelion;  // Initial approx in the book.
     	        	
  R  = (1-(Ee*Ee))/(1+(Ee*cos(maths_misc.to_radians(ve))));
               	
  if (rl < R)
  {    
    temp=(rl*sin(maths_misc.to_radians( (L-ll) ))) / (R-(rl*cos(maths_misc.to_radians( (L-ll)))));
    lambda=180+L+maths_misc.to_degrees(atan(temp));
  }
  else
  {
    temp=(R*sin(maths_misc.to_radians((ll-L))))/(rl-(R*cos(maths_misc.to_radians( (ll-L) ))));
    lambda=maths_misc.to_degrees(atan(temp))+ll;
  }
        	
  if (lambda < 0.0)
    lambda += 360.0;
        	
  beta=rl*tan(maths_misc.to_radians(phi))*sin(maths_misc.to_radians( (lambda-ll) ));
  beta=atan( (beta/(R*sin(maths_misc.to_radians( (ll-L))))) );
  beta = maths_misc.to_degrees(beta);
        	
  // Now work out the distance from Earth.
  p=(R*R)+(r*r)-(2*R*r*cos(maths_misc.to_radians( (l-L) )));
  p=sqrt(p);
        		
  comet_position[0] = lambda;
  comet_position[1] = beta;
  comet_position[2] = p;
  comet_position[3] = r;
       	
  return comet_position;
}


// Workout the rest of the details for a comet
struct astronomical_object comet_details::comet_values(double *output_value,
                                                       double *comet_orbit_elements,
                                                       double julian_date,
                                                       double longitude,
                                                       double latitude,
                                                       bool orbit_type,
                                                       double epoch_perihelion_of_Earth,
                                                       double absolute_mag,
                                                       double slope_param)
{
  static struct astronomical_object comet_position_details;
  //comet_details comet;
  sun sun_details;
  math_misc math_misc;
  double *output;
  double *sun_position;
  static double ecl_coords[2];
  //time_details time_functions;
  co_ord_conversion coord_conversion;

  comet_position_details.actual_geo_ecliptic_lambda = output_value[0];
  comet_position_details.actual_geo_ecliptic_beta   = output_value[1];
  comet_position_details.earth_object_distance      = output_value[2];
  comet_position_details.sun_object_distance        = output_value[3];

  comet_position_details.phase                      = 1;
  comet_position_details.magnitude                  = nan("");
  comet_position_details.angular_size               = nan("");

  // Light travel time.
  comet_position_details.light_travel_time          = comet_position_details.earth_object_distance * TIME_FOR_LIGHT_TO_TRAVEL_1_AU;

  // Work out the details for the Sun.
  sun_position = sun_details.sun_details(julian_date);

  // Effects of aberration.
  output = math_misc.aberration(sun_position[0], \
                                comet_position_details.actual_geo_ecliptic_lambda, \
                                comet_position_details.actual_geo_ecliptic_beta);

  comet_position_details.actual_geo_ecliptic_lambda += output[0];
  comet_position_details.actual_geo_ecliptic_beta   += output[1];

  output = coord_conversion.helio_ecl_to_geo_ecl(comet_position_details.actual_geo_ecliptic_lambda,
                                                 comet_position_details.actual_geo_ecliptic_beta,
                                                 comet_position_details.earth_object_distance,
                                                 sun_position[0],  // lambda of Sun
                                                 sun_position[1],  // beta of Sun
                                                 sun_position[2]); // Earth-Sun distance

  comet_position_details.actual_helio_ecliptic_lambda = output[0] + 180.0;
  comet_position_details.actual_helio_ecliptic_beta   = output[1];

  // Work out the equatorial co-ords.
  ecl_coords[0] = comet_position_details.actual_geo_ecliptic_lambda; // geo-centric ecliptic lambda.
  ecl_coords[1] = comet_position_details.actual_geo_ecliptic_beta;   // geo-centric ecliptic beta.

  output = coord_conversion.ecl_to_equ(&ecl_coords[0],julian_date);

  comet_position_details.equ_ra  = output[0];
  comet_position_details.equ_dec = output[1];

  // Work out the horizontal co-ordinates.
  output = coord_conversion.ecl_to_hor(&ecl_coords[0],julian_date,longitude,latitude);

  comet_position_details.hor_altitude = output[0];
  comet_position_details.hor_azimuth  = output[1];

  // Estimate the magnitude of the comet (visual).
  comet_position_details.magnitude = visual_magnitude(absolute_mag,
                                                      slope_param,
                                                      julian_date,
                                                      comet_position_details.sun_object_distance,
                                                      comet_position_details.earth_object_distance);

  // Work out the rise and set times and positions.
  output = comet_rise_and_set(julian_date, longitude, latitude, orbit_type, comet_orbit_elements, epoch_perihelion_of_Earth);

  comet_position_details.azimuth_rise = output[0];
  comet_position_details.azimuth_set  = output[1];
  comet_position_details.rise_time    = output[2];
  comet_position_details.transit_time = output[4];
  comet_position_details.set_time     = output[3];

  return comet_position_details;
}

// The interpolation rise/set method does not work for comets, so using brute
// force.
// See Atronomical Algorithums ch14
// Input:
// Julian_date	- The date in Julian date
// Longitude   - Longitude of the user (degrees)  pos values are East,
//                                                neg values are west.
// Latitude    - Latitude of the user (degrees).
// Orbit type  - Which type of orbit is the comet following:.
//					0 - periodic
//					1 - parabolic
//
// Output:
// Output[0] - Azimuth of the selected object to rise.
// Output[1] - Azimuth of the selected object to set.
// Output[2] - Time of the object rising (Julian date).
// Output[3] - Time of the object setting (Julian date).
// Output[4] - Time of when the object is in transit (Julian date).
double *comet_details::comet_rise_and_set(double julian_date,
                                          double longitude,
                                          double latitude,
                                          int orbit_type,
                                          double *comet_orbit_elements,
                                          double epoch_perihelion_of_Earth)
{
  //co_ord_conversion coord_conversion;
  static double output[5];
  double start_julian_date = 0;
  double loop_julian_date;
  double *hor_pos;
  double *temp;
  double altitude_previous_previous = 999.99,altitude_previous = 999.99,altitude_present;
  double root_start_rise,root_end_rise;
  double root_start_set,root_end_set;
  double time_1,time_2,time_3;
  long julian_date_as_integer;
  int loop;

  const double interval = (1.0/24.0);

  // Workout the Julian date of the day in question at 0h.
  julian_date_as_integer = (long)julian_date - 1;
  start_julian_date = (double)julian_date_as_integer + 0.5;

  // Find the hours before and after the comet rises and sets.
  altitude_previous = 0.0;
  altitude_present  = 0.0;

  for (loop = 0;loop < 25;loop++)
  {
        loop_julian_date = start_julian_date + (interval*(double)loop);

	hor_pos = interation_position(loop_julian_date,
                                      longitude,
                                      latitude,
                                      orbit_type,
                                      comet_orbit_elements,
                                      epoch_perihelion_of_Earth);

        altitude_previous_previous = altitude_previous;
	altitude_previous = altitude_present;
	altitude_present  = hor_pos[0];

	// Find the roots for the rise,set and transit.
	// Check for rise times.
	if ((altitude_previous <= 0) && (altitude_present >= 0))
	{
          root_start_rise = loop_julian_date - interval;
	  root_end_rise   = loop_julian_date;

	  temp = interation(root_start_rise,
                            root_end_rise,
                            0.001,
                            25,
                            orbit_type,
                            longitude,
                            latitude,
                            comet_orbit_elements,
                            epoch_perihelion_of_Earth);

	  output[0] = temp[1];
	  output[2] = temp[2];
	}

	// Check for set times.
	if ((altitude_previous >= 0) && (altitude_present <= 0))
	{
          root_start_set = loop_julian_date - interval;
	  root_end_set   = loop_julian_date;

	  temp = interation(root_start_set,
                            root_end_set,
                            0.001,
                            25,
                            orbit_type,
                            longitude,
                            latitude,
                            comet_orbit_elements,
                            epoch_perihelion_of_Earth);

	  output[1] = temp[1];
	  output[3] = temp[2];
	}

        // Find the transit time.
        if ((altitude_previous_previous <= altitude_previous) && (altitude_present <= altitude_previous) && (loop >= 3))
        {
          // Find the times this relates to.
          time_1 = loop_julian_date - (2 * interval);
          time_2 = loop_julian_date - interval;
          time_3 = loop_julian_date;

          temp = find_maxima(time_1,
                             time_2,
                             time_3,
                             longitude,
                             latitude,
                             orbit_type,
                             comet_orbit_elements,
                             epoch_perihelion_of_Earth);

           output[4] = temp[0];
        }

  }

  return output;
}

// This method finds the position of the comet in horizontal co-ords at a specified time.
// ++++ What the parameters do
// ++++ The output.
// Output - the position of the comet in horizontal co-ords:
//    output[0] = altitude of the comet(degrees)
//    output[1] = azimuth of the comet (degrees)
double *comet_details::interation_position(double julian_date,
                                           double longitude,
                                           double latitude,
                                           bool selector,
                                           double *comet_orbit_elements,
                                           double epoch_perihelion_of_Earth)
{
  co_ord_conversion coord_conversion;
  static double output[2];
  double *ecl_pos;
  double *hor_pos;

  // Select the type of comet orbit that is to be worked out.
  switch (selector)
  {
    case false :
      ecl_pos = comet_position_perodic(comet_orbit_elements,julian_date);
      break;
    case true :
      ecl_pos = comet_position_parabolic(comet_orbit_elements,
                                         julian_date,
                                         epoch_perihelion_of_Earth);
      break;
  }

  // Convert the comet ecliptic co-ords to horizontal co-ords.
  hor_pos = coord_conversion.ecl_to_hor(ecl_pos,julian_date,longitude,latitude);

  output[0] = hor_pos[0] - ATMOSPHERIC_REFRACTION;
  output[1] = hor_pos[1];

  return output;
}

// Use false position iteration to work out the rise and set times and positions
double *comet_details::interation(double s,
                                  double t,
                                  double e,
                                  int m,
                                  bool selector,
                                  double longitude,
                                  double latitude,
                                  double *comet_orbit_elements,
                                  double epoch_perihelion_of_Earth)
{
  static double output[3];
  double *temp;
  double fs[2],ft[2],fr[2];
  double r = 0.0;
  int n, side=0;

  // Starting values at endpoints of interval.
  temp = interation_position(s,longitude,latitude,selector,comet_orbit_elements,epoch_perihelion_of_Earth);

  fs[0] = temp[0];
  fs[1] = temp[1];

  temp = interation_position(t,longitude,latitude,selector,comet_orbit_elements,epoch_perihelion_of_Earth);

  ft[0] = temp[0];
  ft[1] = temp[1];

  for (n = 0; n < m; n++)
  {
	r = (fs[0]*t - ft[0]*s) / (fs[0] - ft[0]);

        if (fabs(t-s) < e*fabs(t+s))
	  break;

        temp = interation_position(r,longitude,latitude,selector,comet_orbit_elements,epoch_perihelion_of_Earth);

        fr[0] = temp[0];
        fr[1] = temp[1];

	if (fr[0] * ft[0] > 0)
	{
	  // fr and ft have same sign, copy r to t
	  t = r;
	  ft[0] = fr[0];

	  if (side==-1)
	  {
	    fs[0] /= 2;
	  }

	  side = -1;
	}
	else if (fs[0] * fr[0] > 0)
	{
	  // fr and fs have same sign, coproot_end_risey r to s
          s = r;
	  fs[0] = fr[0];

	  if (side==+1)
	  {
            ft[0] /= 2;
	  }

	  side = +1;
	}
	else
	{
	  // fr * f_ very small (looks like zero)
	  break;
	}
  }

  temp = interation_position(r,longitude,latitude,selector,comet_orbit_elements,epoch_perihelion_of_Earth);

  output[0] = temp[0];
  output[1] = temp[1];
  output[2] = r;

  return output;
}

// method to find a maxima when the derivative cannot be used.
// It is slow to converge though.
//double *comet_details::find_maxima(double a,double b,double c)
double *comet_details::find_maxima(double a,
                                   double b,
                                   double c,
                                   double longitude,
                                   double latitude,
                                   bool selector,
                                   double *comet_orbit_elements,
                                   double epoch_perihelion_of_Earth)
{
  static double transit[2];
  double *output;
  double y_middle,y_left,y_right;
  double time_middle = 0.0;
  int loop = 0;

  // Find if the maxima is to the left of b.
  while ((c - a) > 0.001)
  {
    time_middle = ((c - a) / 2.0) + a;

    output = interation_position(time_middle,longitude,latitude,selector,comet_orbit_elements,epoch_perihelion_of_Earth);
    y_middle = output[0];

    output = interation_position(c,longitude,latitude,selector,comet_orbit_elements,epoch_perihelion_of_Earth);
    y_right = output[0];

    output = interation_position(a,longitude,latitude,selector,comet_orbit_elements,epoch_perihelion_of_Earth);
    y_left = output[0];

    if (y_middle > y_left)
    {
      a = time_middle;
    }
    else if (y_middle > y_right)
    {
       c = time_middle;
    }

    loop++;
  }

  transit[0] = time_middle;
  output = interation_position(time_middle,longitude,latitude,selector,comet_orbit_elements,epoch_perihelion_of_Earth);
  transit[1] = output[1];

  return transit;
}

// Workout the visual magnitude of the comet.
double comet_details::visual_magnitude(double total_mag,
                                       double mag_slope,
                                       double julian_date,
                                       double ds,
                                       double de)
{
  double visual_magnitude;
  double sun_earth_distance,sto_angle,p;
  double *values;
  planets planet;

  // Work out the Sun-Object-Earth i.e. phase angle.
  // Find the Sun-Earth distance (in AU).
  values = planet.planet_position_values(julian_date, 2);
  sun_earth_distance = values[4];	// R

  sto_angle = (ds*ds) + (de*de) - (sun_earth_distance * sun_earth_distance);
  sto_angle = sto_angle / (2.0 * ds * de);
  sto_angle = acos(sto_angle);

  // Work out the terms for the magnitude equation.
  p = (1 + cos(sto_angle)) / 2.0;

  visual_magnitude = total_mag + (5 * log10(de)) + (2.5 * mag_slope * log10(ds)) - (2.5 * log10(p));

  return visual_magnitude;
}
