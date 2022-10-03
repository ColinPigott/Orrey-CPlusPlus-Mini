// This example shows how to use the comet_position_periodic (Julian) method.

// How to build:
//
// g++ -Wall -o example-021.out example-021.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include "astronomy_object.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  // Expected results from:
  // Example from
  api_interface api;
  struct astronomical_object object;
  double orbit_params[7];

  // Test the new comet position code.
  // Comet 116P/Wild 4 2022/06/13 22:00 51.5N 0.0W
  //
  //    Field	     Content					         Units			Symbol
  //    =====      =======       				         =====			======
  //	    0        Period 					    (mean Solar years)             T
  // 	    1        Epoch of periastron							   t
  // 	    2	     Longitude of periastron				 	  	           w
  // 	    3        Eccentricity								   e
  // 	    4        Semi-major axis of orbit 		            (arcsec)		           a
  // 	    5        Inclination of orbit 			    (degrees)		           i
  //	    6        Position angle of ascending node 	            (degrees)		           o
  cout << "Comet - periodic - year,months, etc - Comet 116P/Wild 4 2022/06/13 22:00 51.5N 0.0W" << endl;
  orbit_params[0] = 6.5048;
  orbit_params[1] = 2016.029501913;
  orbit_params[2] = 194.414095976; // (peri + node)
  orbit_params[3] = 0.37266174;
  orbit_params[4] = 3.48457297;
  orbit_params[5] = 3.60741312;
  orbit_params[6] = 21.014489640779;

  object = api.comet_position_perodic(&orbit_params[0],
                                      2459744.41667,
                                      0.0,
                                      51.5,
                                      5.60,
                                      5.36);

  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "example-021.cpp" << endl;
  cout << "Comet periodic actual_geo_ecliptic_lambda     = " << object.actual_geo_ecliptic_lambda << endl;
  cout << "Comet periodic actual geo ecliptic beta       = " << object.actual_geo_ecliptic_beta << endl;
  cout << "Comet periodic actual_helio_ecliptic_lambda   = " << object.actual_helio_ecliptic_lambda << endl;
  cout << "Comet periodic actual helio ecliptic beta     = " << object.actual_helio_ecliptic_beta << endl;
  cout << "Comet periodic RA                             = " << object.equ_ra << endl;
  cout << "Comet periodic DEC                            = " << object.equ_dec << endl;
  cout << "Comet periodic hor_altitude                   = " << object.hor_altitude << endl;
  cout << "Comet periodic hor_azimuth                    = " << object.hor_azimuth << endl;
  cout << "Comet periodic Sun-Earth distance             = " << object.earth_object_distance  << endl;
  cout << "Comet periodic angular size                   = " << object.angular_size << endl;
  cout << "Comet periodic light travel time              = " << object.light_travel_time << endl;
  cout << "Comet periodic Sun-object distance            = " << object.sun_object_distance << endl;
  cout << "Comet periodic phase                          = " << object.phase << endl;
  cout << "Comet periodic magnitude                      = " << object.magnitude << endl;
  cout << "Comet periodic azimuth rise                   = " << object.azimuth_rise << endl;
  cout << "Comet periodic azimuth set                    = " << object.azimuth_set << endl;
  cout << "Comet periodic rise time                      = " << object.rise_time << endl;
  cout << "Comet periodic transit time                   = " << object.transit_time << endl;
  cout << "Comet periodic set time                       = " << object.set_time << endl;
  cout << endl;

  return 0;
}
