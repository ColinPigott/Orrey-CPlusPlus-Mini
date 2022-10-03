// This example shows how to use the gst (Julian) method.

// How to build:
//
// g++ -Wall -o example-006.out example-006.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  api_interface api;
  double output;

  output = api.gst(2444352.10892);

  cout << "example-006" << endl;
  cout << "Calculated gst            = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  return 0;
}
