// This example shows how to use the comet_position_parabolic (Julian) method.

// How to build:
//
// g++ -Wall -o example-023.out example-023.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include "astronomy_object.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  api_interface api;
  struct astronomical_object object;
  double parabolic_orbit_params[5];

  // Comet C/2017 K2 (PANSTARRS) 2022/06/14 22:00
  parabolic_orbit_params[0] = 2459933.442190267776;	// 2022-Dec-19.94219027
  parabolic_orbit_params[1] = 1.799073955184896;
  parabolic_orbit_params[2] = 87.54383914154957;
  parabolic_orbit_params[3] = 236.1676054883491;
  parabolic_orbit_params[4] = 88.26338356498053;

  // Perihelion of Earth (closest distance between Earth and Sun) in that epoch:
  // 2022 Jan 4 06:52 (Julian date = 2459583.78611)

  object = api.comet_position_parabolic(&parabolic_orbit_params[0],
                                        2459745.41667,
                                        2459583.78611,
                                        0.0,
                                        51.5,
                                        4.80,
                                        2.48);

  cout << setprecision(DISPLAY_PRECISION);
  cout << "example-023" << endl;
  cout << "Comet parabolic actual_geo_ecliptic_lambda     = " << object.actual_geo_ecliptic_lambda << endl;
  cout << "Comet parabolic actual geo ecliptic beta       = " << object.actual_geo_ecliptic_beta << endl;
  cout << "Comet parabolic actual_helio_ecliptic_lambda   = " << object.actual_helio_ecliptic_lambda << endl;
  cout << "Comet parabolic actual helio ecliptic beta     = " << object.actual_helio_ecliptic_beta << endl;
  cout << "Comet parabolic RA                             = " << object.equ_ra << endl;
  cout << "Comet parabolic DEC                            = " << object.equ_dec << endl;
  cout << "Comet parabolic hor_altitude                   = " << object.hor_altitude << endl;
  cout << "Comet parabolic hor_azimuth                    = " << object.hor_azimuth << endl;
  cout << "Comet parabolic Sun-Earth distance             = " << object.earth_object_distance  << endl;
  cout << "Comet parabolic angular size                   = " << object.angular_size << endl;
  cout << "Comet parabolic light travel time              = " << object.light_travel_time << endl;
  cout << "Comet parabolic Sun-object distance            = " << object.sun_object_distance << endl;
  cout << "Comet parabolic phase                          = " << object.phase << endl;
  cout << "Comet parabolic magnitude                      = " << object.magnitude << endl;
  cout << "Comet parabolic azimuth rise                   = " << object.azimuth_rise << endl;
  cout << "Comet parabolic azimuth set                    = " << object.azimuth_set << endl;
  cout << "Comet parabolic rise time                      = " << object.rise_time << endl;
  cout << "Comet parabolic transit time                   = " << object.transit_time << endl;
  cout << "Comet parabolic set time                       = " << object.set_time << endl;
  cout << endl;

  return 0;
}
