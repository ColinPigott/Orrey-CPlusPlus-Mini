// This example shows how to use to the lst (Julian) method.

// How to build:
//
// g++ -Wall -o example-008.out example-008.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

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

  output = api.lst(2444352.10892, 64);

  cout << "example-008" << endl;
  cout << "Calculated lst            = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  return 0;
}
