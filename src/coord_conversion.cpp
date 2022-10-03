// Code for the coord_conversion methods.
#include "coord_conversion.hpp"
#include "math.h"
#include "constants.hpp"
#include "math_misc.hpp"
#include "time_details.hpp"
#include <iostream>

using namespace std;
using namespace constants;

// Convert equatorial to horizon co-ord conversion.
// Input  - julian_date = The date of the observation (Julian date).
//        - RA          = The RA (decimal hours).
//        - Dec         = The DEC of the object (degrees).
//        - latitude    = The latitude of the observer (degrees).
//        - longituide  = The longitude of the observer (degrees).
// Output - [0] = altitude (in degrees)
//        - [1] = azimuth (in degrees)
double *co_ord_conversion::equ_to_hor(double julian_date,double ra,double dec,double latitude,double longitude)
{
  double a,b,a1,h1,lst,hour_angle;
  static double output[2];
  math_misc math_misc;
  time_details time_functions;

  // Work out the hour angle
  lst = time_functions.lst(julian_date,longitude);

  hour_angle = lst - ra;

  if (hour_angle < 0)
  {
    hour_angle += 24.0;
  }

  // Convert the hour angle into degrees.
  hour_angle *= HR_MOV;
        	
  // Find the altitude.
  // Find sin a.
  a = ((sin(math_misc.to_radians(dec)))*(sin(math_misc.to_radians(latitude)))) + 
      ( (cos(math_misc.to_radians(dec)))*(cos(math_misc.to_radians(latitude)))*(cos(math_misc.to_radians(hour_angle))));
        	
  // Find a. - altitude
  a = asin(a);   

  b = a;      
     
  // Update the astro class attribute.
  output[0] = math_misc.to_degrees(a);
        	
  // Find the azimuth
  // Find cos a1.
  a1 = ( (sin(math_misc.to_radians(dec)))-( (sin(math_misc.to_radians(latitude)))*(sin(b)) ) ) / 
	( (cos(math_misc.to_radians(latitude)))*(cos(b)) );
        	
  a1 = acos(a1);   
  a1 = math_misc.to_degrees(a1);
        	
  // Find the sin of the hour-angle.
  h1 = sin(math_misc.to_radians(hour_angle));
        	        	
  if (h1 > 0)
    a1 = 360.0-a1;
        	
  // Update the astro class attribute.
  output[1] = a1;
        	
  return output;
}
     
// Convert horizon co-ords to equatorial co-ords.
// Input : altitude      - elevation of the object from the horizon (degrees) (hor co-ord).
//         azimuth       - angle from north to the object (degrees) (hor co-ord).
//         latitude      - latitude of the observer (degrees).
//         time 	  - Time of the observation (Julian date).
// Output : output[0]    - RA
//          output[1]    - Dec
//          output[2]    - hour_angle
double *co_ord_conversion::hor_to_equ(double altitude, double azimuth, double latitude,double longitude,double time)
{
  static double output[3];
  double *date;
  double hour_angle,hour_anglel,delta,alpha,sinA,lst;
  math_misc math_misc;
  time_details time_details;
    	 
  // Work out the Dec.
  delta = sin(math_misc.to_radians(altitude))*sin(math_misc.to_radians(latitude));
  delta = delta + (cos(math_misc.to_radians(altitude))*cos(math_misc.to_radians(latitude)) * cos(math_misc.to_radians(azimuth))); 
  delta = math_misc.to_degrees(asin(delta));
    	 
  // Work out the hour-angle.
  hour_angle = sin(math_misc.to_radians(altitude))-(sin(math_misc.to_radians(latitude))*sin(math_misc.to_radians(delta)));
  hour_angle = hour_angle / (cos(math_misc.to_radians(latitude))*cos(math_misc.to_radians(delta)));
  hour_anglel = math_misc.to_degrees(acos(hour_angle));
  	 
  // Work out sin A.
  sinA = sin(math_misc.to_radians(azimuth));
  
  if (sinA < 0)
  {
    hour_angle = hour_anglel;
  }
  else
  {
    hour_angle = 360.0 - hour_anglel;
  }
    	 
  hour_angle /= 15.0;
         	     
  // Work out the RA.
  date = time_details.julian_to_date(time);
   	     
  lst  = time_details.lst(date[0],date[1],date[2],date[3],date[4],date[5],longitude);
  	     
  alpha = lst - hour_angle;
   	     
  if (alpha < 0.0)
  {
    alpha += 24.0;
  }
   	     
  // Output the results.
  output[0] = alpha; // RA
  output[1] = delta; // Dec
  output[2] = hour_angle; // hour angle in hours.
   	     
  return output;
}  
    	 
/* Work out the obliquity to the ecliptic - Astronomy for Your Calculator p41 */
/* Make private. */
double co_ord_conversion::obliquity_ecliptic(int year,int month,int day, int hour, int min,double sec,double offset)
{
  double t,e;
  int dec_hour;
  time_details time_details;
                
  dec_hour = hour;
  dec_hour += (int)offset;
        	
  t = time_details.julian_date(year,month,day,dec_hour,min,sec);
                            
  t = t - JULIAN2000JAN1_5;
                
  t = t / JULIAN_CENTURY;
  	        	
  e = (46.815*t)+(0.0006*(t*t))-(0.00181*(t*t*t));    
              
  e = e/3600.0;
            
  e = 23.439292 - e;
          
  return e;
}
        
/* Work out the obliquity to the ecliptic - Astronomy for Your Calculator p41 */
/* Input - t = Julian date */
/* Output    = obliquity to the ecliptic (degrees) */
/* Make private */
double co_ord_conversion::obliquity_ecliptic(double t)
{
  double e;
              
  t = t - JULIAN2000JAN1_5;
                
  t = t / JULIAN_CENTURY;
  	        	
  e = (46.815*t)+(0.0006*(t*t))-(0.00181*(t*t*t));    
              
  e = e/3600.0;

  e = 23.439292 - e;
          
  return e;
}
             
// Convert ecliptic co-ords to horizontal co-ords for a selected object.
// NB: The co-ords are to be in degrees.
// NB: Input  - ecl[0] 		= lambda
//              ecl[1] 		= beta
//		year			--:
//              month			  :
//              day			  :-- Time
//              hour			  :
//              minute			  :
//              seconds		          :
//              time_offset	        --:
//              longitude		--:-- Position
//              latitude		--:
//     Output - hor_co_ords[0] = altitude
//              hor_co_ords[1] = azimuth
double *co_ord_conversion::ecl_to_hor(double ecl[],int year, int month, int day,int hour, int minute,double seconds,double time_offset,double longitude,double latitude)
{
  double julian_time;
  time_details time_details;
  
  julian_time = time_details.julian_date(year,month,day,hour,minute,seconds);

  julian_time += time_offset / 24.0;

  return ecl_to_hor(ecl,julian_time,longitude,latitude);
}

// Convert ecliptic co-ords to horizontal co-ords for a selected object.
// NB: The co-ords are to be in degrees.
// NB: Input  - ecl.get_coord_a = lambda
//              ecl.get_coord_b = beta
//		julian date
//		longitude (degrees)
//		latitude        = latitude of the observer (+ve is north)(degrees)
//     Output - hor_co_ords.set_coord_a = altitude
//              hor_co_ords.set_coord_b = azimuth
double *co_ord_conversion::ecl_to_hor(double ecl[],double julian_date,double longitude,double latitude)
{
  static double hor_co_ords[2];
  double p,a1 = 0,e,st;
  math_misc math_misc;
  time_details time_details;
        	
  // Declare the arrays to be used.
  double v[3];
  double s[3];
  double r[3];
  double w[3];
        	
  double c1[3][3];
  double b[3][3];
  double a[3][3];
        	
  // Work out the value in matrix v.
  v[0] = cos(math_misc.to_radians(ecl[0]))*cos(math_misc.to_radians(ecl[1]));
  v[1] = sin(math_misc.to_radians(ecl[0]))*cos(math_misc.to_radians(ecl[1]));		
  v[2] = sin(math_misc.to_radians(ecl[1]));
        	              	
  e = obliquity_ecliptic(julian_date);

  // Work out the contents of array c1.
  c1[0][0] = 1.0;
  c1[0][1] = 0.0;
  c1[0][2] = 0.0;
        	
  c1[1][0] = 0.0;
  c1[1][1] = cos(math_misc.to_radians(e));
  c1[1][2] = -sin(math_misc.to_radians(e));
        	
  c1[2][0] = 0.0;
  c1[2][1] = sin(math_misc.to_radians(e));
  c1[2][2] = cos(math_misc.to_radians(e));
                
  // Work out the contents of s
  s[0] = (c1[0][0]*v[0]) + (c1[0][1]*v[1]) + (c1[0][2]*v[2]);
  s[1] = (c1[1][0]*v[0]) + (c1[1][1]*v[1]) + (c1[1][2]*v[2]);
  s[2] = (c1[2][0]*v[0]) + (c1[2][1]*v[1]) + (c1[2][2]*v[2]);
                        	
  // Convert the local siderial time into degrees.
  st = time_details.lst(julian_date,longitude);
  st *= HR_MOV;

  // Work out the contents of matrix b.
  b[0][0] = cos(math_misc.to_radians(st));
  b[0][1] = sin(math_misc.to_radians(st));
  b[0][2] = 0.0;
        	
  b[1][0] = sin(math_misc.to_radians(st));
  b[1][1] = -cos(math_misc.to_radians(st));
  b[1][2] = 0.0;
        	
  b[2][0] = 0.0;
  b[2][1] = 0.0;
  b[2][2] = 1.0;
                        	
  // Work out the contents of matrix r.
  r[0] = (b[0][0]*s[0]) + (b[0][1]*s[1]) + (b[0][2]*s[2]);
  r[1] = (b[1][0]*s[0]) + (b[1][1]*s[1]) + (b[1][2]*s[2]);
  r[2] = (b[2][0]*s[0]) + (b[2][1]*s[1]) + (b[2][2]*s[2]);
                        	
  // Work out the contents of matrix a.
  a[0][0]= -sin(math_misc.to_radians(latitude));
  a[0][1]= 0.0;
  a[0][2]= cos(math_misc.to_radians(latitude));
        	
  a[1][0]= 0.0;
  a[1][1]= -1.0;
  a[1][2]= 0.0;
        	
  a[2][0]= cos(math_misc.to_radians(latitude));
  a[2][1]= 0.0;
  a[2][2]= sin(math_misc.to_radians(latitude));
                
  // Work out the contents of matrix w.
  w[0] = (a[0][0]*r[0]) + (a[0][1]*r[1]) + (a[0][2]*r[2]);
  w[1] = (a[1][0]*r[0]) + (a[1][1]*r[1]) + (a[1][2]*r[2]);
  w[2] = (a[2][0]*r[0]) + (a[2][1]*r[1]) + (a[2][2]*r[2]);
        	
  // Find the azimuth.     	
  // Make sure that m is in the correct quadrant.
  a1 = math_misc.tan_correct_quadrant(w[0], w[1]);
        	
  // Find the altitude.
  p = asin(w[2]);
  p = math_misc.to_degrees(p);
        	       	    
  hor_co_ords[0] = p;
  hor_co_ords[1] = a1;
        	
  return hor_co_ords;
}
    
// Convert ecliptic to equatorial co-ords.
// NB: The co-ords are to be in degrees.
// NB: Input  - ecl.get_coord_a = lambda
//              ecl.get_coord_b = beta
//     Output - equ_co_ords.set_coord_a = RA (in hours)
//              equ_co_ords.set_coord_b = DEC (in degrees)
double *co_ord_conversion::ecl_to_equ(double ecl[],int year,int month,int day,int hour,int minute,double sec,double offset)
{
  static double equ_co_ords[2];
  double delta,alpha = 0,x,y,e;
  math_misc math_misc;
  //time_details time_details;
        	
  // Works best with the true value for obliquity_ecliptic and not mean.
  // The function here produces the mean value.
  // For the true value, work out the value of the nutation and add it to the mean value.
  e = obliquity_ecliptic(year,month,day,hour,minute,sec,offset);
          
  delta = (sin(math_misc.to_radians(ecl[1]))*(cos(math_misc.to_radians(e)))) + (cos(math_misc.to_radians(ecl[1]))*sin(math_misc.to_radians(e))*sin(math_misc.to_radians(ecl[0])));
        	
  delta = math_misc.to_degrees(asin(delta));
        	
  y = (sin(math_misc.to_radians(ecl[0]))*cos(math_misc.to_radians(e)))-(tan(math_misc.to_radians(ecl[1]))*sin(math_misc.to_radians(e)));
  x = cos(math_misc.to_radians(ecl[0]));
        
  alpha = math_misc.to_degrees(atan((y/x)));
        	        	
  // Bring a1 into the correct quadrant.
  alpha = math_misc.tan_correct_quadrant(x, y);
      	
  // Convert the RA to hours (from degrees).
  alpha = alpha / 15.0;
        	
  // Place the converted co-ords into the output array.
  equ_co_ords[0] = alpha;
  equ_co_ords[1] = delta;
        	
  return equ_co_ords;
}

// Convert ecliptic (either heliocentric or geocentric) to equatorial co-ords.
// NB: The co-ords are to be in degrees.
// NB: Input  - ecl.get_coord_a	 = lambda
//              ecl.get_coord_b	 = beta
//		julian_date		 = The Julian date 
//     Output - equ_co_ords.set_coord_a = RA (in hours)
//              equ_co_ords.set_coord_b = DEC (in degrees)
double *co_ord_conversion::ecl_to_equ(double *ecl,double julian_date)
{
  static double equ_co_ords[2];
  double delta,alpha = 0,x,y,e;
  math_misc math_misc;
        	
  // Works best with the true value for obliquity_ecliptic and not mean.
  // The function here produces the mean value.
  // For the true value, work out the value of the nutation and add it to the mean value.
  e = obliquity_ecliptic(julian_date);
          
  delta = (sin(math_misc.to_radians(ecl[1]))*(cos(math_misc.to_radians(e)))) + (cos(math_misc.to_radians(ecl[1]))*sin(math_misc.to_radians(e))*sin(math_misc.to_radians(ecl[0])));
        	    	
  delta = math_misc.to_degrees(asin(delta));
        	
  y = (sin(math_misc.to_radians(ecl[0]))*cos(math_misc.to_radians(e)))-(tan(math_misc.to_radians(ecl[1]))*sin(math_misc.to_radians(e)));
  x = cos(math_misc.to_radians(ecl[0]));
        
  alpha = math_misc.to_degrees(atan((y/x)));
        	        	
  // Bring a1 into the correct quadrant.
  alpha = math_misc.tan_correct_quadrant(x, y);
      	
  // Convert the RA to hours (from degrees).
  alpha = alpha / 15.0;
        	
  // Place the converted co-ords into the output array.
  equ_co_ords[0] = alpha;
  equ_co_ords[1] = delta;
        	
  return equ_co_ords;
}

// Convert helio ecliptic co-ords to geo ecliptic
// To convert the helio centric co-ords to geocentric (and visa-versa).
//
// To convert helio centric ecliptic co-ords to geo ecliptic co-ords
// The parameters are the helio centric co-ord of the object (with distance from the Sun) and the 
// helio centric coordates of the Earth (and distance between the Earth and the Sun).
// To obtain the helio ecliptic co-ords of the Earth:
// - Find the geo co-ord of the Sun
// - helio ecliptic longitude = geo ecliptic longitude + 180
// - helio ecliptic latitude  = - geo ecliptic latitude
// - helio ecliptic distance  = distance between the the Sun and the Earth. 
// 
// @Input:
// lambda_o  = helio ecliptic longitude of object (degrees)
// beta_o    = helio ecliptic latitude of object (degrees)
// dist_o    = distance of object from Sun (AU)
// lambda_e  = helio ecliptic longitude of Earth (degrees)
// beta_e    = helio ecliptic latitude of Earth (degrees)
// dist_e    = distance between Earth and the Sun (AU).
// 
// @output:
// output[0] = geo ecliptic longitude of object (degrees) 
// output[1] = geo ecliptic latitude of object (degrees)
// output[2] = distance of object from the Earth (AU)
// 
// To convert geo centric co-ords to helio centric ecliptic co-ords
// The parameters are the geo centric co-ord of the object (with distance from Earth) and the 
// geo centric coordates of the Sun (and distance between the Earth and the Sun).
// 
// @Input:
// lambda_o  = geo ecliptic longitude of object (degrees)
// beta_o    = geo ecliptic latitude of object (degrees)
// dist_o    = distance of object from Earth (AU)
// lambda_e  = geo ecliptic longitude of the Sun (degrees)
// beta_e    = geo ecliptic latitude of the Sun (degrees)
// dist_e    = distance between Earth and the Sun (AU).
// 
// @output:
// output[0] = helio ecliptic longitude of object (degrees) 
// output[1] = helio ecliptic latitude of object (degrees)
// output[2] = distance of object from the Sun (AU)
double *co_ord_conversion::helio_ecl_to_geo_ecl(double lambda_o,double beta_o,double dist_o,double lambda_e,double beta_e,double dist_e)
{
  static double output[3];
  double x,y,z;	
  math_misc math_misc;
  
  x = dist_o * cos(math_misc.to_radians(beta_o)) * cos(math_misc.to_radians(lambda_o)); 
  x -= dist_e * cos(math_misc.to_radians(beta_e)) * cos(math_misc.to_radians(lambda_e));
  
  y = dist_o * cos(math_misc.to_radians(beta_o)) * sin(math_misc.to_radians(lambda_o));
  y -= dist_e * cos(math_misc.to_radians(beta_e)) * sin(math_misc.to_radians(lambda_e));
  
  z = dist_o * sin(math_misc.to_radians(beta_o)) - dist_e * sin(math_misc.to_radians(beta_e));

  output[2] = sqrt( (x*x)+(y*y)+(z*z) );
  output[1] = z / sqrt( (x*x) + (y*y) );
  output[1] = math_misc.to_degrees(atan(output[1]));
  output[0] = math_misc.to_degrees(atan( ( y/x) ));
  
  if (output[0] < 0)
  {
    output[0] += 360.0;
  }

  return output;
}


