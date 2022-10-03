// This example shows how to use the double_star method.

// How to build:
//
// g++ -Wall -o example-001.out example-001.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

const int DISPLAY_PRECISION = 15;

int main(void)
{
  // Expected results from:
  // Practical Astronomy with your Calculator, 3rd Edition p133
  api_interface api;
  double *output;
		 
  output = api.double_star(1980, 1, 1, 0, 0, 0.0, 0.0, 41.623, 1934.008, 0.907, 0.2763, 59.025, 219.907, 23.717);
									
  // Display the output.
  cout << "Example-001.cpp" << endl;
  cout << "Calculated position angle = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated separation     = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;
  
  return 0;
}
