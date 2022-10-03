// Header file for the Moon class

class moon
{
private:
  const double lo = 318.351648;		        // Moon's mean longitude at the epoch (degrees).
  const double po = 36.340410;		        // mean longitude of tgew perigee at the epoch (degrees).
  const double no = 318.510107;		        // mean longitude of the node at the epoch (degrees).
  const double i  = 5.145396;			// inclination of the Moon's orbit.
  const double e  = 0.054900;			// eccentricity of Moon orbit
  const double a  = 384401;			// semi-major axis of Moon's orbit (Km).
  const double moon_angular_dia = 0.5181;	// Moon's angular size at distance a from Earth (degrees).
  
  double *moon_distance_size_light_travel(double moon_corrected_anomaly,double equation_centre);
  double moon_phase(double lambda,double true_orbital_longitude);
public:
  
  double *moon_details(double julian_date);
};
