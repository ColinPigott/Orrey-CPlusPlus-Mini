// Header file for the planets class.

// #defines for internat use with this class.
#define PLANET_INTERNAL_MIN_ID	0
#define PLANET_INTERNAL_MAX_ID	8
#define PLANET_INTERNAL_EARTH_ID	2

struct planet_orbit_params
{
  double period;
  double longitude_at_epoch;
  double longitude_of_perihelion;
  double eccentricity;
  double semi_major_axis;
  double inclination;
  double longitude_of_ascending_node;
  double angular_diameter_at_1AU;
  double visual_mag_at_1AU;
};


class planets
{
private:
  const planet_orbit_params planet_constants[8] =
  { //  Period     longitide  longitude     e      semi-major      i    longitude    angular  mag
    //            at epc      of the               axis of              of the       diameter
    //                        perihelion           the orbit            ascending
    //                                                                  node
    {  0.240852,  60.750646,  77.299833, 0.205633, 0.387099,  7.004540,  48.212740,   6.74, -0.42},	// Mercury
    {  0.615211,  88.455855, 131.430236, 0.006778, 0.723332,  3.394535,  76.589820,  16.92, -4.40},	// Venus
    {  1.00004,   99.403308, 102.768413, 0.016713, 1.00000,   9.999999,  99.999999,  99.99, -9.99},	// Earth (N/A = all 9's
    {  1.880932, 240.739474, 335.874939, 0.093396, 1.523688,  1.849736,  49.480308,   9.36, -1.52},	// Mars
    { 11.863075,  90.638185,  14.170747, 0.048482, 5.202561,  1.303613, 100.353142, 196.74, -9.40},	// Jupiter
    { 29.471362, 287.690033,  92.861407, 0.055581, 9.554747,  2.488980, 113.576139, 165.60, -8.88},	// Saturn
    { 84.039492, 271.063148, 172.884833, 0.046321, 19.21814,  0.773059,  73.926961,  65.80, -7.19},	// Uranus
    {164.79246,  282.349556,  48.009758, 0.009003, 30.109570, 1.770646, 131.670599,  62.20, -6.87}	// Neptune
  };
   
  //double *planet_position_values(double julian_date, int planet_id); 
  double *planet_distance_size_light_travel(double r, double R,double l,double L,int planet_id);
  double planet_phase(double lambda,double true_orbital_longitude);
  double planet_magnitude(double r,double p,double phase,int planet_id);

public:
   
  double *planet_position_values(double julian_date, int planet_id);  
  double *planet_details(double julian_date, int planet_id);
  struct astronomical_object *planet_all_details(double julian_date);
};
