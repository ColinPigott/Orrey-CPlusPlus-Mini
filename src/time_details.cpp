// This class handles the time functions.
#include <iostream>
#include <math.h>
#include "constants.hpp"
#include "time_details.hpp"
#include <iomanip>

using namespace std;
using namespace constants;

// Produce the year in decimal form, e.g. 1934.008    
double time_details::decimal_year(int year, int month, int day,int hour,int min,double secs,double time_offset)
{
  double decimal_year;
    	
  decimal_year = year + ((double)(month-1)/12.0) + ((double)(day-1)/365.25) + ((double)hour/8766.0) + ((double)min/525960.0) + ((double)secs/31557600.0);
  decimal_year += (double)time_offset / 8766;
    	    	
  return decimal_year;
}    
    
// Produce the year in decimal form, e.g. 1934.008
double time_details::decimal_year(double julian_date)
{
  double decimal_year;
  double *date_and_time;
    	 
  date_and_time = julian_to_date(julian_date);
    	
  // date_and_time[0] = year;	
  // date_and_time[1] = month;
  // date_and_time[2] = day;  
  // date_and_time[3] = hours;
  // date_and_time[4] = mins; 
  // date_and_time[5] = seconds;
    	
  decimal_year = date_and_time[0] + ((date_and_time[1]-1)/12.0) + ((date_and_time[2]-1)/365.25) + (date_and_time[3]/8766.0) + (date_and_time[4]/525960.0) + (date_and_time[5]/31557600.0);
    	
  return decimal_year;
}
     
// Workout the Julian day.
// NB: This function will not work, if the date is before
// 1582 October 15th.
double time_details::julian_date(int year,int month,int day,int hour,int min,double sec)
{
  int year1,month1,a,b,c,d;
  double julian,days,dec_hour;
            
  dec_hour = hour + ((double)min/60) + (sec/3600.0);       
           
  days = (double)day + (dec_hour/24);
           
  if ((month == 1) || (month == 2))
  {
    year1 = year - 1;
    month1 = month + 12;
  }
  else
  {
    year1 = year;
    month1 = month;
  }

#if 0	// Original code
  // This part will only work if the date is after 1582 Oct 15.
  a = (int)floor((year1/100));
  b = 2-a+(int)floor((a/4));

  if (year1 < 0)
  {
    c = (int)floor(((365.25*year1)-0.75));
  }
  else
  {
    c = (int)floor(((365.25*year1)));
  }

  d = (int)floor((30.6001*(month1+1)));
#endif

  // This part will only work if the date is after 1582 Oct 15.
  a = (int)((year1/100));
  b = 2-a+(int)((a/4));

  if (year1 < 0)
  {
    c = (int)(((365.25*year1)-0.75));
  }
  else
  {
    c = (int)(((365.25*year1)));
  }

  d = (int)((30.6001*(month1+1)));


  julian = b + c + d + days + 1720994.5;

  return julian;
}
	
double time_details::julian_date(double year,double month,double day,double hour,double min,double sec)
{
  int a,b,c,d,year1,month1;
  double julian,days,dec_hour;
            
  dec_hour = hour + (min/60) + (sec/3600.0);       
            
  days = day + (dec_hour/24);
            
  if ((month == 1) || (month == 2))
  {
    year1 = (int)(year - 1);
    month1 = (int)(month + 12);
  }
  else
  {
    year1 = (int)year;
    month1 = (int)month;
  }

  // This part will only work if the date is after 1582 Oct 15.
  a = (int)floor((year1/100));
  b = 2-a+(int)floor((a/4));

  if (year1 < 0)
  {
    c = (int)floor(((365.25*year1)-0.75));
  }
  else
  {
    c = (int)floor(((365.25*year1)));
  }

  d = (int)floor((30.6001*(month1+1)));
           
  julian = b + c + d + days + 1720994.5;

  return julian;
}
	
// Convert the Julian date to year,month,day, etc.
double *time_details::julian_to_date(double julian_date)
{
  static double output[7];
  double i,f,a,b,c,d,e,g,h,j,seconds,mins,hours,day,month,year;
		
  julian_date += 0.5;
		 
  f = julian_date - floor(julian_date);
  i = floor(julian_date);
			
  if (i > 2299160.0)
  {
    a = floor( ((i - 1867216.25)/36524.25) );
    b = i + 1 + a - floor( (a/4) ); 
  }
  else
    b = i;
	     			 
  c = b + 1524;
  d = floor( ((c-122.1)/365.25) );
  e = floor( (365.25*d) );
  g = floor( ((c-e)/30.6001) );
	 
  day   = c-e+f-floor( (30.6001*g) );
		 
  if (g < 13.5)
  {
    month = g - 1.0;
  }
  else
  {
    month = g - 13.0;
  }
			 
  if (month > 2.5)
  {
    year = d - 4716.0;
  }
  else
  {
    year = d - 4715.0;
  }
			 
  j       = (day - floor(day)) * 24.0;
  hours   = floor(j);
		 
  h       = (j - floor(j)) * 60.0;
  mins    = floor(h);
		 
  seconds = (h - floor(h)) * 60.0;

  output[0] = (double)(int)year;	//converted_date.set_coord_a(year);
  output[1] = (double)(int)month; //converted_date.set_coord_b(month);
  output[2] = (double)(int)day;   //converted_date.set_extra_field1(Math.floor(day));
  output[3] = (double)(int)hours; //converted_date.set_extra_field2(hours);
  output[4] = (double)(int)mins;   //converted_date.set_extra_field3(mins);
  output[5] = seconds;//converted_date.set_extra_field4(seconds);
		 
  return output;
}

// Work out the Greenwich Siderial Time.
double time_details::gst(int year, int month, int day, int hour, int min, double seconds)
{
  double s,jd,t,t0,ut;

  jd = julian_date(year,month,day,0,0,0.0);
            
  s  = jd - 2451545.0;
  t  = s/36525.0;
  t0 = 6.697374558 + (2400.051336*t) + (0.000025862*(t*t));
            
  // Change t0 to the range 0-24. 
  while ( (t0 >= 24.0) || (t0 < 0.0) )
  {
    if (t0 < 0.0)
      t0 += 24.0;
    else
      t0 -= 24.0;               
  }
                                    
  // Take account of the time offset.
  ut = (double)hour + ((double)min/60.0) + (seconds/3600.0);   

  ut = ut * 1.002737909;
  t0 += ut;

  // Change t0 to the range 0-24.
  while ( (t0 >= 24.0) || (t0 < 0.0) )
  {
    if (t0 < 0.0)
      t0 += 24.0;
    else
      t0 -= 24.0;
  }
                      
  return t0;
}

// Work out the Greenwich Siderial Time.
double time_details::gst(double year, double month, double day, double hour, double min, double seconds)
{
  double s,jd,t,t0,ut;

  jd = julian_date((int)year,(int)month,(int)day,0,0,0.0);
            
  s  = jd - 2451545.0;
  t  = s/36525.0;
  t0 = 6.697374558 + (2400.051336*t) + (0.000025862*(t*t));
            
  // Change t0 to the range 0-24.
  while ( (t0 >= 24.0) || (t0 < 0.0) )
  {
    if (t0 < 0.0)
      t0 += 24.0;
    else
      t0 -= 24.0;
  }
                                    
  // Take account of the time offset.
  ut = hour + (min/60.0) + (seconds/3600.0);   
                       
  ut = ut * 1.002737909;
  t0 += ut;
            
  // Change t0 to the range 0-24.
  while ( (t0 >= 24.0) || (t0 < 0.0) )
  {
    if (t0 < 0.0)
      t0 += 24.0;
    else
      t0 -= 24.0;
  }
                      
  return t0;
}
        
// Work out the Greenwich Siderial Time.
double time_details::gst(double jd)
{
  double s,t,t0,ut;
  double *time_convensional;
  double jd_time_midnight;

  time_convensional = julian_to_date(jd);

  jd_time_midnight = julian_date(time_convensional[0],
                                 time_convensional[1],
                                 time_convensional[2],
                                 0.0,
                                 0.0,
                                 0.0);

  s  = jd_time_midnight - 2451545.0;

  t  = s/36525.0;
  t0 = 6.697374558 + (2400.051336*t) + (0.000025862*(t*t));

  // Change t0 to the range 0-24. 
  while ( (t0 >= 24.0) || (t0 < 0.0) )
  {
    if (t0 < 0.0)
      t0 += 24.0;
    else
      t0 -= 24.0;
  }

  ut = time_convensional[3] + (time_convensional[4]/60.0) + (time_convensional[5]/3600.0);

  ut = ut * 1.002737909;
  t0 += ut;

  // Change t0 to the range 0-24.
  while ( (t0 >= 24.0) || (t0 < 0.0) )
  {
    if (t0 < 0.0)
      t0 += 24.0;
    else
      t0 -= 24.0;
  }

  return t0;
}
        
// Work out the Local Siderial Time.
// Longitude W = +ve, E = -ve
double time_details::lst(int year, int month, int day,int hour,int min,double secs,double time_offset,double longitude)
{
  double lst_value,gst_value,long_angle;

  gst_value = gst(year,month,day,hour,min,secs);           
            
  long_angle = longitude / HR_MOV; 
                       
  if (longitude > 0)          
    lst_value = gst_value - long_angle;
  else  
    lst_value = gst_value + long_angle;        
            
  if (lst_value  > 24)
    lst_value -= 24.0;          
            
  if (lst_value  > 24)
    lst_value -= 24.0;

  if (lst_value < 0)
    lst_value += 24.0;

  return lst_value;
}
                 
// Work out the Local Siderial Time from local time.
// Longitude W = +ve, E = -ve
double time_details::lst(double year, double month, double day,double hour,double min,double secs,double longitude)
{
  double lst_value,gst_value,long_angle;

  gst_value = gst(year,month,day,hour,min,secs);
                                 
  long_angle = longitude / HR_MOV; 
            
  if (longitude > 0)          
    lst_value = gst_value - long_angle;
  else  
    lst_value = gst_value + long_angle;        
            
  if (lst_value  > 24)
    lst_value -= 24.0;

  if (lst_value < 0)
    lst_value += 24.0;

  return lst_value;
}
        
// Work out the Local Siderial Time.
// Input:
// julian_date	= The Julian date
// longitude	= The longitude W is positive, E is negative
//
// Output:
// The local Siderial Time in decimal hours.
double time_details::lst(double julian_date,double longitude)
{
  double lst_value,gst_value,long_angle;

  gst_value = gst(julian_date);

  long_angle = longitude / HR_MOV; 
      
  if (longitude > 0)          
    lst_value = gst_value - long_angle;
  else  
    lst_value = gst_value + long_angle;        
            
  if (lst_value  > 24)
    lst_value -= 24.0;

  if (lst_value < 0)
    lst_value += 24.0;

  return lst_value;
}
        
// Find the hour angle. Section 24 p35
double time_details::hour_angle(double lst,double ra)
{
  double hr; // Holds the hour angle.
        	
  hr = lst - ra;
        	
  if (hr < 0)
    hr += 24;
        		
  return hr;
}
        
// Convert the given lst at a specified longitude to gst.
double time_details::lst_to_gst(double lst,double longitude)
{
  double delta_long,gst=0.0;
        	       	
  // Find the difference in hours between the longitude and a longitude of 0.0.
  delta_long = abs((longitude / HR_MOV));
       		
  // Assuming longitude W is negative. - This is set in JSR 179
  if (longitude < 0.0)
  {
    gst = lst - delta_long;  // Longitude is East - sub.
  }
  else
  {
    gst = lst + delta_long;  // Longitude is West - add.
  }
       		
  // Make sure the result is within the range of 0-24hr.
  if (gst >= 24.0)
    gst -= 24.0;
  else if (gst < 0.0)
    gst += 24.0;
       		
  // Return the result to the rest of the system.
  return gst;
}
        
// Convert GST to UT.
double time_details::gst_to_ut(int year,int month,int day,double gst)
{
  double ut_time,jd,s,t,t0;
        	
  jd = julian_date(year,month,day,0,0,0);
  s  = jd - 2451545.0;
  t  = s/36525.0;
  t0 = 6.697374558 + (2400.051336 * t) + (0.000025862*(t*t));
        	       	        	
  // Change t0 to the range 0-24.
  while ( (t0 >= 24.0) || (t0 < 0.0) )
  {
    if (t0 < 0.0)
      t0 += 24.0;
    else
      t0 -= 24.0;
  }
         	
  ut_time = gst - t0;
         	
  if (abs(0-ut_time) > (1.0/3600)) // If the number is close to zero, treat as zero.
  {
    // Change t0 to the range 0-24.
    while ( (ut_time >= 24.0) || (ut_time < 0.0) )
    {
      if (ut_time < 0.0)
        ut_time += 24.0;
      else
        ut_time -= 24.0;
    }
  }
        	
  ut_time = ut_time * 0.9972695663;
         	     	
  return ut_time;
}
     
// Convert GST to UT.
double time_details::gst_to_ut(double julian_date,double gst)
{
  double ut_time,s,t,t0;
        	
  s  = julian_date - 2451545.0;
  t  = s/36525.0;
  t0 = 6.697374558 + (2400.051336 * t) + (0.000025862*(t*t));
        	
  // Change t0 to the range 0-24.
  while ( (t0 >= 24.0) || (t0 < 0.0) )
  {
    if (t0 < 0.0)
      t0 += 24.0;
    else
      t0 -= 24.0;
  }

  ut_time = gst - t0;
         	
  if (abs(0-ut_time) > (1.0/3600)) // If the number is close to zero, treat as zero.
  {
    // Change t0 to the range 0-24.
    while ( (ut_time >= 24.0) || (ut_time < 0.0) )
    {
      if (ut_time < 0.0)
        ut_time += 24.0;
      else
        ut_time -= 24.0;
    }
  }
         	
  ut_time = ut_time * 0.9972695663;
        	
  return ut_time;
}

// Work out the fraction of a year that a date is.
double time_details::mjd(int day,int month,int year,double hour)
{
  double modifedJulian;			
  double a;
  int b;
			
  a = 10000.0 * year + 100.0 * month + day;
			
  if (month <= 2) 
  {
    month = month + 12;
    year = year-1;
  }
			
  if (a <= 15821004.1)
  {
    b = -2 + (int)floor( ((year+4716)/4) )-1179;
  } else {
    b = (int)floor((year/400))-(int)floor((year/100))+(int)floor((year/4));
  }
			
  a=365.0*year-679004.0;
  modifedJulian = a+b+floor(30.6001*(month+1))+day+hour/24.0;
					
  return modifedJulian;
}

// Work out the number of leap years between 1 and a specified year.
// Algorithum from:
// https://www.geeksforgeeks.org/count-of-leap-years-in-a-given-year-range/
long time_details::number_of_leap_years(long year)
{
  long number_of_leap_years;

  number_of_leap_years = (year / 4) - (year / 100) + (year / 400);

  return number_of_leap_years;
}
	

