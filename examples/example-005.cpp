// This example shows how to use the gst (no-Julian) method.

// How to build:
//
// g++ -Wall -o example-005.out example-005.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  // Expected results from:
  // Practical Astronomy with your Calculator p17
  api_interface api;
  double output;

  output = api.gst(1980, 4, 22, 14, 36, 51.67);

  // These lines are used for diagnostic reasons.
  cout << "example-005" << endl;
  cout << "Calculated gst            = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  return 0;
}
