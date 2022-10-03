#include "api_interface.hpp"
#include "constants.hpp"
#include "star.hpp"
#include "math_misc.hpp"
#include "time_details.hpp"
#include "sun.hpp"
#include "moon.hpp"
#include "comet_details.hpp"
#include "planets.hpp"
#include "astronomy_object.hpp"
#include "coord_conversion.hpp"

#include <iostream>
#include <cmath>

using namespace std;
using namespace constants;

// Position of a binary star.
double* api_interface::double_star(int year, int month, int day,int hour,int min,double secs,double time_offset,double period,double periastron,double semi_major,double e,double i, double w,double pa) const
{
  star binary;
  time_details time_functions;
  double years;		
	
  years = time_functions.decimal_year(year, month, day, hour, min, secs, time_offset);
	
  return binary.double_star(years,period,periastron,semi_major,e,i,w,pa);
}

// Star rise/set
double *api_interface::star_rise_set(double julian_date,double longitude,double latitude,double *star_eq_coords) const
{
  math_misc math_misc;

  return math_misc.rise_and_set_interpolate(julian_date,longitude,latitude,OBJECT_ID_STAR,star_eq_coords,NULL,0);
}

// Time methods
double api_interface::julian_date(int year,int month,int day,int hour,int min,double sec) const
{
  time_details time_functions;
	
  return time_functions.julian_date( year, month, day, hour, min, sec);
}

double *api_interface::julian_to_date(double julian_date) const
{
  time_details time_functions;
	
  return time_functions.julian_to_date(julian_date);
}

double api_interface::gst(int year, int month, int day, int hour, int min, double seconds) const
{
  time_details time_functions;
	
  return time_functions.gst(year, month, day, hour, min, seconds);	
}

double api_interface::gst(double jd) const
{
  time_details time_functions;

  return time_functions.gst(jd);
}

double api_interface::lst(int year, int month, int day,int hour,int min,double secs,double time_offset,double longitude) const
{
  time_details time_functions;
	
  return time_functions.lst(year, month, day, hour, min, secs, time_offset, longitude);
}

double api_interface::lst(double julian_date,double longitude) const
{
  time_details time_functions;
	
  return time_functions.lst(julian_date, longitude);
}

double api_interface::lst_to_gst(double lst,double longitude) const
{
  time_details time_functions;
	
  return time_functions.lst_to_gst(lst, longitude);
}

double api_interface::gst_to_ut(int year,int month,int day,double gst) const
{
  time_details time_functions;

  return time_functions.gst_to_ut(year, month, day, gst);
}

double api_interface::gst_to_ut(double julian_date,double gst) const
{
  time_details time_functions;
	
  return time_functions.gst_to_ut(julian_date, gst);
}

// co-ord methods.
double *api_interface::equ_to_hor(double julian_date,double ra,double dec,double latitude,double longitude) const
{
  co_ord_conversion co_ords;
  
  return co_ords.equ_to_hor(julian_date,ra,dec,latitude,longitude);
}

double *api_interface::hor_to_equ(double altitude, double azimuth, double latitude,double longitude,double time) const
{
  co_ord_conversion co_ords;
  
  return co_ords.hor_to_equ(altitude, azimuth, latitude, longitude, time);
}

double *api_interface::ecl_to_hor(double *ecl,
	                           int year, 
  		                   int month, 
  		                   int day, 
  		                   int hour, 
  		                   int minute, 
  		                   double seconds, 
  		                   double time_offset, 
  		                   double longitude,
  		                   double latitude) const
{
  co_ord_conversion co_ords;
  
  return co_ords.ecl_to_hor(ecl,         \
	                    year,        \
  		            month,       \
  		            day,         \
  		            hour,        \
  		            minute,      \
  		            seconds,     \
  		            time_offset, \
  		            longitude,   \
  		            latitude);
}
  		     
double *api_interface::ecl_to_hor(double *ecl,double julian_date,double longitude,double latitude) const
{
  co_ord_conversion co_ords;
  
  return co_ords.ecl_to_hor(ecl, julian_date, longitude, latitude);
}

double *api_interface::ecl_to_equ(double *ecl,int year,int month,int day,int hour,int minute,double sec,double offset) const
{
  co_ord_conversion co_ords;
  
  return co_ords.ecl_to_equ(ecl, year, month, day, hour, minute, sec, offset);
}

double *api_interface::ecl_to_equ(double *ecl,double julian_date) const
{
  co_ord_conversion co_ords;
  
  return co_ords.ecl_to_equ(ecl, julian_date);
} 

double *api_interface::helio_ecl_to_geo_ecl(double lambda_o,double beta_o,double dist_o,double lambda_e,double beta_e,double dist_e) const
{
  co_ord_conversion co_ords;
  
  return co_ords.helio_ecl_to_geo_ecl(lambda_o, beta_o, dist_o, lambda_e, beta_e, dist_e);
}

// Comet methods.
struct astronomical_object api_interface::comet_position_perodic(double *comet_orbit_elements,
                                                    int year,
                                                    int month,
                                                    int day,
                                                    int hour,
                                                    int min,
                                                    double secs,
                                                    double time_offset,
                                                    double longitude,
                                                    double latitude,
                                                    double absolute_mag,
                                                    double slope_param) const
{
  static struct astronomical_object comet_position_details;
  comet_details comet;
  double *output;
  double julian_time;

  // Find the position of the comet.
  output = comet.comet_position_perodic(comet_orbit_elements, \
                                        year,                 \
                                        month,                \
                                        day,                  \
                                        hour,                 \
                                        min,                  \
                                        secs,                 \
                                        time_offset);

  julian_time = julian_date( year, month, day, hour, min, secs);

  comet_position_details = comet.comet_values(output,comet_orbit_elements,julian_time,longitude,latitude,false,0,absolute_mag,slope_param);


  return comet_position_details;
}

struct astronomical_object api_interface::comet_position_perodic(double *comet_orbit_elements,
                                                                  double julian_date,
                                                                  double longitude,
                                                                  double latitude,
                                                                  double absolute_mag,
                                                                  double slope_param) const
{
  static struct astronomical_object comet_position_details;
  comet_details comet;
  double *output;

  // Find the position of the comet.
  output = comet.comet_position_perodic(comet_orbit_elements,julian_date);

  comet_position_details = comet.comet_values(output,comet_orbit_elements,julian_date,longitude,latitude,false,0,absolute_mag,slope_param);

  return comet_position_details;
}

struct astronomical_object api_interface::comet_position_parabolic(double *comet_orbit_elements,
                                                                    int year,
                                                                    int month,
                                                                    int day,
                                                                    int hour,
                                                                    int min,
                                                                    double secs,
                                                                    double time_offset,
                                                                    double epoch_perihelion_of_Earth,
                                                                    double longitude,
                                                                    double latitude,
                                                                    double absolute_mag,
                                                                    double slope_param) const
{
    static struct astronomical_object comet_position_details;
    comet_details comet;
    double *output;
    double julian_time;

    // Find the position of the comet.
    output = comet.comet_position_parabolic(comet_orbit_elements,       \
                                            year,                       \
                                            month,                      \
                                            day,                        \
                                            hour,                       \
                                            min,                        \
                                            secs,                       \
                                            time_offset,                \
                                            epoch_perihelion_of_Earth
                                            );

    julian_time = julian_date( year, month, day, hour, min, secs);

    comet_position_details = comet.comet_values(output,comet_orbit_elements,julian_time,longitude,latitude,true,epoch_perihelion_of_Earth,absolute_mag,slope_param);

    return comet_position_details;

}

struct astronomical_object api_interface::comet_position_parabolic(double *comet_orbit_elements,
                                                                   double julian_date,
                                                                   double epoch_perihelion_of_Earth,
                                                                   double longitude,
                                                                   double latitude,
                                                                   double absolute_mag,
                                                                   double slope_param) const
{
    static struct astronomical_object comet_position_details;
    comet_details comet;
    double *output;

    // Find the position of the comet.
    output = comet.comet_position_parabolic(comet_orbit_elements, \
                                            julian_date,          \
                                            epoch_perihelion_of_Earth);

    comet_position_details = comet.comet_values(output,comet_orbit_elements,julian_date,longitude,latitude,true,epoch_perihelion_of_Earth,absolute_mag,slope_param);

    return comet_position_details;

}

// Solar system objects
struct astronomical_object *api_interface::object_details(const double julian_date,const double longitude,const double latitude) const
{
  static struct astronomical_object object[11];
  double *output;
  static double ecl_coords[2];
  struct astronomical_object *planet_details;
  math_misc math_misc;
  sun sun_details;
  moon moon_details;
  planets planet;
  co_ord_conversion coord_conversion;
  int planet_id;

  // Work out the details for the Sun.
  output = sun_details.sun_details(julian_date);

  // output[0] = Geo ecliptic co-ord lambda.
  // output[1] = Geo ecliptic co-ord beta.
  // output[2] = Sun-Earth distance (AU).
  // output[3] = Angular size (arc seconds)
  // output[4] = Light travel time (seconds)
  // output[5] = Mean anomaly of the Sun (degrees)
  object[OBJECT_ID_SUN].actual_geo_ecliptic_lambda = output[0];
  object[OBJECT_ID_SUN].actual_geo_ecliptic_beta   = output[1];
  object[OBJECT_ID_SUN].earth_object_distance      = output[2];
  object[OBJECT_ID_SUN].angular_size               = output[3];
  object[OBJECT_ID_SUN].light_travel_time          = output[4];
  object[OBJECT_ID_SUN].sun_object_distance        = 0.0;
  object[OBJECT_ID_SUN].phase                      = 1.0;
  object[OBJECT_ID_SUN].magnitude                  = -26.7;

  // Work out the helio ecliptic co-ords for the Sun, which are always 0.0 and 0.0.	
  object[OBJECT_ID_SUN].actual_helio_ecliptic_lambda = 0.0;
  object[OBJECT_ID_SUN].actual_helio_ecliptic_beta   = 0.0;
		
  // Work out the equatorial co-ords.
  ecl_coords[0] = output[0]; // geo-centric ecliptic lambda.
  ecl_coords[1] = output[1]; // geo-centric ecliptic beta.

  output = coord_conversion.ecl_to_equ(&ecl_coords[0],julian_date); 
	
  object[OBJECT_ID_SUN].equ_ra  = output[0];
  object[OBJECT_ID_SUN].equ_dec = output[1];

  // Work out the horizontal co-ordinates.
  output = coord_conversion.ecl_to_hor(&ecl_coords[0],julian_date,longitude,latitude); 
	
  object[OBJECT_ID_SUN].hor_altitude = output[0];
  object[OBJECT_ID_SUN].hor_azimuth  = output[1];
  
  // Workout the ecliptic co-ords for Earth - needed for co-ord conversions for the other objects.
  object[OBJECT_ID_EARTH].actual_helio_ecliptic_lambda = object[OBJECT_ID_SUN].actual_geo_ecliptic_lambda + 180.0;
  object[OBJECT_ID_EARTH].actual_helio_ecliptic_beta   = -object[OBJECT_ID_SUN].actual_geo_ecliptic_beta;
  object[OBJECT_ID_EARTH].sun_object_distance          = object[OBJECT_ID_SUN].earth_object_distance;
  object[OBJECT_ID_EARTH].actual_geo_ecliptic_lambda   = 0.0;
  object[OBJECT_ID_EARTH].actual_geo_ecliptic_beta     = 0.0;
  object[OBJECT_ID_EARTH].earth_object_distance        = 0.0;

  // Work out the details for the Moon.
  // output[0] = Geo ecliptic co-ord lambda.
  // output[1] = Geo ecliptic co-ord beta.
  // output[2] = Sun-Earth distance (AU).
  // output[3] = Angular size (arc seconds)
  // output[4] = Light travel time (seconds)
  // output[5] = phase
  output = moon_details.moon_details(julian_date);
	
  object[OBJECT_ID_MOON].actual_geo_ecliptic_lambda = output[0];
  object[OBJECT_ID_MOON].actual_geo_ecliptic_beta   = output[1];
  object[OBJECT_ID_MOON].earth_object_distance      = output[2];
  object[OBJECT_ID_MOON].angular_size               = output[3];
  object[OBJECT_ID_MOON].light_travel_time          = output[4];
  object[OBJECT_ID_MOON].phase		      = output[5];
  object[OBJECT_ID_MOON].magnitude                  = -12.7; 
	  
  output = coord_conversion.helio_ecl_to_geo_ecl(object[OBJECT_ID_MOON].actual_geo_ecliptic_lambda,
                                                 object[OBJECT_ID_MOON].actual_geo_ecliptic_beta,
                                                 object[OBJECT_ID_MOON].earth_object_distance,
                                                 object[OBJECT_ID_EARTH].actual_helio_ecliptic_lambda,
                                                 object[OBJECT_ID_EARTH].actual_helio_ecliptic_beta,
                                                 object[OBJECT_ID_EARTH].sun_object_distance);  
  
  object[OBJECT_ID_MOON].actual_helio_ecliptic_lambda = output[0];
  object[OBJECT_ID_MOON].actual_helio_ecliptic_beta   = output[1];
  object[OBJECT_ID_MOON].sun_object_distance          = output[2];
  
  // Work out the equatorial co-ords.
  ecl_coords[0] = object[OBJECT_ID_MOON].actual_geo_ecliptic_lambda; // geo-centric ecliptic lambda.
  ecl_coords[1] = object[OBJECT_ID_MOON].actual_geo_ecliptic_beta; // geo-centric ecliptic beta.
	
  output = coord_conversion.ecl_to_equ(&ecl_coords[0],julian_date); 
	
  object[OBJECT_ID_MOON].equ_ra  = output[0];
  object[OBJECT_ID_MOON].equ_dec = output[1];

  // Work out the horizontal co-ordinates.
  output = coord_conversion.ecl_to_hor(&ecl_coords[0],julian_date,longitude,latitude); 
	
  object[OBJECT_ID_MOON].hor_altitude = output[0];
  object[OBJECT_ID_MOON].hor_azimuth  = output[1];

  // Work out the details for the planets.
  planet_details = planet.planet_all_details(julian_date);
  
                 
  for (planet_id = 0;planet_id < 8;planet_id++)
  { 
     if ((planet_id + OBJECT_ID_MERCURY) != OBJECT_ID_EARTH)
     {          
       // Effects of aberration.
       output = math_misc.aberration(object[OBJECT_ID_SUN].actual_geo_ecliptic_lambda, \
                                     planet_details[planet_id].actual_geo_ecliptic_lambda, \
                                     planet_details[planet_id].actual_geo_ecliptic_beta);
	          
       planet_details[planet_id].actual_geo_ecliptic_lambda += output[0];
       planet_details[planet_id].actual_geo_ecliptic_beta   += output[1];
     }
        
     object[(planet_id + OBJECT_ID_MERCURY)].actual_geo_ecliptic_lambda   = planet_details[planet_id].actual_geo_ecliptic_lambda;
     object[(planet_id + OBJECT_ID_MERCURY)].actual_geo_ecliptic_beta     = planet_details[planet_id].actual_geo_ecliptic_beta;
     object[(planet_id + OBJECT_ID_MERCURY)].apparent_geo_ecliptic_lambda = planet_details[planet_id].apparent_geo_ecliptic_lambda;
     object[(planet_id + OBJECT_ID_MERCURY)].apparent_geo_ecliptic_beta   = planet_details[planet_id].apparent_geo_ecliptic_beta;
     
     if ((planet_id + OBJECT_ID_MERCURY) != OBJECT_ID_EARTH)
     {          
       object[(planet_id + OBJECT_ID_MERCURY)].sun_object_distance        = planet_details[planet_id].sun_object_distance;
     }
     
     object[(planet_id + OBJECT_ID_MERCURY)].earth_object_distance        = planet_details[planet_id].earth_object_distance;
     object[(planet_id + OBJECT_ID_MERCURY)].light_travel_time            = planet_details[planet_id].light_travel_time;
     object[(planet_id + OBJECT_ID_MERCURY)].phase                        = planet_details[planet_id].phase;
     object[(planet_id + OBJECT_ID_MERCURY)].magnitude                    = planet_details[planet_id].magnitude;
     object[(planet_id + OBJECT_ID_MERCURY)].angular_size                 = planet_details[planet_id].angular_size;
     object[(planet_id + OBJECT_ID_MERCURY)].rise_time                    = planet_details[planet_id].rise_time;
     object[(planet_id + OBJECT_ID_MERCURY)].set_time                     = planet_details[planet_id].set_time;

     output = coord_conversion.helio_ecl_to_geo_ecl(object[(planet_id + OBJECT_ID_MERCURY)].actual_geo_ecliptic_lambda,
                                                    object[(planet_id + OBJECT_ID_MERCURY)].actual_geo_ecliptic_beta,
                                                    object[(planet_id + OBJECT_ID_MERCURY)].earth_object_distance,
                                                    object[OBJECT_ID_SUN].actual_geo_ecliptic_lambda,
                                                    object[OBJECT_ID_SUN].actual_geo_ecliptic_beta,
                                                    object[OBJECT_ID_SUN].earth_object_distance);  

     if ( ((planet_id + OBJECT_ID_MERCURY) == OBJECT_ID_MERCURY) || ((planet_id + OBJECT_ID_MERCURY) == OBJECT_ID_VENUS) )
     {
       output[0] = output[0] + 180.0;
       object[(planet_id + OBJECT_ID_MERCURY)].actual_helio_ecliptic_lambda = math_misc.angle_in_range(output[0]);     
     }
     else
     {
       object[(planet_id + OBJECT_ID_MERCURY)].actual_helio_ecliptic_lambda = output[0];
     }
     
     object[(planet_id + OBJECT_ID_MERCURY)].actual_helio_ecliptic_beta   = output[1];

     if ((planet_id + OBJECT_ID_MERCURY) != OBJECT_ID_EARTH)
     {           
       // Work out the equatorial co-ords.
       ecl_coords[0] = planet_details[planet_id].actual_geo_ecliptic_lambda; // geo-centric ecliptic lambda.
       ecl_coords[1] = planet_details[planet_id].actual_geo_ecliptic_beta;   // geo-centric ecliptic beta.
	
       output = coord_conversion.ecl_to_equ(&ecl_coords[0],julian_date); 
	
       object[(planet_id + OBJECT_ID_MERCURY)].equ_ra  = output[0];
       object[(planet_id + OBJECT_ID_MERCURY)].equ_dec = output[1];

       // Work out the horizontal co-ordinates.
       output = coord_conversion.ecl_to_hor(&ecl_coords[0],julian_date,longitude,latitude); 
	
       object[(planet_id + OBJECT_ID_MERCURY)].hor_altitude = output[0];
       object[(planet_id + OBJECT_ID_MERCURY)].hor_azimuth  = output[1];
     }
   }
        
   // Work out the rise and set related details.
   // Work out the rise and set details for the Sun.
        
   // Output[0] - Azimuth of the selected object to rise.
   // Output[1] - Azimuth of the selected object to set.		 
   // Output[2] - Time of the object rising (Julian date).
   // Output[3] - Time of the object setting (Julian date).
   // Output[4] - Time of when the object is in transit.
   output = math_misc.rise_and_set_interpolate(julian_date,longitude,latitude,OBJECT_ID_SUN,NULL,NULL,0);
        
   object[OBJECT_ID_SUN].azimuth_rise = output[0];
   object[OBJECT_ID_SUN].azimuth_set  = output[1];
   object[OBJECT_ID_SUN].rise_time    = output[2];
   object[OBJECT_ID_SUN].transit_time = output[4];
   object[OBJECT_ID_SUN].set_time     = output[3];

   output = math_misc.rise_and_set_interpolate(julian_date,longitude,latitude,OBJECT_ID_MOON,NULL,NULL,0);
        
   object[OBJECT_ID_MOON].azimuth_rise = output[0];
   object[OBJECT_ID_MOON].azimuth_set  = output[1];
   object[OBJECT_ID_MOON].rise_time    = output[2];
   object[OBJECT_ID_MOON].transit_time = output[4];
   object[OBJECT_ID_MOON].set_time     = output[3];
        
   // Work out the rise and set details for the planets.
   for (planet_id = OBJECT_ID_MERCURY;planet_id < MAX_CORE_OBJECT_ID;planet_id++)
   {
      if (planet_id != OBJECT_ID_EARTH)
      {
        output = math_misc.rise_and_set_interpolate(julian_date,longitude,latitude,planet_id,NULL,NULL,0);
                
        object[planet_id].azimuth_rise = output[0];
        object[planet_id].azimuth_set  = output[1];
        object[planet_id].rise_time    = output[2];
        object[planet_id].transit_time = output[4];
        object[planet_id].set_time     = output[3];
      }
      else
      {
        object[planet_id].azimuth_rise = 0.0;
        object[planet_id].azimuth_set  = 0.0;
        object[planet_id].rise_time    = 0.0;
        object[planet_id].transit_time = 0.0;
        object[planet_id].set_time     = 0.0;
      }   
    }

    return object;
}
