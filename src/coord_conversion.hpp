// Header file for the coordinate converstion methods.

class co_ord_conversion
{
private:
    double obliquity_ecliptic(double t);
    double obliquity_ecliptic(int year,int month,int day, int hour, int min,double sec,double offset);
public:
 
    double *equ_to_hor(double julian_date,double ra,double dec,double latitude,double longitude);
    double *hor_to_equ(double altitude, double azimuth, double latitude,double longitude,double time);
    double *ecl_to_hor(double *ecl,
     			     int year, 
     			     int month, 
     			     int day, 
     			     int hour, 
     			     int minute, 
     			     double seconds, 
     			     double time_offset, 
     			     double longitude,
     			     double latitude);
    double *ecl_to_hor(double *ecl,double julian_date,double longitude,double latitude);
    double *ecl_to_equ(double *ecl,int year,int month,int day,int hour,int minute,double sec,double offset);
    double *ecl_to_equ(double *ecl,double julian_date);
     	
    double *helio_ecl_to_geo_ecl(double lambda_o,double beta_o,double dist_o,double lambda_e,double beta_e,double dist_e);
};

