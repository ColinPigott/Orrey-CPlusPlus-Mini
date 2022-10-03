// This example shows how to use the ecl_to_hor (Julian) method.

// How to build:
//
// g++ -Wall -o example-015.out example-015.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  api_interface api;
  double ecl[2];
  double *output;

  ecl[0] = 241.0969;
  ecl[1] =   0.8277;

  output = api.ecl_to_hor(&ecl[0], 2447487.5, 0.0, 51.5);

  // These lines are used for diagnostic reasons.
  cout << "example-015" << endl;
  cout << "Calculated hor azimuth    = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated hor alitude    = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;

  return 0;
}
