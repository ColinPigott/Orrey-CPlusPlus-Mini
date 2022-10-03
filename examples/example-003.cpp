// This example shows how to use the julian_date method.

// How to build:
//
// g++ -Wall -o example-003.out example-003.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  api_interface api;
  double output;

  output = api.julian_date(1992,12,16,0,0,0.0);

  cout << "example-003" << endl;
  cout << "Calculated Julian date    = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  return 0;
}
