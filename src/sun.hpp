// The header file for the sun class.

class sun
{
private:
  const double e = 0.016713;		 	// eccentricity of orbit.
  const double ro =1.495985e8;	 	// Sun semi-major axis
  const double thetao = 0.533128;	 	// angular size at r = semi-major axis)
  const double epsilon_g = 279.403303;	// ecliptic longitude at epoch 1990.0
  const double omega_g = 282.768422;		// ecliptic longitude of perigee

  double *sun_distance_size_light_time(double v);
public:
   
  double *sun_details(double julian);
};
