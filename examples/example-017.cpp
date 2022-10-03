// This example shows how to use the ecl_to_equ (Julian) method.

// How to build:
//
// g++ -Wall -o example-017.out example-017.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

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

  ecl[0] = 139.686111;
  ecl[1] =   4.875278;

  output = api.ecl_to_equ(&ecl[0], 2444238.50000);

  cout << "example-017" << endl;
  cout << "Calculated equ ra         = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated equ dec        = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;

  return 0;
}
