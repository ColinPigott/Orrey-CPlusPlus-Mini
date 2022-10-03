// This example shows how to use the equ_to_hor method.

// How to build:
//
// g++ -Wall -o example-012.out example-012.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{ 
  // Expected results from:
  // Example from Practical Astronomy for your Calculator p35-36
  // Convert RA 18hr 32m 21s DEC = +23 13' 10" to horizontal co-ords at 52N 64W on 1980 Apr 22 14h 36m 51.67s UT 
  api_interface api;
  double *output;

  output = api.equ_to_hor(2444352.1089313 ,18.539167, 23.219444, 52, -64.0);

  // These lines are used for diagnostic reasons.
  cout << "Calculated hor azimuth    = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated hor alitude    = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;

  return 0;
}
