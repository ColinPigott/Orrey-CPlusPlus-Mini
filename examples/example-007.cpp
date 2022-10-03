// This example shows how to use the lst (non-Julian) method.

// How to build:
//
// g++ -Wall -o example-007.out example-007.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  // Expected results from:
  // Practical Astronomy for your Calculator p20
  api_interface api;
  double output;

  output = api.lst(1980, 4, 22, 14, 36, 51.67, 0.0, 64);

  cout << "example007" << endl;
  cout << "Calculated lst            = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  return 0;
}

