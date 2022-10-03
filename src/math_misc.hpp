// Header file for the math_misc class.

class math_misc
{
public:

    double angle_in_range(double angle);
    double tan_correct_quadrant(double x,double y);
    double to_radians(double degrees);
    double to_degrees(double radians);
    double solveKeplers(double initial_value,double ecc,double error);
	
    double *nutation(double julian_date);
    double *aberration(double sun_lambda,double lambda,double beta);
    double refaction(double latitude,double temp, double pressure,double altitude_angle);
    double *rise_and_set_interpolate(double julian_date,
	                             double longitude,
	                             double latitude,
	                             int object,
	                             double *pos_star,
	                             double *comet_orbit_elements,
	                             double epoch_perihelion_of_Earth);
};
