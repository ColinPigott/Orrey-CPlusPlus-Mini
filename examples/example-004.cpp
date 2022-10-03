// This example shows how to use the julian_to_date method.

// How to build:
//
// g++ -Wall -o example-004.out example-004.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  // Expected results from:
  // Practical Astronomy with your Calculator p8
  api_interface api;
  double *output;

  output = api.julian_to_date(2446113.75);

  // These lines are used for diagnostic reasons.
  cout << "example-004" << endl;
  cout << "Calculated output[0]      = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated output[1]      = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated output[2]      = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << "Calculated output[3]      = " << setprecision(DISPLAY_PRECISION) << output[3] << endl;
  cout << "Calculated output[4]      = " << setprecision(DISPLAY_PRECISION) << output[4] << endl;
  cout << "Calculated output[5]      = " << setprecision(DISPLAY_PRECISION) << output[5] << endl;
  cout << endl;

  return 0;
}
