// Example of a calling application that uses the Orrey mini library.
// To build:
//	g++ -Wall Application.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include <iostream>
#include <iomanip>
#include "api_interface.h"
#include "astronomy_object.h"

using namespace std;

int main ()
{
  api_interface api;

  double *answer;
  double orbit_params[7];
  double parabolic_orbit_params[5];
  double star_pos[2];
  struct astronomical_object *objects;
  struct astronomical_object comet_position;
  int loop;

  cout << setprecision(15) << fixed;

  answer = api.double_star(1980, 1, 1, 0, 0, 0.0, 0.0, 41.623, 1934.008, 0.907, 0.2763, 59.025, 219.907, 23.717);

  cout << "Binary star" << endl;
  cout << "answer = " << answer[0] << " " << answer[1] << endl;
  cout << endl;

  // Rise and set of a star.
  star_pos[0] = 23.655556; // RA
  star_pos[1] = 21.700000; // Dec

  answer = api.star_rise_set(2444475.50000,0.0,30.0,&star_pos[0]);

  cout << "Star rise/set" << endl;
  cout << "answer = " << answer[0] << " " << answer[1] << endl;
  cout << "         " << answer[2] << " " << answer[3] << " " << answer[4] << endl;
  cout << endl;

  objects = api.object_details(2447487.50000,0.0,51.5);	// Details for 22nd Nov 1988 00:00:00

  cout << "Solar system object details:" << endl;
  cout << "Sun actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_SUN].actual_geo_ecliptic_lambda << endl;
  cout << "Sun actual geo ecliptic beta       = " << objects[OBJECT_ID_SUN].actual_geo_ecliptic_beta << endl;
  cout << "Sun actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_SUN].actual_helio_ecliptic_lambda << endl;
  cout << "Sun actual helio ecliptic beta     = " << objects[OBJECT_ID_SUN].actual_helio_ecliptic_beta << endl;
  cout << "Sun RA                             = " << objects[OBJECT_ID_SUN].equ_ra << endl;
  cout << "Sun DEC                            = " << objects[OBJECT_ID_SUN].equ_dec << endl;
  cout << "Sun hor_altitude                   = " << objects[OBJECT_ID_SUN].hor_altitude << endl;
  cout << "Sun hor_azimuth                    = " << objects[OBJECT_ID_SUN].hor_azimuth << endl;
  cout << "Sun Sun-Earth distance             = " << objects[OBJECT_ID_SUN].earth_object_distance  << endl;
  cout << "Sun angular size                   = " << objects[OBJECT_ID_SUN].angular_size << endl;
  cout << "Sun light travel time              = " << objects[OBJECT_ID_SUN].light_travel_time << endl;
  cout << "Sun Sun-object distance            = " << objects[OBJECT_ID_SUN].sun_object_distance << endl;
  cout << "Sun phase                          = " << objects[OBJECT_ID_SUN].phase << endl;
  cout << "Sun magnitude                      = " << objects[OBJECT_ID_SUN].magnitude << endl;
  cout << "Sun azimuth rise                   = " << objects[OBJECT_ID_SUN].azimuth_rise << endl;
  cout << "Sun azimuth set                    = " << objects[OBJECT_ID_SUN].azimuth_set << endl;
  cout << "Sun rise time                      = " << objects[OBJECT_ID_SUN].rise_time << endl;
  cout << "Sun transit time                   = " << objects[OBJECT_ID_SUN].transit_time << endl;
  cout << "Sun set time                       = " << objects[OBJECT_ID_SUN].set_time << endl;

  cout << endl;
  cout << "Moon actual_geo_ecliptic_lambda    = " << objects[OBJECT_ID_MOON].actual_geo_ecliptic_lambda << endl;
  cout << "Moon actual geo ecliptic beta      = " << objects[OBJECT_ID_MOON].actual_geo_ecliptic_beta << endl;
  cout << "Moon actual_helio_ecliptic_lambda  = " << objects[OBJECT_ID_MOON].actual_helio_ecliptic_lambda << endl;
  cout << "Moon actual helio ecliptic beta    = " << objects[OBJECT_ID_MOON].actual_helio_ecliptic_beta << endl;
  cout << "Moon RA                            = " << objects[OBJECT_ID_MOON].equ_ra << endl;
  cout << "Moon DEC                           = " << objects[OBJECT_ID_MOON].equ_dec << endl;
  cout << "Moon hor_altitude                  = " << objects[OBJECT_ID_MOON].hor_altitude << endl;
  cout << "Moon hor_azimuth                   = " << objects[OBJECT_ID_MOON].hor_azimuth << endl;
  cout << "Moon Sun-Moon distance             = " << objects[OBJECT_ID_MOON].earth_object_distance  << endl;
  cout << "Moon angular size                  = " << objects[OBJECT_ID_MOON].angular_size << endl;
  cout << "Moon light travel time             = " << objects[OBJECT_ID_MOON].light_travel_time << endl;
  cout << "Moon Sun-object distance           = " << objects[OBJECT_ID_MOON].sun_object_distance << endl;
  cout << "Moon phase                         = " << objects[OBJECT_ID_MOON].phase << endl;
  cout << "Moon magnitude                     = " << objects[OBJECT_ID_MOON].magnitude << endl;
  cout << "Moon azimuth rise                  = " << objects[OBJECT_ID_MOON].azimuth_rise << endl;
  cout << "Moon azimuth set                   = " << objects[OBJECT_ID_MOON].azimuth_set << endl;
  cout << "Moon rise time                     = " << objects[OBJECT_ID_MOON].rise_time << endl;
  cout << "Moon transit time                  = " << objects[OBJECT_ID_MOON].transit_time << endl;
  cout << "Moon set time                      = " << objects[OBJECT_ID_MOON].set_time << endl;
  cout << endl;

  for (loop = OBJECT_ID_MERCURY;loop < MAX_CORE_OBJECT_ID;loop++)
  {
    cout << "Object Id = " << loop << endl;
    cout << "Actual_geo_ecliptic_lambda         = " << objects[loop].actual_geo_ecliptic_lambda << endl;
    cout << "Actual geo ecliptic beta           = " << objects[loop].actual_geo_ecliptic_beta << endl;
    cout << "Actual_helio_ecliptic_lambda       = " << objects[loop].actual_helio_ecliptic_lambda << endl;
    cout << "Actual helio ecliptic beta         = " << objects[loop].actual_helio_ecliptic_beta << endl;
    cout << "RA                                 = " << objects[loop].equ_ra << endl;
    cout << "DEC                                = " << objects[loop].equ_dec << endl;
    cout << "hor_altitude                       = " << objects[loop].hor_altitude << endl;
    cout << "hor_azimuth                        = " << objects[loop].hor_azimuth << endl;
    cout << "Earth-Object distance              = " << objects[loop].earth_object_distance  << endl;
    cout << "Sun-Object distance                = " << objects[loop].sun_object_distance  << endl;
    cout << "Angular size                       = " << objects[loop].angular_size << endl;
    cout << "Light travel time                  = " << objects[loop].light_travel_time << endl;
    cout << "Phase                              = " << objects[loop].phase << endl;
    cout << "Magnitude                          = " << objects[loop].magnitude << endl;
    cout << "Azimuth rise                       = " << objects[loop].azimuth_rise << endl;
    cout << "Azimuth set                        = " << objects[loop].azimuth_set << endl;
    cout << "Rise time                          = " << objects[loop].rise_time << endl;
    cout << "Transit time                       = " << objects[loop].transit_time << endl;
    cout << "Set time                           = " << objects[loop].set_time << endl;
    cout << endl;
  }


  // Test the new comet position code.
  // Comet 116P/Wild 4 2022/06/13 22:00 51.5N 0.0W
  //
  //    Field	     Content					         Units		Symbol
  //    =====      =======       				         =====		======
  //	    0        Period 					     (mean Solar years)    T
  // 	    1        Epoch of periastron					           t
  // 	    2	     Longitude of periastron				 	  	   w
  // 	    3        Eccentricity							   e
  // 	    4        Semi-major axis of orbit 		                (arcsec)	   a
  // 	    5        Inclination of orbit 			        (degrees)          i
  //	    6        Position angle of ascending node 	                (degrees)	   o
  cout << "Comet - periodic - year,months, etc - Comet 116P/Wild 4 2022/06/13 22:00 51.5N 0.0W" << endl;
  orbit_params[0] = 6.5048;
  orbit_params[1] = 2016.029501913;
  orbit_params[2] = 194.414095976; // (peri + node)
  orbit_params[3] = 0.37266174;
  orbit_params[4] = 3.48457297;
  orbit_params[5] = 3.60741312;
  orbit_params[6] = 21.014489640779;

  comet_position = api.comet_position_perodic(&orbit_params[0],
                                      2022,
                                      6,
                                      13,
                                      22,
                                      0,
                                      0.0,
                                      0.0,
                                      0.0,
                                      51.5,
                                      5.60,
                                      5.36);

  cout << "New comet position code- periodic" << endl;
  cout << "Actual_geo_ecliptic_lambda         = " << comet_position.actual_geo_ecliptic_lambda << endl;
  cout << "Actual geo ecliptic beta           = " << comet_position.actual_geo_ecliptic_beta << endl;
  cout << "Actual_helio_ecliptic_lambda       = " << comet_position.actual_helio_ecliptic_lambda << endl;
  cout << "Actual helio ecliptic beta         = " << comet_position.actual_helio_ecliptic_beta << endl;
  cout << "RA                                 = " << comet_position.equ_ra << endl;
  cout << "DEC                                = " << comet_position.equ_dec << endl;
  cout << "hor_altitude                       = " << comet_position.hor_altitude << endl;
  cout << "hor_azimuth                        = " << comet_position.hor_azimuth << endl;
  cout << "Earth-Object distance              = " << comet_position.earth_object_distance  << endl;
  cout << "Sun-Object distance                = " << comet_position.sun_object_distance  << endl;
  cout << "Angular size                       = " << comet_position.angular_size << endl;
  cout << "Light travel time                  = " << comet_position.light_travel_time << endl;
  cout << "Phase                              = " << comet_position.phase << endl;
  cout << "Magnitude                          = " << comet_position.magnitude << endl;
  cout << "Azimuth rise                       = " << comet_position.azimuth_rise << endl;
  cout << "Azimuth set                        = " << comet_position.azimuth_set << endl;
  cout << "Rise time                          = " << comet_position.rise_time << endl;
  cout << "Transit time                       = " << comet_position.transit_time << endl;
  cout << "Set time                           = " << comet_position.set_time << endl;
  cout << endl;

  // Comet C/2017 K2 (PANSTARRS) 2022/06/14 22:00
  parabolic_orbit_params[0] = 2459933.442190267776;	// 2022-Dec-19.94219027
  parabolic_orbit_params[1] = 1.799073955184896;
  parabolic_orbit_params[2] = 87.54383914154957;
  parabolic_orbit_params[3] = 236.1676054883491;
  parabolic_orbit_params[4] = 88.26338356498053;

  // Perihelion of Earth (closest distanceobjects = api.object_details(2447487.50000,0.0,51.5); between Earth and Sun) in that epoch:
  // 2022 Jan 4 06:52 (Julian date = 2459583.78611)

  comet_position = api.comet_position_parabolic(&parabolic_orbit_params[0],
                                                 2022,
                                                 6,
                                                 14,
                                                 22,
                                                 0,
                                                 0.0,
                                                 0.0,
                                                 2459583.78611,
                                                 0.0,
                                                 51.5,
                                                 4.80,
                                                 2.48);

  cout << "New comet position code - parabolic Comet C/2017 K2 (PANSTARRS) 2022/06/14 22:00" << endl;
  cout << "Actual_geo_ecliptic_lambda         = " << comet_position.actual_geo_ecliptic_lambda << endl;
  cout << "Actual geo ecliptic beta           = " << comet_position.actual_geo_ecliptic_beta << endl;
  cout << "Actual_helio_ecliptic_lambda       = " << comet_position.actual_helio_ecliptic_lambda << endl;
  cout << "Actual helio ecliptic beta         = " << comet_position.actual_helio_ecliptic_beta << endl;
  cout << "RA                                 = " << comet_position.equ_ra << endl;
  cout << "DEC                                = " << comet_position.equ_dec << endl;
  cout << "hor_altitude                       = " << comet_position.hor_altitude << endl;
  cout << "hor_azimuth                        = " << comet_position.hor_azimuth << endl;
  cout << "Earth-Object distance              = " << comet_position.earth_object_distance  << endl;
  cout << "Sun-Object distance                = " << comet_position.sun_object_distance  << endl;
  cout << "Angular size                       = " << comet_position.angular_size << endl;
  cout << "Light travel time                  = " << comet_position.light_travel_time << endl;
  cout << "Phase                              = " << comet_position.phase << endl;
  cout << "Magnitude                          = " << comet_position.magnitude << endl;
  cout << "Azimuth rise                       = " << comet_position.azimuth_rise << endl;
  cout << "Azimuth set                        = " << comet_position.azimuth_set << endl;
  cout << "Rise time                          = " << comet_position.rise_time << endl;
  cout << "Transit time                       = " << comet_position.transit_time << endl;
  cout << "Set time                           = " << comet_position.set_time << endl;
  cout << endl;

  return 0;
}




