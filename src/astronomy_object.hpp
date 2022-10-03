// Header file that specifies the details for an astronomical object.
// An astronomical object is the Sun, Moon and planets.

// An array of structures of the form struct astronomical_object
// The indexes are:
//	0	Sun
//	1	Moon
//	2	Mercury
//	3	Venus
//	4	Earth		
//	5	Mars
//	6	Jupiter
//	7	Saturn
//	8	Uranus
//	9	Neptune
//     10      Comet with a periodic orbit
//     11      Comet with a parabolic orbit
#define OBJECT_ID_SUN		       0
#define OBJECT_ID_MOON		       1
#define OBJECT_ID_MERCURY	       2
#define OBJECT_ID_VENUS	       3
#define OBJECT_ID_EARTH	       4
#define OBJECT_ID_MARS		       5
#define OBJECT_ID_JUPITER	       6
#define OBJECT_ID_SATURN	       7
#define OBJECT_ID_URANUS  	       8
#define OBJECT_ID_NEPTUNE	       9
#define OBJECT_ID_STAR               12

#define MAX_CORE_OBJECT_ID           10
#define MAX_OBJECT_ID                12

struct astronomical_object
{
  double actual_geo_ecliptic_lambda;
  double actual_geo_ecliptic_beta;
  double actual_helio_ecliptic_lambda;
  double actual_helio_ecliptic_beta;  
  double apparent_geo_ecliptic_lambda;
  double apparent_geo_ecliptic_beta;
  double equ_ra;
  double equ_dec;
  double hor_altitude;
  double hor_azimuth;
  double sun_object_distance;
  double earth_object_distance;
  double light_travel_time;
  double phase;
  double magnitude;
  double angular_size;
  double azimuth_rise;
  double azimuth_set;
  double rise_time;
  double transit_time;
  double set_time;
};
