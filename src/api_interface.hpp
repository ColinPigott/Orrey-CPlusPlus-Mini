// Impliement a facade pattern.

class api_interface
{
public:

  // Binary star methods.
  double* double_star(int year,
  		       int month,
  		       int day,
  		       int hour,
  		       int min,
  		       double secs,
  		       double time_offset,
  		       double period,
  		       double periastron,
  		       double semi_major,
  		       double e,
  		       double i,
  		       double w,
  		       double pa) const;
  		       
  // Star rise/set
  double *star_rise_set(double julian_date,double longitude,double latitude,double *star_eq_coords) const;
  
  // Time methods.
  double julian_date(int year,int month,int day,int hour,int min,double sec) const;
  double *julian_to_date(double julian_date) const;
  double gst(int year, int month, int day, int hour, int min, double seconds) const;
  double gst(double jd) const;
  double lst(int year, int month, int day,int hour,int min,double secs,double time_offset,double longitude) const;
  double lst(double julian_date,double longitude) const;
  double lst_to_gst(double lst,double longitude) const;
  double gst_to_ut(int year,int month,int day,double gst) const;
  double gst_to_ut(double julian_date,double gst) const;
  
  // co-ord methods.
  double *equ_to_hor(double julian_date,double ra,double dec,double latitude,double longitude) const;
  double *hor_to_equ(double altitude, double azimuth, double latitude,double longitude,double time) const;
  double *ecl_to_hor(double *ecl,
  		     int year, 
  		     int month, 
  		     int day, 
  		     int hour, 
  		     int minute, 
  		     double seconds, 
  		     double time_offset, 
  		     double longitude,
  		     double latitude) const;
  double *ecl_to_hor(double *ecl,double julian_date,double longitude,double latitude) const;
  double *ecl_to_equ(double *ecl,int year,int month,int day,int hour,int minute,double sec,double offset) const;
  double *ecl_to_equ(double *ecl,double julian_date) const; 
  double *geo_ecl_to_helio_ecl(double *geo_ecl) const;
  double *helio_ecl_to_geo_ecl(double lambda_o,double beta_o,double dist_o,double lambda_e,double beta_e,double dist_e) const;
  
  // Comet methods.
  struct astronomical_object comet_position_perodic(double *comet_orbit_elements,
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
                                                    double slope_param) const;
  struct astronomical_object comet_position_perodic(double *comet_orbit_elements,
                                                    double julian_date,
                                                    double longitude,
                                                    double latitude,
                                                    double absolute_mag,
                                                    double slope_param) const; 
  struct astronomical_object comet_position_parabolic(double *comet_orbit_elements,
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
                                                      double slope_param) const;
  struct astronomical_object comet_position_parabolic(double *comet_orbit_elements,
  							double julian_date,
                                                      double epoch_perihelion_of_Earth,
                                                      double longitude,
                                                      double latitude,
                                                      double absolute_mag,
                                                      double slope_param) const ;
    
  // Solar system objects
  struct astronomical_object *object_details(const double julian_date,const double longitude,const double latitude) const;  
};


