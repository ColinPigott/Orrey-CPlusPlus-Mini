// Header file for the time_details functions.
class time_details
{
public:

  double decimal_year(int year, int month, int day,int hour,int min,double secs,double time_offset);
  double decimal_year(double julian_date);
  double julian_date(int year,int month,int day,int hour,int min,double sec);
  double julian_date(double year,double month,double day,double hour,double min,double sec);
  double *julian_to_date(double julian_date);
  double gst(int year, int month, int day, int hour, int min, double seconds);
  double gst(double year, double month, double day, double hour, double min, double seconds);
  double gst(double jd);
  double lst(int year, int month, int day,int hour,int min,double secs,double time_offset,double longitude);
  double lst(double year, double month, double day,double hour,double min,double secs,double longitude);
  double lst(double julian_date,double longitude);
  double hour_angle(double lst,double ra);
  double lst_to_gst(double lst,double longitude);
  double gst_to_ut(int year,int month,int day,double gst);
  double gst_to_ut(double julian_date,double gst);
  double mjd(int day,int month,int year,double hour);
  long number_of_leap_years(long year);
};

