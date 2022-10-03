// Header file for the comet methods.
class comet_details
{
public:

  double *comet_position_perodic(double *comet_orbit_elements,
                                 int year, 
                                 int month, 
                                 int day,
                                 int hour,
                                 int min,
                                 double secs,
                                 double time_offset);
  double *comet_position_perodic(double *comet_orbit_elements,double julian_date);
  double *comet_position_parabolic(double *comet_orbit_elements,
				    int year, 
				    int month, 
				    int day,
				    int hour,
				    int min,
				    double secs,
				    double time_offset,
				    double epoch_perihelion_of_Earth);
  double* comet_position_parabolic(double *comet_orbit_elements,
                                   double julian_date,
                                   double epoch_perihelion_of_Earth); 
  struct astronomical_object comet_values(double *output_value,
                                          double *comet_orbit_elements,
                                          double julian_date,
                                          double longitude,
                                          double latitude,
                                          bool orbit_type,
                                          double epoch_perihelion_of_Earth,
                                          double absolute_mag,
                                          double slope_param);
private:
  double *comet_rise_and_set(double julian_date,
                             double longitude,
                             double latitude,
                             int orbit_type,
                             double *comet_orbit_elements,
                             double epoch_perihelion_of_Earth);
  double *interation_position(double julian_date,
  			       double longitude,
  			       double latitude,
  			       bool selector,
  			       double *comet_orbit_elements,
  			       double epoch_perihelion_of_Earth);
  double *find_maxima(double a,
                      double b,
                      double c,
                      double longitude,
 		      double latitude,
  		      bool selector,
  		      double *comet_orbit_elements,
  		      double epoch_perihelion_of_Earth);	       
  double *interation(double s,
		      double t,
		      double e,
		      int m,
		      bool selector,
		      double longitude,
		      double latitude,
		      double *comet_orbit_elements,
		      double epoch_perihelion_of_Earth);
  double visual_magnitude(double absolute_mag,
                          double slope_param,
                          double julian_date,
                          double ds,
                          double de);
};
