// This example shows how to use the helio_ecl_to_geo_ecl method.

// How to build:
//
// g++ -Wall -o example-018.out example-018.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

#include "api_interface.h"
#include <iostream>
#include <iomanip>

const int DISPLAY_PRECISION = 15;

using namespace std;

int main(void)
{
  api_interface api;
  double *output;

  // Data for 2024/01/01 00:00:00 UT
  //	object		longitude     latitiude  	Distance(AU)
  // ===========        =========     =========  	============
  // Sun (Geo)		280.038992	 0.000162	0.9833183
  // Earth (Helio)	100.04627	-0.00016	0.9833183
  //
  // Jupiter (Helio)	 45.83832	-1.06566	4.9848972
  // Jupiter (Geo)	 35.582395	-1.185480	4.4814715
  //
  // The source:
  // https://eco.mtk.nao.ac.jp/koyomi/cande/index.html.en
  
  
  // Test Geo co-ords to Helio
  // Convert the geo ecl co-ords for the object and the origin of the new co-ord system(Sun) and convert to the helio co-ords.
  //                                         geo co-ord Jupiter            geo co-ord Sun 
  //                                :-----------------------------:  :-----------------------------:
  output = api.helio_ecl_to_geo_ecl(35.582395, -1.185480, 4.4814715, 280.038992, 0.000162, 0.9833183);	

  // These lines are used for diagnostic reasons.
  cout << "Output (Geo to Helio):" << endl;
  cout << "Calculated helio lambda   = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated helio beta     = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated helio distance = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << endl;

  // Test Helio co-ords to Geo
  // Convert the helio ecl co-ords for the object and the origin of the new co-ord system(Sun) and convert to the helio co-ords.
  //                                    helio co-ord Jupiter            Helio co-ord Earth 
  //                                :---------------------------:  :----------------------------:
  output = api.helio_ecl_to_geo_ecl(45.83832, -1.06566, 4.9848972, 100.04627, -0.00016, 0.9833183);

  // These lines are used for diagnostic reasons.
  cout << "Output (Helio to Geo):" << endl;
  cout << "Calculated helio lambda   = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated helio beta     = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated helio distance = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << endl;

  return 0;
}
