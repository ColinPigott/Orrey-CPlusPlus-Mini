// This example shows how to use the lst_to_gst method.

// How to build:
//
// g++ -Wall -o example-009.out example-009.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  // Expected results from:
  // Practical Astronomy for your Calculator p21 0.401453 64W
  api_interface api;
  double output;

  output = api.lst_to_gst(0.401453,64);

  cout << "example-009" << endl;
  cout << "Calculated lst_to_gst     = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  return 0;
}
