// This example shows how to use the helio_ecl_to_geo_ecl method.

// How to build:
//
// g++ -Wall -o example-018.out example-018.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.hpp"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  api_interface api;
  double *output;

  // The position is for Jupiter on 22nd Nov 1988 at 00:00:00
  // Convert the geo ecl co-ords for the object and the origin of the new co-ord system(Sun) and convert to the helio co-ords.
  //                                           geo co-ord Jupiter                    geo co-ord Sun
  //                                :--------------------------------------:  :--------------------------------------:
  output = api.helio_ecl_to_geo_ecl(61.2007462, -1.0319223, 4.03398255097488, 239.9074184, 0.0001560, 0.98758155072300);

  // These lines are used for diagnostic reasons.
  cout << "example-018" << endl;
  cout << "Calculated helio lambda   = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated helio beta     = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated helio distance = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << endl;

  return 0;
}
