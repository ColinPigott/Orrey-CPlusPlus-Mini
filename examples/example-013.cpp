// This example shows how to use the hor_to_equ method.

// How to build:
//
// g++ -Wall -o example-013.out example-013.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  api_interface api;
  double *output;

  output = api.hor_to_equ(-58.2,  6.2, 51.5, 0.0, 2447487.50000);

  cout << "example-013" << endl;
  cout << "Calculated equ ra         = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated equ dec        = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated hour angle     = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << endl;

  return 0;
}
