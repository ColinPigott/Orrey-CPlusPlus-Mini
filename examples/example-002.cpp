// This example shows how to use the star_rise_set method.

// How to build:
//
// g++ -Wall -o example-002.out example-002.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  // Expected results from:
  // Practical Astronomy with your Calculator, 3rd edition p52-55
  api_interface api;
  double equ_co_ords[2];
  double *output;

  // Output[0] - Azimuth of the selected object to rise.
  // Output[1] - Azimuth of the selected object to set.
  // Output[2] - Time of the object rising (Julian date).
  // Output[3] - Time of the object setting (Julian date).
  // Output[4] - Time of when the object is in transit (Julian date).

  equ_co_ords[0] = 23.655556; // RA
  equ_co_ords[1] = 21.700000; // Dec

  output = api.star_rise_set(2444475.50000,64.0,30.0,&equ_co_ords[0]);

  cout << "TestJunit004_001_000_0000" << endl;
  cout << "Calculated azimuth rise   = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated azimuth set    = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated time rise      = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << "Calculated time set       = " << setprecision(DISPLAY_PRECISION) << output[3] << endl;
  cout << "Calculated time transit   = " << setprecision(DISPLAY_PRECISION) << output[4] << endl;
  cout << endl;

  return 0;
}
