// This method shows how to use the object_details method.

// How to build:
//
// g++ -Wall -o example-024.out example-024.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include "astronomy_object.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  api_interface api;
  struct astronomical_object *objects;
  int loop;

  // The position of the objects in the Solar system on 22nd Nov 1988 00:00:00 and from central London (UK).
  objects = api.object_details(2447487.50000,0.0,51.5);

  cout << setprecision(DISPLAY_PRECISION) << endl;
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

  return 0;
}

