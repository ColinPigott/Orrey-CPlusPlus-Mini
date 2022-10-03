// This example shows how to use the gst_to_ut (Julian) method.

// How to build:
//
// g++ -Wall -o example-011.out example-011.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  // Expected results from:
  // Practical Astronomy for Your Calculator p18 1980 4 22 4.668119
  api_interface api;
  double output;

  output = api.gst_to_ut(2444351.50000,4.668119);

  // These lines are used for diagnostic reasons.
  cout << "example-011" << endl;
  cout << "Calculated gst_to_ust     = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  return 0;
}
