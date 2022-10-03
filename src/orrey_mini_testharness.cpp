// Test BOOST_CHECK_CLOSE
// From:
//	https://www.boost.org/doc/libs/1_31_0/libs/test/doc/components/test_tools/reference/BOOST_CHECK_CLOSE.html

// To build:
//	g++ -Wall -o testharness.out orrey_mini_testharness.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp -lboost_system -lboost_thread -lboost_unit_test_framework

// each test module could contain no more then one 'main' file with init function defined
// alternatively you could define init function yourself
#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include "orrey_mini_testharness_tolerances.hpp"
#include "api_interface.hpp"
#include "astronomy_object.hpp"
#include <math.h>

#include <iostream>
#include <iomanip>

using namespace std;

// Test the ecl_to_equ function. 
BOOST_AUTO_TEST_CASE( TestJunit000_000_000_0000 )    
{
  api_interface api;
  double expected_output[2];
  double ecl[2];
  double *output;
  int results_check = 0;

  // Set the expected answers.
  expected_output[0] =   9 + (34.0/60.0) + (53.44/3600.0); // Actual RA
  expected_output[1] =  19 + (32.0/60.0) + (2.0/3600.0);   // Actual Dec
  
  ecl[0] = 139.686111;
  ecl[1] =   4.875278;
		 
  output = api.ecl_to_equ(&ecl[0], 1980, 1, 1, 0, 0, 0.0, 0.0);
						
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= EQU_RA_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= EQU_DEC_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit000_000_000_0000" << endl;  
  cout << "Expected equ ra           = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected equ dec          = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Calculated equ ra         = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated equ dec        = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 2);			
}

BOOST_AUTO_TEST_CASE( TestJunit000_000_000_0001 )    
{
  // Expected results from:
  // Example from Astronomy with your Calculator p40
  api_interface api;
  double expected_output[2];
  double ecl[2];
  double *output;
  int results_check = 0;
    
  // Set the expected answers.
  expected_output[0] =   9 + (34.0/60.0) + (53.44/3600.0); // Actual RA
  expected_output[1] =  19 + (32.0/60.0) + (2.0/3600.0);   // Actual Dec
  
  ecl[0] = 139.686111;
  ecl[1] =   4.875278;
		 
  output = api.ecl_to_equ(&ecl[0], 2444238.50000);
						
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= EQU_RA_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= EQU_DEC_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit000_000_000_0001" << endl;  
  cout << "Expected equ ra           = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected equ dec          = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Calculated equ ra         = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated equ dec        = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 2);			
}

// Test the ecl_to_hor function. 
BOOST_AUTO_TEST_CASE( TestJunit000_001_000_0000 )    
{
  // Expected results from:
  // Example from Practical Astronomy with your Calculator p48
  api_interface api;
  double expected_output[2];
  double ecl[2];
  double *output;
  int results_check = 0;

  // My test examples
  // Set the expected answers. hor co-ords for Jupiter 51.5N 0.00W
  expected_output[0] =  57.858046;
  expected_output[1] = 183.376322;
  
  // Geo ecliptic co-ords for Jupiter 1988/11/22 00:00:00
  ecl[0] =  61.2007435;
  ecl[1] =  -1.0319226;
		 
  output = api.ecl_to_hor(&ecl[0], 2447487.5, 0.0, 51.5);

  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= HOR_AZIMUTH_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= HOR_ALTITUDE_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit000_001_000_0000" << endl;  
  cout << "Expected hor azimuth      = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected hor altitude     = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Calculated hor azimuth    = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated hor alitude    = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 2);			
}

BOOST_AUTO_TEST_CASE( TestJunit000_001_000_0001 )    
{
  api_interface api;
  double expected_output[2];
  double ecl[2];
  double *output;
  int results_check = 0;
    
  // My test examples
  // Set the expected answers. hor co-ords for Jupiter 51.5N 0.00W
  expected_output[0] =  57.858046;
  expected_output[1] = 183.376322;

  // Geo ecliptic co-ords for Jupiter 1988/11/22 00:00:00
  ecl[0] =  61.2007435;
  ecl[1] =  -1.0319226;

  output = api.ecl_to_hor(&ecl[0], 1988, 11, 22, 0, 0, 0.0, 0.0, 0.0, 51.5);
						
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= HOR_AZIMUTH_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= HOR_ALTITUDE_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit000_001_000_0001" << endl;  
  cout << "Expected hor azimuth      = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected hor altitude     = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Calculated hor azimuth    = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated hor alitude    = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 2);			
}

// Test the helio ecl to geo ecliptic co-ord method
// Can convert from geo to helio.
BOOST_AUTO_TEST_CASE( TestJunit000_003_000_0000 )    
{
  api_interface api;
  double expected_output[3];
  double *output;
  int results_check = 0;
  
  // Set the expected answers.
  expected_output[0] = 61.0969; 
  expected_output[1] = -0.8277;
  expected_output[2] = 5.021236536482; 
  
  // The position is for Jupiter on 22nd Nov 1988 at 00:00:00
  // Convert the geo ecl co-ords for the object and the origin(Sun) and convert to the helio co-ords.
  output = api.helio_ecl_to_geo_ecl(61.2007435, -1.0319226, 4.03398217780624, 239.9074184, 0.0001560, 0.98758155072300);
  					
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= GEO_HELIO_ECL_LAMBDA_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= GEO_HELIO_ECL_BETA_TOL )
    results_check++;

  if ( abs((output[2] - expected_output[2])) <= GEO_HELIO_ECL_DISTANCE_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit000_000_003_0000" << endl;  
  cout << "Expected geo lambda     = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected geo beta       = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Expected geo distance   = " << setprecision(DISPLAY_PRECISION) << expected_output[2] << endl;
  cout << "Calculated geo lambda   = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated geo beta     = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated geo distance = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 3);			
}

// Test the helio ecl to geo ecliptic co-ord method
// Can convert from helio to geo.
BOOST_AUTO_TEST_CASE( TestJunit000_003_000_0001 )    
{
  api_interface api;
  double expected_output[3];
  double *output;
  int results_check = 0;
  
  // Set the expected answers.
  expected_output[0] = 61.2007435; 
  expected_output[1] = -1.0319226;
  expected_output[2] = 4.03398217780624; 
  
  // The position is for Jupiter on 22nd Nov 1988 at 00:00:00
  // Convert the helio ecl co-ords for the object and the origin(Earth) and convert to the geo co-ords.
  output = api.helio_ecl_to_geo_ecl(61.0969, -0.8277, 5.021236536482, 59.9074184, -0.0001560, 0.98758155072300);
  					
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= HELIO_GEO_ECL_LAMBDA_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= HELIO_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((output[2] - expected_output[2])) <= HELIO_GEO_ECL_DISTANCE_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit000_000_003_0001" << endl;  
  cout << "Expected helio lambda     = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected helio beta       = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Expected helio distance   = " << setprecision(DISPLAY_PRECISION) << expected_output[2] << endl;
  cout << "Calculated helio lambda   = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated helio beta     = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated helio distance = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 3);			
}

// Test the hor_to_equ function. 
BOOST_AUTO_TEST_CASE( TestJunit000_004_000_0000 )    
{
  api_interface api;
  double expected_output[2];
  double *output;
  int results_check = 0;
    
  // Set the expected answers.
  expected_output[0] = 15.8591666;	// Expected RA
  expected_output[1] = -20.165556;	// Expected DEC
		 
  output = api.hor_to_equ(-58.2,  6.2, 51.5, 0.0, 2447487.50000);
						
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= EQU_RA_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= EQU_DEC_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit000_004_000_0000" << endl;  
  cout << "Expected equ ra           = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected equ dec          = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Calculated equ ra         = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated equ dec        = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated hour angle     = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << "results_check             = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 2);			
}

// Test the equ_to_hor function. 
BOOST_AUTO_TEST_CASE( TestJunit000_005_000_0000 )    
{
  // Expected results from:
  // Example from Practical Astronomy for your Calculator p35-36
  // Convert RA 18hr 32m 21s DEC = +23 13' 10" to horizontal co-ords at 52N 64W on 1980 Apr 22 14h 36m 51.67s UT

  api_interface api;
  double expected_output[2];
  double *output;
  int results_check = 0;
    
  // Set the expected answers.
  expected_output[0] =  19.33434688480822;	// Altitude
  expected_output[1] = 283.2710244987528;	// Azimuth
		 
  output = api.equ_to_hor(2444352.1089313 ,18.539167, 23.219444, 52, -64.0);
						
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= HOR_AZIMUTH_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= HOR_ALTITUDE_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit000_005_000_0000" << endl;  
  cout << "Expected hor altitude     = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected hor azimuth      = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Calculated hor alitude    = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated hor azimuth    = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 2);			
}

//001	000		000			0000	Julian date
// Julian date - year,month, day,etc
BOOST_AUTO_TEST_CASE( TestJunit001_000_000_0000 )    
{
  // Expected results from:
  // Astronomical Algorithums ? 
  api_interface api;
  double actual_value = 2448972.500000;	
  double output;
  int results_check = 0;
    
  output = api.julian_date(1992,12,16,0,0,0.0);		 
						
  // Check that the answer is within the tolerance.
  if ( abs((output - actual_value)) <= JULIAN_DATE_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_000_000_0000" << endl;
  cout << "Expected Julian date      = " << setprecision(DISPLAY_PRECISION) << actual_value << endl;
  cout << "Calculated Julian date    = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;	
	
  BOOST_CHECK(results_check == 1);			
}

//001	001		000			0000	Julian to date
BOOST_AUTO_TEST_CASE( TestJunit001_001_000_0000 )    
{
  // Expected results from:
  // Practical Astronomy with your Calculator p8
  api_interface api;
  double actual_value[6];	
  double *output;
  int results_check = 0;
  
  actual_value[0] = 1985.0;
  actual_value[1] = 2.0;
  actual_value[2] = 17.0;
  actual_value[3] = 6.0;
  actual_value[4] = 0.0;
  actual_value[5] = 0.0;
    
  output = api.julian_to_date(2446113.75);		 
						
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - actual_value[0])) <= JULIAN_DATE_TOL )
    results_check++;

  if ( abs((output[1] - actual_value[1])) <= JULIAN_DATE_TOL )
    results_check++;

  if ( abs((output[2] - actual_value[2])) <= JULIAN_DATE_TOL )
    results_check++;
    
  if ( abs((output[3] - actual_value[3])) <= JULIAN_DATE_TOL )
    results_check++;
    
  if ( abs((output[4] - actual_value[4])) <= JULIAN_DATE_TOL )
    results_check++;
    
  if ( abs((output[5] - actual_value[5])) <= JULIAN_DATE_TOL )
    results_check++;
        				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_001_000_0000" << endl;
  cout << "Expected actual_value[0]  = " << setprecision(DISPLAY_PRECISION) << actual_value[0] << endl;
  cout << "Expected actual_value[1]  = " << setprecision(DISPLAY_PRECISION) << actual_value[1] << endl;
  cout << "Expected actual_value[2]  = " << setprecision(DISPLAY_PRECISION) << actual_value[2] << endl;
  cout << "Expected actual_value[3]  = " << setprecision(DISPLAY_PRECISION) << actual_value[3] << endl;
  cout << "Expected actual_value[4]  = " << setprecision(DISPLAY_PRECISION) << actual_value[4] << endl;
  cout << "Expected actual_value[5]  = " << setprecision(DISPLAY_PRECISION) << actual_value[5] << endl;
  cout << "Calculated output[0]      = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated output[1]      = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated output[2]      = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << "Calculated output[3]      = " << setprecision(DISPLAY_PRECISION) << output[3] << endl;
  cout << "Calculated output[4]      = " << setprecision(DISPLAY_PRECISION) << output[4] << endl;
  cout << "Calculated output[5]      = " << setprecision(DISPLAY_PRECISION) << output[5] << endl;
  cout << endl;	
	
  BOOST_CHECK(results_check == 6);			
}

//001	002		000			0000	gst
// Test the gst function.
BOOST_AUTO_TEST_CASE( TestJunit001_002_000_0000 )    
{
  // Expected results from:
  // Practical Astronomy with your Calculator p17
  api_interface api;
  double actual_value = 4.66784;
  double output;
  int results_check = 0;
    
  //output = api.gst(1980, 4, 22, 14, 36, 51.67);
  output = api.gst(1980, 4, 22, 14, 36, 50.69);

  // Check that the answer is within the tolerance.
  if ( abs((output - actual_value)) <= GST_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_002_000_0000" << endl;
  cout << "Expected gst              = " << setprecision(DISPLAY_PRECISION) << actual_value << endl;
  cout << "Calculated gst            = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;	
	
  BOOST_CHECK(results_check == 1);			
}

//001	002		000			0001	gst
// Test the gst function.
BOOST_AUTO_TEST_CASE( TestJunit001_002_000_0001 )
{
  // Expected results from:
  // Practical Astronomy with your Calculator p17
  api_interface api;
  double actual_value = 4.66784;
  double output;
  int results_check = 0;

  output = api.gst(2444352.10892);

  // Check that the answer is within the tolerance.
  if ( abs((output - actual_value)) <= GST_TOL )
    results_check++;

  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_002_000_0001" << endl;
  cout << "Expected gst              = " << setprecision(DISPLAY_PRECISION) << actual_value << endl;
  cout << "Calculated gst            = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  BOOST_CHECK(results_check == 1);
}

//001	003		000			0000	lst
// Test the lst function.
BOOST_AUTO_TEST_CASE( TestJunit001_003_000_0000 )    
{
  // Expected results from:
  // Practical Astronomy for your Calculator p20
  api_interface api;
  double actual_value = 0.401453;	
  double output;
  int results_check = 0;
    
  output = api.lst(1980, 4, 22, 14, 36, 51.67, 0.0, 64);		 
						
  // Check that the answer is within the tolerance.
  if ( abs((output - actual_value)) <= LST_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_003_000_0000" << endl;
  cout << "Expected lst              = " << setprecision(DISPLAY_PRECISION) << actual_value << endl;
  cout << "Calculated lst            = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;	
	
  BOOST_CHECK(results_check == 1);			
}

//001	003		000			0001	lst
// Test the lst function.
BOOST_AUTO_TEST_CASE( TestJunit001_003_000_0001 )
{
  // Expected results from:
  // Practical Astronomy for your Calculator p20
  api_interface api;
  double actual_value = 0.4011808;
  double output;
  int results_check = 0;

  output = api.lst(2444352.10892, 64);

  // Check that the answer is within the tolerance.
  if ( abs((output - actual_value)) <= LST_TOL )
    results_check++;

  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_003_000_0000" << endl;
  cout << "Expected lst              = " << setprecision(DISPLAY_PRECISION) << actual_value << endl;
  cout << "Calculated lst            = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  BOOST_CHECK(results_check == 1);
}

//001	004		000			0000	lst to gst
// Test the lst_to_gst function.
BOOST_AUTO_TEST_CASE( TestJunit001_004_000_0000 )    
{
  // Expected results from:
  // Practical Astronomy for your Calculator p21 0.401453 64W
  api_interface api;
  double actual_value = 4.668119;	
  double output;
  int results_check = 0;
    
  output = api.lst_to_gst(0.401453,64);		 
						
  // Check that the answer is within the tolerance.
  if ( abs((output - actual_value)) <= GST_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_004_000_0000" << endl;
  cout << "Expected lst_to_gst       = " << setprecision(DISPLAY_PRECISION) << actual_value << endl;
  cout << "Calculated lst_to_gst     = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;	
	
  BOOST_CHECK(results_check == 1);			
}

//001	005		000			0000	gst to ut
// Test the gst_to_ut function.
BOOST_AUTO_TEST_CASE( TestJunit001_005_000_0000 )    
{
  // Expected results from:
  // Practical Astronomy for Your Calculator p18 1980 4 22 4.668119
  api_interface api;
  double actual_value = 14.614353;	
  double output;
  int results_check = 0;
    
  output = api.gst_to_ut(1980,4,22,4.668119);		 
						
  // Check that the answer is within the tolerance.
  if ( abs((output - actual_value)) <= UT_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_005_000_0000" << endl;
  cout << "Expected gst_to_ut        = " << setprecision(DISPLAY_PRECISION) << actual_value << endl;
  cout << "Calculated gst_to_ust     = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;	
	
  BOOST_CHECK(results_check == 1);			
}

//001	005		000			0001	gst to ut
// Test the gst_to_ut function.
BOOST_AUTO_TEST_CASE( TestJunit001_005_000_0001 )
{
  // Expected results from:
  // Practical Astronomy for Your Calculator p18 1980 4 22 4.668119
  api_interface api;
  double actual_value = 14.614353;
  double output;
  int results_check = 0;

  output = api.gst_to_ut(2444351.50000,4.668119);

  // Check that the answer is within the tolerance.
  if ( abs((output - actual_value)) <= UT_TOL )
    results_check++;

  // These lines are used for diagnostic reasons.
  cout << "TestJunit001_005_000_0001" << endl;
  cout << "Expected gst_to_ut        = " << setprecision(DISPLAY_PRECISION) << actual_value << endl;
  cout << "Calculated gst_to_ust     = " << setprecision(DISPLAY_PRECISION) << output << endl;
  cout << endl;

  BOOST_CHECK(results_check == 1);
}

//002	000		000			0000	Sun
// Check Sun details 12
BOOST_AUTO_TEST_CASE( TestJunit002_000_000_0000 )    
{
  // Expected results from:
  // Example from www.heavens-above.com, www.calsky.com(no longer exists).
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;
    
  // Set the expected answers.
  expected_output[0] = 239.9077269;				// geo_ecliptic_lambda
  expected_output[1] =  -0.0010841;				// geo_ecliptic_beta
  expected_output[2] =   0.0;					// helio_ecliptic_lambda
  expected_output[3] =   0.0;					// helio_ecliptic_beta 
  expected_output[4] =  15 + (51.0/60.0) + (33.24/3600.0);	// RA (apparent)
  expected_output[5] = -20 - (22.0/60.0) - (38.80/3600.0);	// DEC (apparent)
  expected_output[6] =  -58.516887;                             // hor_altitude
  expected_output[7] =    6.257001;                             // hor_azimuth
  expected_output[8] =    0.9875817;				// Sun-Earth distance
  expected_output[9] =    1943.424;				// angular size 
  expected_output[10] =    492.80792;				// light travel time
  expected_output[11] =    0.0;                                 // Sun-object distance
  expected_output[12] =    1.0;                                 // phase
  expected_output[13] =    -26.7;				// magnitude
  expected_output[14] =    122.0;				// azimuth rise 
  expected_output[15] =    237.0;				// azimuth set
  expected_output[16] =    2447487.81250;			// rise time 
  expected_output[17] =    2447487.99028;			// transit time 
  expected_output[18] =    2447488.16806;			// set time 
   
  objects = api.object_details(2447487.50000,0.0,51.5);	
						
  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_SUN].actual_geo_ecliptic_lambda - expected_output[0])) <= SUN_GEO_ECL_LAMBDA_TOL )
    results_check++;
    							
  if ( abs((objects[OBJECT_ID_SUN].actual_geo_ecliptic_beta - expected_output[1])) <= SUN_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_SUN].actual_helio_ecliptic_lambda - expected_output[2])) <= SUN_HELIO_ECL_LAMBDA_TOL )
    results_check++;			

  if ( abs((objects[OBJECT_ID_SUN].actual_helio_ecliptic_beta - expected_output[3])) <= SUN_HELIO_ECL_BETA_TOL )
    results_check++;			

  if ( abs((objects[OBJECT_ID_SUN].equ_ra - expected_output[4])) <= SUN_EQU_RA_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SUN].equ_dec - expected_output[5])) <= SUN_EQU_DEC_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SUN].hor_altitude - expected_output[6])) <= SUN_HOR_AZIMUTH_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SUN].hor_azimuth - expected_output[7])) <= SUN_HOR_ALTITUDE_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SUN].earth_object_distance - expected_output[8])) <= SUN_EARTH_DIST_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_SUN].angular_size - expected_output[9])) <= SUN_ANGULAR_SIZE_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SUN].light_travel_time - expected_output[10])) <= SUN_LIGHT_TRAVEL_TOL )
    results_check++;	
    
  if ( abs((objects[OBJECT_ID_SUN].sun_object_distance - expected_output[11])) <= SUN_SUN_DIST_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SUN].phase - expected_output[12])) <= SUN_PHASE_TOL )
    results_check++;   

  if ( abs((objects[OBJECT_ID_SUN].magnitude - expected_output[13])) <= SUN_MAG_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_SUN].azimuth_rise - expected_output[14])) <= SUN_AZIMUTH_RISE_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_SUN].azimuth_set - expected_output[15])) <= SUN_AZIMUTH_SET_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_SUN].rise_time - expected_output[16])) <= SUN_RISE_TIME_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_SUN].transit_time - expected_output[17])) <= SUN_TRANSIT_TIME_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_SUN].set_time - expected_output[18])) <= SUN_SET_TIME_TOL )
    results_check++;     
    			    			
  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_000_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Sun actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Sun actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Sun actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Sun actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Sun RA                             = " << expected_output[4] << endl;
  cout << "Sun DEC                            = " << expected_output[5] << endl;	
  cout << "Sun hor_altitude                   = " << expected_output[6] << endl;
  cout << "Sun hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Sun Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Sun angular size                   = " << expected_output[9] << endl;
  cout << "Sun light travel time              = " << expected_output[10] << endl;
  cout << "Sun Sun-object distance            = " << expected_output[11] << endl;
  cout << "Sun phase                          = " << expected_output[12] << endl;
  cout << "Sun magnitude                      = " << expected_output[13] << endl;
  cout << "Sun azimuth rise                   = " << expected_output[14] << endl;
  cout << "Sun azimuth set                    = " << expected_output[15] << endl;
  cout << "Sun rise time                      = " << expected_output[16] << endl;
  cout << "Sun transit time                   = " << expected_output[17] << endl;
  cout << "Sun set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Sun actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_SUN].actual_geo_ecliptic_lambda << endl;
  cout << "Sun actual geo ecliptic beta       = " << objects[OBJECT_ID_SUN].actual_geo_ecliptic_beta << endl; 
  cout << "Sun actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_SUN].actual_helio_ecliptic_lambda << endl;
  cout << "Sun actual helio ecliptic beta     = " << objects[OBJECT_ID_SUN].actual_helio_ecliptic_beta << endl;
  cout << "Sun RA                             = " << objects[OBJECT_ID_SUN].equ_ra << endl;
  cout << "Sun DEC                            = " << objects[OBJECT_ID_SUN].equ_dec << endl;	
  cout << "Sun hor_altitude                   = " << objects[OBJECT_ID_SUN].hor_altitude << endl;
  cout << "Sun hor_azimuth                    = " << objects[OBJECT_ID_SUN].hor_azimuth << endl;		
  cout << "Sun Sun-Earth distance             = " << objects[OBJECT_ID_SUN].earth_object_distance  << endl;
  cout << "Sun angular size                   = " << objects[OBJECT_ID_SUN].angular_size << endl;
  cout << "Sun light travel time              = " << objects[OBJECT_ID_SUN].light_travel_time << endl;
  cout << "Sun Sun-object distance            = " << objects[OBJECT_ID_SUN].sun_object_distance << endl;
  cout << "Sun phase                          = " << objects[OBJECT_ID_SUN].phase << endl;
  cout << "Sun magnitude                      = " << objects[OBJECT_ID_SUN].magnitude << endl;
  cout << "Sun azimuth rise                   = " << objects[OBJECT_ID_SUN].azimuth_rise << endl;
  cout << "Sun azimuth set                    = " << objects[OBJECT_ID_SUN].azimuth_set << endl;
  cout << "Sun rise time                      = " << objects[OBJECT_ID_SUN].rise_time << endl;
  cout << "Sun transit time                   = " << objects[OBJECT_ID_SUN].transit_time << endl;
  cout << "Sun set time                       = " << objects[OBJECT_ID_SUN].set_time << endl;
  cout << "Results                            = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	001		000			0000	Moon
// Check Moon details 21
BOOST_AUTO_TEST_CASE( TestJunit002_001_000_0000 )    
{
  // Expected results from:
  // Example from 
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;
   
  expected_output[0] =  37.3521173;				// geo_ecliptic_lambda
  expected_output[1] =   3.7719351;				// geo_ecliptic_beta
  expected_output[2] =  60.0138;				// helio_ecliptic_lambda
  expected_output[3] =   0.0116;				// helio_ecliptic_beta 
  expected_output[4] =   2 + (15.0/60.0) + (26.44/3600.0);	// RA
  expected_output[5] =  17 + (34.0/60.0) + (40.10/3600.0);	// DEC
  expected_output[6] =   49.670284;                             // hor_altitude
  expected_output[7] =  222.842592;                             // hor_azimuth
  expected_output[8] =    0.00242647756684;			// Moon-Earth distance
  expected_output[9] =    1948.271;				// angular size 
  expected_output[10] =    1.2271188;                           // light travel time
  expected_output[11] =    0.989854195650;			// Sun-object distance
  expected_output[12] =    0.9609216;				// phase
  expected_output[13] =    -12.7;				// magnitude
  expected_output[14] =     55.0;				// azimuth rise 
  expected_output[15] =    302.0;				// azimuth set
  expected_output[16] =    2447488.11667;			// rise time
  expected_output[17] =    2447488.46181;			// transit time 
  expected_output[18] =    2447487.75625;			// set time   
    
  objects = api.object_details(2447487.50000,0.0,51.5);	

  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_MOON].actual_geo_ecliptic_lambda - expected_output[0])) <= MOON_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_MOON].actual_geo_ecliptic_beta - expected_output[1])) <= MOON_GEO_ECL_BETA_TOL )
    results_check++;
	
  if ( abs((objects[OBJECT_ID_MOON].actual_helio_ecliptic_lambda - expected_output[2])) <= MOON_HELIO_ECL_LAMBDA_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MOON].actual_helio_ecliptic_beta - expected_output[3])) <= MOON_HELIO_ECL_BETA_TOL )
    results_check++;			

  if ( abs((objects[OBJECT_ID_MOON].equ_ra - expected_output[4])) <= MOON_EQU_RA_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_MOON].equ_dec - expected_output[5])) <= MOON_EQU_DEC_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MOON].hor_altitude - expected_output[6])) <= MOON_HOR_AZIMUTH_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MOON].hor_azimuth - expected_output[7])) <= MOON_HOR_ALTITUDE_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MOON].earth_object_distance - expected_output[8])) <= MOON_EARTH_DIST_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MOON].angular_size - expected_output[9])) <= MOON_ANGULAR_SIZE_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MOON].light_travel_time - expected_output[10])) <= MOON_LIGHT_TRAVEL_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MOON].sun_object_distance - expected_output[11])) <= MOON_SUN_DIST_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MOON].phase - expected_output[12])) <= MOON_PHASE_TOL )
    results_check++;   

  if ( abs((objects[OBJECT_ID_MOON].magnitude - expected_output[13])) <= MOON_MAG_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_MOON].azimuth_rise - expected_output[14])) <= MOON_AZIMUTH_RISE_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_MOON].azimuth_set - expected_output[15])) <= MOON_AZIMUTH_SET_TOL )
    results_check++;    

  if ( abs((objects[OBJECT_ID_MOON].rise_time - expected_output[16])) <= MOON_RISE_TIME_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_MOON].transit_time - expected_output[17])) <= MOON_TRANSIT_TIME_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_MOON].set_time - expected_output[18])) <= MOON_SET_TIME_TOL )
    results_check++;     

  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_001_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Moon actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Moon actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Moon actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Moon actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Moon RA                             = " << expected_output[4] << endl;
  cout << "Moon DEC                            = " << expected_output[5] << endl;	
  cout << "Moon hor_altitude                   = " << expected_output[6] << endl;
  cout << "Moon hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Moon Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Moon angular size                   = " << expected_output[9] << endl;
  cout << "Moon light travel time              = " << expected_output[10] << endl;
  cout << "Moon Sun-object distance            = " << expected_output[11] << endl;
  cout << "Moon phase                          = " << expected_output[12] << endl;
  cout << "Moon magnitude                      = " << expected_output[13] << endl;
  cout << "Moon azimuth rise                   = " << expected_output[14] << endl;
  cout << "Moon azimuth set                    = " << expected_output[15] << endl;
  cout << "Moon rise time                      = " << expected_output[16] << endl;
  cout << "Moon transit time                   = " << expected_output[17] << endl;
  cout << "Moon set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Moon actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_MOON].actual_geo_ecliptic_lambda << endl;
  cout << "Moon actual geo ecliptic beta       = " << objects[OBJECT_ID_MOON].actual_geo_ecliptic_beta << endl; 
  cout << "Moon actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_MOON].actual_helio_ecliptic_lambda << endl;
  cout << "Moon actual helio ecliptic beta     = " << objects[OBJECT_ID_MOON].actual_helio_ecliptic_beta << endl;
  cout << "Moon RA                             = " << objects[OBJECT_ID_MOON].equ_ra << endl;
  cout << "Moon DEC                            = " << objects[OBJECT_ID_MOON].equ_dec << endl;	
  cout << "Moon hor_altitude                   = " << objects[OBJECT_ID_MOON].hor_altitude << endl;
  cout << "Moon hor_azimuth                    = " << objects[OBJECT_ID_MOON].hor_azimuth << endl;		
  cout << "Moon Object-Earth distance          = " << objects[OBJECT_ID_MOON].earth_object_distance  << endl;
  cout << "Moon angular size                   = " << objects[OBJECT_ID_MOON].angular_size << endl;
  cout << "Moon light travel time              = " << objects[OBJECT_ID_MOON].light_travel_time << endl;
  cout << "Moon Sun-object distance            = " << objects[OBJECT_ID_MOON].sun_object_distance << endl;
  cout << "Moon phase                          = " << objects[OBJECT_ID_MOON].phase << endl;
  cout << "Moon magnitude                      = " << objects[OBJECT_ID_MOON].magnitude << endl;
  cout << "Moon azimuth rise                   = " << objects[OBJECT_ID_MOON].azimuth_rise << endl;
  cout << "Moon azimuth set                    = " << objects[OBJECT_ID_MOON].azimuth_set << endl;
  cout << "Moon rise time                      = " << objects[OBJECT_ID_MOON].rise_time << endl;
  cout << "Moon transit time                   = " << objects[OBJECT_ID_MOON].transit_time << endl;
  cout << "Moon set time                       = " << objects[OBJECT_ID_MOON].set_time << endl;
  cout << "Results                             = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	002		000			0000	Mercury
// Check Mercury details 13
BOOST_AUTO_TEST_CASE( TestJunit002_002_000_0000 )    
{
  // Mercury on 22nd Nov 1988 00:00:00 at 51.5N and 0.0W
  // Expected results from:
  // https://ssd.jpl.nasa.gov/horizons/app.html#/
  // www.heavens-above.com
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;
    
  expected_output[0] = 234.5756806;				// geo_ecliptic_lambda
  expected_output[1] =   0.2108014;				// geo_ecliptic_beta
  expected_output[2] = 222.8664;				// helio_ecliptic_lambda
  expected_output[3] =  0.6722;                                 // helio_ecliptic_beta
  expected_output[4] =  15 + (29.0/60.0) + (43.68/3600.0);	// RA Astrometric
  expected_output[5] = -18 - (44.0/60.0) - (56.90/3600.0);	// DEC Astrometric
  expected_output[6] =   -56.463584;                            // hor_altitude
  expected_output[7] =    15.432571;                            // hor_azimuth
  expected_output[8] =    1.42003529159566;			// Mercury-Earth distance
  expected_output[9] =    4.737694;                             // angular size
  expected_output[10] =    708.604404;				// light travel time
  expected_output[11] =    0.446252351344;			// Sun-object distance
  expected_output[12] =    0.9892806;				// phase
  expected_output[13] =    -1.032;				// magnitude
  expected_output[14] =    121.4;				// azimuth rise 
  expected_output[15] =    238.3;				// azimuth set
  expected_output[16] =    2447487.79722;			// rise time 
  expected_output[17] =    2447487.97639;			// transit time 
  expected_output[18] =    2447488.15556;			// set time    
       
  objects = api.object_details(2447487.50000,0.0,51.5);
						
  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_MERCURY].actual_geo_ecliptic_lambda - expected_output[0])) <= MERCURY_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_MERCURY].actual_geo_ecliptic_beta - expected_output[1])) <= MERCURY_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_MERCURY].actual_helio_ecliptic_lambda - expected_output[2])) <= MERCURY_HELIO_ECL_LAMBDA_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MERCURY].actual_helio_ecliptic_beta - expected_output[3])) <= MERCURY_HELIO_ECL_BETA_TOL )
    results_check++;			
	
  if ( abs((objects[OBJECT_ID_MERCURY].equ_ra - expected_output[4])) <= MERCURY_EQU_RA_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_MERCURY].equ_dec - expected_output[5])) <= MERCURY_EQU_DEC_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MERCURY].hor_altitude - expected_output[6])) <= MERCURY_HOR_ALTITUDE_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_MERCURY].hor_azimuth - expected_output[7])) <= MERCURY_HOR_AZIMUTH_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_MERCURY].earth_object_distance - expected_output[8])) <= MERCURY_EARTH_DIST_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_MERCURY].angular_size - expected_output[9])) <= MERCURY_ANGULAR_SIZE_TOL )
    results_check++;	
	  
  if ( abs((objects[OBJECT_ID_MERCURY].light_travel_time - expected_output[10])) <= MERCURY_LIGHT_TRAVEL_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MERCURY].sun_object_distance - expected_output[11])) <= MERCURY_SUN_DIST_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MERCURY].phase - expected_output[12])) <= MERCURY_PHASE_TOL )
    results_check++;   
		    
  if ( abs((objects[OBJECT_ID_MERCURY].magnitude - expected_output[13])) <= MERCURY_MAG_TOL )
    results_check++;     
    
  if ( abs((objects[OBJECT_ID_MERCURY].azimuth_rise - expected_output[14])) <= MERCURY_AZIMUTH_RISE_TOL )
    results_check++;     
		  
  if ( abs((objects[OBJECT_ID_MERCURY].azimuth_set - expected_output[15])) <= MERCURY_AZIMUTH_SET_TOL )
    results_check++;    
  
  if ( abs((objects[OBJECT_ID_MERCURY].rise_time - expected_output[16])) <= MERCURY_RISE_TIME_TOL )
    results_check++;     
	  
  if ( abs((objects[OBJECT_ID_MERCURY].transit_time - expected_output[17])) <= MERCURY_TRANSIT_TIME_TOL )
    results_check++;     
  
  if ( abs((objects[OBJECT_ID_MERCURY].set_time - expected_output[18])) <= MERCURY_SET_TIME_TOL )
    results_check++;       
 
  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_002_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Mercury actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Mercury actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Mercury actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Mercury actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Mercury RA                             = " << expected_output[4] << endl;
  cout << "Mercury DEC                            = " << expected_output[5] << endl;	
  cout << "Mercury hor_altitude                   = " << expected_output[6] << endl;
  cout << "Mercury hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Mercury Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Mercury angular size                   = " << expected_output[9] << endl;
  cout << "Mercury light travel time              = " << expected_output[10] << endl;
  cout << "Mercury Sun-object distance            = " << expected_output[11] << endl;
  cout << "Mercury phase                          = " << expected_output[12] << endl;
  cout << "Mercury magnitude                      = " << expected_output[13] << endl;
  cout << "Mercury azimuth rise                   = " << expected_output[14] << endl;
  cout << "Mercury azimuth set                    = " << expected_output[15] << endl;
  cout << "Mercury rise time                      = " << expected_output[16] << endl;
  cout << "Mercury transit time                   = " << expected_output[17] << endl;
  cout << "Mercury set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Mercury actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_MERCURY].actual_geo_ecliptic_lambda << endl;
  cout << "Mercury actual geo ecliptic beta       = " << objects[OBJECT_ID_MERCURY].actual_geo_ecliptic_beta << endl; 
  cout << "Mercury actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_MERCURY].actual_helio_ecliptic_lambda << endl;
  cout << "Mercury actual helio ecliptic beta     = " << objects[OBJECT_ID_MERCURY].actual_helio_ecliptic_beta << endl;
  cout << "Mercury RA                             = " << objects[OBJECT_ID_MERCURY].equ_ra << endl;
  cout << "Mercury DEC                            = " << objects[OBJECT_ID_MERCURY].equ_dec << endl;	
  cout << "Mercury hor_altitude                   = " << objects[OBJECT_ID_MERCURY].hor_altitude << endl;
  cout << "Mercury hor_azimuth                    = " << objects[OBJECT_ID_MERCURY].hor_azimuth << endl;		
  cout << "Mercury Sun-Earth distance             = " << objects[OBJECT_ID_MERCURY].earth_object_distance  << endl;
  cout << "Mercury angular size                   = " << objects[OBJECT_ID_MERCURY].angular_size << endl;
  cout << "Mercury light travel time              = " << objects[OBJECT_ID_MERCURY].light_travel_time << endl;
  cout << "Mercury Sun-object distance            = " << objects[OBJECT_ID_MERCURY].sun_object_distance << endl;
  cout << "Mercury phase                          = " << objects[OBJECT_ID_MERCURY].phase << endl;
  cout << "Mercury magnitude                      = " << objects[OBJECT_ID_MERCURY].magnitude << endl;
  cout << "Mercury azimuth rise                   = " << objects[OBJECT_ID_MERCURY].azimuth_rise << endl;
  cout << "Mercury azimuth set                    = " << objects[OBJECT_ID_MERCURY].azimuth_set << endl;
  cout << "Mercury rise time                      = " << objects[OBJECT_ID_MERCURY].rise_time << endl;
  cout << "Mercury transit time                   = " << objects[OBJECT_ID_MERCURY].transit_time << endl;
  cout << "Mercury set time                       = " << objects[OBJECT_ID_MERCURY].set_time << endl;
  cout << "Results                                = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	003		000			0000	Venus
// Check Venus details 14
BOOST_AUTO_TEST_CASE( TestJunit002_003_000_0000 )    
{
  // Venus on 22nd Nov 1988 00:00:00 at 51.5N and 0.0W
  // Expected results from:
  // https://ssd.jpl.nasa.gov/horizons/app.html#/
  // www.heavens-above.com
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;

  expected_output[0] =  208.0731603;				// geo_ecliptic_lambda
  expected_output[1] =    1.8217367;				// geo_ecliptic_beta
  expected_output[2] =  161.7010;				// helio_ecliptic_lambda
  expected_output[3] =  3.3819;                                 // helio_ecliptic_beta
  expected_output[4] =  13 + (47.0/60.0) + (32.03/3600.0);	// RA Astrometric
  expected_output[5] = - 9 - (08.0/60.0) - (38.20/3600.0);	// DEC Astrometric
  expected_output[6] =  -39.081603;                             // hor_altitude
  expected_output[7] =   46.043061;                             // hor_azimuth
  expected_output[8] =    1.33354737204811;			// Sun-Earth distance
  expected_output[9] =    12.51428;				// angular size
  expected_output[10] =    665.446518;				// light travel time
  expected_output[11] =    0.719063940761;			// Earth-object distance
  expected_output[12] =    0.8441029;				// phase
  expected_output[13] =    -3.967;				// magnitude
  expected_output[14] =    104.9;				// azimuth rise 
  expected_output[15] =    254.8;				// azimuth set
  expected_output[16] =    2447487.68750;			// rise time 
  expected_output[17] =    2447487.90486;			// transit time 
  expected_output[18] =    2447488.12153;			// set time 
   
  objects = api.object_details(2447487.50000,0.0,51.5);
						
  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_VENUS].actual_geo_ecliptic_lambda - expected_output[0])) <= VENUS_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_VENUS].actual_geo_ecliptic_beta - expected_output[1])) <= VENUS_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_VENUS].actual_helio_ecliptic_lambda - expected_output[2])) <= VENUS_HELIO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_VENUS].actual_helio_ecliptic_beta - expected_output[3])) <= VENUS_HELIO_ECL_BETA_TOL )
    results_check++;			
	
  if ( abs((objects[OBJECT_ID_VENUS].equ_ra - expected_output[4])) <= VENUS_EQU_RA_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_VENUS].equ_dec - expected_output[5])) <= VENUS_EQU_DEC_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_VENUS].hor_altitude - expected_output[6])) <= VENUS_HOR_ALTITUDE_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_VENUS].hor_azimuth - expected_output[7])) <= VENUS_HOR_AZIMUTH_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_VENUS].earth_object_distance - expected_output[8])) <= VENUS_EARTH_DIST_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_VENUS].angular_size - expected_output[9])) <= VENUS_ANGULAR_SIZE_TOL )
    results_check++;	
 		  
  if ( abs((objects[OBJECT_ID_VENUS].light_travel_time - expected_output[10])) <= VENUS_LIGHT_TRAVEL_TOL )
    results_check++;	
 
  if ( abs((objects[OBJECT_ID_VENUS].sun_object_distance - expected_output[11])) <= VENUS_SUN_DIST_TOL )
    results_check++;	
	        
  if ( abs((objects[OBJECT_ID_VENUS].phase - expected_output[12])) <= VENUS_PHASE_TOL )
    results_check++;   
		    
  if ( abs((objects[OBJECT_ID_VENUS].magnitude - expected_output[13])) <= VENUS_MAG_TOL )
    results_check++;     
	    
  if ( abs((objects[OBJECT_ID_VENUS].azimuth_rise - expected_output[14])) <= VENUS_AZIMUTH_RISE_TOL )
    results_check++;     
	  
  if ( abs((objects[OBJECT_ID_VENUS].azimuth_set - expected_output[15])) <= VENUS_AZIMUTH_SET_TOL )
    results_check++;    
	  
  if ( abs((objects[OBJECT_ID_VENUS].rise_time - expected_output[16])) <= VENUS_RISE_TIME_TOL )
    results_check++;     
	  
  if ( abs((objects[OBJECT_ID_VENUS].transit_time - expected_output[17])) <= VENUS_TRANSIT_TIME_TOL )
    results_check++;     
	  
  if ( abs((objects[OBJECT_ID_VENUS].set_time - expected_output[18])) <= VENUS_SET_TIME_TOL )
    results_check++;       	

  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_003_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Venus actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Venus actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Venus actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Venus actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Venus RA                             = " << expected_output[4] << endl;
  cout << "Venus DEC                            = " << expected_output[5] << endl;	
  cout << "Venus hor_altitude                   = " << expected_output[6] << endl;
  cout << "Venus hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Venus Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Venus angular size                   = " << expected_output[9] << endl;
  cout << "Venus light travel time              = " << expected_output[10] << endl;
  cout << "Venus Sun-object distance            = " << expected_output[11] << endl;
  cout << "Venus phase                          = " << expected_output[12] << endl;
  cout << "Venus magnitude                      = " << expected_output[13] << endl;
  cout << "Venus azimuth rise                   = " << expected_output[14] << endl;
  cout << "Venus azimuth set                    = " << expected_output[15] << endl;
  cout << "Venus rise time                      = " << expected_output[16] << endl;
  cout << "Venus transit time                   = " << expected_output[17] << endl;
  cout << "Venus set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Venus actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_VENUS].actual_geo_ecliptic_lambda << endl;
  cout << "Venus actual geo ecliptic beta       = " << objects[OBJECT_ID_VENUS].actual_geo_ecliptic_beta << endl; 
  cout << "Venus actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_VENUS].actual_helio_ecliptic_lambda << endl;
  cout << "Venus actual helio ecliptic -1.032 beta     = " << objects[OBJECT_ID_VENUS].actual_helio_ecliptic_beta << endl;
  cout << "Venus RA                             = " << objects[OBJECT_ID_VENUS].equ_ra << endl;
  cout << "Venus DEC                            = " << objects[OBJECT_ID_VENUS].equ_dec << endl;	
  cout << "Venus hor_altitude                   = " << objects[OBJECT_ID_VENUS].hor_altitude << endl;
  cout << "Venus hor_azimuth                    = " << objects[OBJECT_ID_VENUS].hor_azimuth << endl;		
  cout << "Venus Sun-Earth distance             = " << objects[OBJECT_ID_VENUS].earth_object_distance  << endl;
  cout << "Venus angular size                   = " << objects[OBJECT_ID_VENUS].angular_size << endl;
  cout << "Venus light travel time              = " << objects[OBJECT_ID_VENUS].light_travel_time << endl;
  cout << "Venus Sun-object distance            = " << objects[OBJECT_ID_VENUS].sun_object_distance << endl;
  cout << "Venus phase                          = " << objects[OBJECT_ID_VENUS].phase << endl;
  cout << "Venus magnitude                      = " << objects[OBJECT_ID_VENUS].magnitude << endl;
  cout << "Venus azimuth rise                   = " << objects[OBJECT_ID_VENUS].azimuth_rise << endl;
  cout << "Venus azimuth set                    = " << objects[OBJECT_ID_VENUS].azimuth_set << endl;
  cout << "Venus rise time                      = " << objects[OBJECT_ID_VENUS].rise_time << endl;
  cout << "Venus transit time                   = " << objects[OBJECT_ID_VENUS].transit_time << endl;
  cout << "Venus set time                       = " << objects[OBJECT_ID_VENUS].set_time << endl;
  cout << "Results                              = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	004		000			0000	Earth
// Check Earth details 15
BOOST_AUTO_TEST_CASE( TestJunit002_004_000_0000 )    
{
  // Earth on 22nd Nov 1988 00:00:00 at 51.5N and 0.0W
  // Expected results from:
  // https://ssd.jpl.nasa.gov/horizons/app.html#/
  // www.heavens-above.com
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;

  expected_output[0] =   0.00;                                  // geo_ecliptic_lambda
  expected_output[1] =   0.00;                                  // geo_ecliptic_beta
  expected_output[2] =   59.9077269;				// helio_ecliptic_lambda
  expected_output[3] =    0.0010841;				// helio_ecliptic_beta
  expected_output[4] =   0 + ( 0.0/60.0) + ( 0.00/3600.0);	// RA Astrometric
  expected_output[5] =   0 + ( 0.0/60.0) + ( 0.00/3600.0);	// DEC Astrometric
  expected_output[6] =   0.0;					// hor_altitude
  expected_output[7] =    0.0;                                  // hor_azimuth
  expected_output[8] =    0.9875817;				// Sun-Earth distance
  expected_output[9] =    0.0;                                  // angular size
  expected_output[10] =    0.0;                                 // light travel time
  expected_output[11] =    0.0;                                 // Earth-object distance
  expected_output[12] =    1.0;                                 // phase
  expected_output[13] =    0.0;                                 // magnitude
  expected_output[14] =    0.0;                                 // azimuth rise
  expected_output[15] =    0.0;                                 // azimuth set
  expected_output[16] =    0.0; 	 			// rise time 
  expected_output[17] =    0.0;                                 // transit timeALTITUDE
  expected_output[18] =    0.0;                                 // set time
       
  objects = api.object_details(2447487.50000,0.0,51.5);
						
  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_EARTH].actual_geo_ecliptic_lambda - expected_output[0])) <= EARTH_GEO_ECL_LAMBDA_TOL )
    results_check++;
  							
  if ( abs((objects[OBJECT_ID_EARTH].actual_geo_ecliptic_beta - expected_output[1])) <= EARTH_GEO_ECL_BETA_TOL )
    results_check++;
			
  if ( abs((objects[OBJECT_ID_EARTH].actual_helio_ecliptic_lambda - expected_output[2])) <= EARTH_HELIO_ECL_LAMBDA_TOL )
    results_check++;			
		
  if ( abs((objects[OBJECT_ID_EARTH].actual_helio_ecliptic_beta - expected_output[3])) <= EARTH_HELIO_ECL_BETA_TOL )
    results_check++;			

  if ( abs((objects[OBJECT_ID_EARTH].equ_ra - expected_output[4])) <= EARTH_EQU_RA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_EARTH].equ_dec - expected_output[5])) <= EARTH_EQU_DEC_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_EARTH].hor_altitude - expected_output[6])) <= EARTH_HOR_ALTITUDE_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_EARTH].hor_azimuth - expected_output[7])) <= EARTH_HOR_AZIMUTH_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_EARTH].sun_object_distance - expected_output[8])) <= EARTH_EARTH_DIST_TOL )
    results_check++; 
  
  if ( abs((objects[OBJECT_ID_EARTH].light_travel_time - expected_output[10])) <= EARTH_ANGULAR_SIZE_TOL )
    results_check++;	
       
  if ( abs((objects[OBJECT_ID_EARTH].earth_object_distance - expected_output[11])) <= EARTH_EARTH_DIST_TOL )
    results_check++;	
      
  if ( abs((objects[OBJECT_ID_EARTH].angular_size - expected_output[9])) <= EARTH_SUN_DIST_TOL )
    results_check++;	
    
  if ( abs((objects[OBJECT_ID_EARTH].phase - expected_output[12])) <= EARTH_PHASE_TOL )
    results_check++;   
    
  if ( abs((objects[OBJECT_ID_EARTH].magnitude - expected_output[13])) <= EARTH_MAG_TOL )
    results_check++;     
    
  if ( abs((objects[OBJECT_ID_EARTH].azimuth_rise - expected_output[14])) <= EARTH_AZIMUTH_RISE_TOL )
    results_check++;     
  
  if ( abs((objects[OBJECT_ID_EARTH].azimuth_set - expected_output[15])) <= EARTH_AZIMUTH_SET_TOL )
    results_check++;     
    
  if ( abs((objects[OBJECT_ID_EARTH].rise_time - expected_output[16])) <= EARTH_RISE_TIME_TOL )
    results_check++;     
   
  if ( abs((objects[OBJECT_ID_EARTH].transit_time - expected_output[17])) <= EARTH_TRANSIT_TIME_TOL )
    results_check++;     
  
  if ( abs((objects[OBJECT_ID_EARTH].set_time - expected_output[18])) <= EARTH_SET_TIME_TOL )
    results_check++;     	  			
    			
  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_004_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Earth actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Earth actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Earth actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Earth actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Earth RA                             = " << expected_output[4] << endl;
  cout << "Earth DEC                            = " << expected_output[5] << endl;	
  cout << "Earth hor_altitude                   = " << expected_output[6] << endl;
  cout << "Earth hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Earth Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Earth angular size                   = " << expected_output[9] << endl;
  cout << "Earth light travel time              = " << expected_output[10] << endl;
  cout << "Earth Sun-object distance            = " << expected_output[11] << endl;
  cout << "Earth phase                          = " << expected_output[12] << endl;
  cout << "Earth magnitude                      = " << expected_output[13] << endl;
  cout << "Earth azimuth rise                   = " << expected_output[14] << endl;
  cout << "Earth azimuth set                    = " << expected_output[15] << endl;
  cout << "Earth rise time                      = " << expected_output[16] << endl;
  cout << "Earth transit time                   = " << expected_output[17] << endl;
  cout << "Earth set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Earth actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_EARTH].actual_geo_ecliptic_lambda << endl;
  cout << "Earth actual geo ecliptic beta       = " << objects[OBJECT_ID_EARTH].actual_geo_ecliptic_beta << endl; 
  cout << "Earth actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_EARTH].actual_helio_ecliptic_lambda << endl;
  cout << "Earth actual helio ecliptic beta     = " << objects[OBJECT_ID_EARTH].actual_helio_ecliptic_beta << endl;
  cout << "Earth RA                             = " << objects[OBJECT_ID_EARTH].equ_ra << endl;
  cout << "Earth DEC                            = " << objects[OBJECT_ID_EARTH].equ_dec << endl;	
  cout << "Earth hor_altitude                   = " << objects[OBJECT_ID_EARTH].hor_altitude << endl;
  cout << "Earth hor_azimuth                    = " << objects[OBJECT_ID_EARTH].hor_azimuth << endl;		
  cout << "Earth Sun-Earth distance             = " << objects[OBJECT_ID_EARTH].sun_object_distance  << endl;
  cout << "Earth angular size                   = " << objects[OBJECT_ID_EARTH].angular_size << endl;
  cout << "Earth light travel time              = " << objects[OBJECT_ID_EARTH].light_travel_time << endl;
  cout << "Earth object distance                = " << objects[OBJECT_ID_EARTH].earth_object_distance << endl;
  cout << "Earth phase                          = " << objects[OBJECT_ID_EARTH].phase << endl;
  cout << "Earth magnitude                      = " << objects[OBJECT_ID_EARTH].magnitude << endl;
  cout << "Earth azimuth rise                   = " << objects[OBJECT_ID_EARTH].azimuth_rise << endl;
  cout << "Earth azimuth set                    = " << objects[OBJECT_ID_EARTH].azimuth_set << endl;
  cout << "Earth rise time                      = " << objects[OBJECT_ID_EARTH].rise_time << endl;
  cout << "Earth transit time                   = " << objects[OBJECT_ID_EARTH].transit_time << endl;
  cout << "Earth set time                       = " << objects[OBJECT_ID_EARTH].set_time << endl;
  cout << "Results                              = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	005		000			0000	Mars
// Check Mars details 16
BOOST_AUTO_TEST_CASE( TestJunit002_005_000_0000 )    
{
  // Mars on 22nd Nov 1988 00:00:00 at 51.5N and 0.0W
  // Expected results from:
  // https://ssd.jpl.nasa.gov/horizons/app.html#/
  // www.heavens-above.com
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;

  expected_output[0] =   3.6073523;				// geo_ecliptic_lambda
  expected_output[1] =   -0.8158096;				// geo_ecliptic_beta
  expected_output[2] =  38.3448;				// helio_ecliptic_lambda
  expected_output[3] =  -0.3611;				// helio_ecliptic_beta 
  expected_output[4] =   0 + (15.0/60.0) + ( 5.44/3600.0);	// RA Astrometric
  expected_output[5] =   0 + (44.0/60.0) + (43.90/3600.0);	// DEC Astrometric
  expected_output[6] =   20.074388;                             // hor_altitude
  expected_output[7] =  243.962632;                             // hor_azimuth
  expected_output[8] =    0.64400361461097;			// Sun-Earth distance
  expected_output[9] =    14.54231;				// angular size
  expected_output[10] =    321.3608844;				// light travel time
  expected_output[11] =    1.447646362811;			// Sun-object distance
  expected_output[12] =    1.0;                                 // phase
  expected_output[13] =    -1.073;				// magnitude
  expected_output[14] =     88.7;				// azimuth rise 
  expected_output[15] =    271.5;				// azimuth set
  expected_output[16] =    2447488.08646;			// rise time
  expected_output[17] =    2447488.33889;			// transit time 
  expected_output[18] =    2447487.59306;			// set time
       
  objects = api.object_details(2447487.50000,0.0,51.5);
						
  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_MARS].actual_geo_ecliptic_lambda - expected_output[0])) <= MARS_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_MARS].actual_geo_ecliptic_beta - expected_output[1])) <= MARS_GEO_ECL_BETA_TOL )
    results_check++;
	
  if ( abs((objects[OBJECT_ID_MARS].actual_helio_ecliptic_lambda - expected_output[2])) <= MARS_HELIO_ECL_LAMBDA_TOL )
    results_check++;	
    							
  if ( abs((objects[OBJECT_ID_MARS].actual_helio_ecliptic_beta - expected_output[3])) <= MARS_HELIO_ECL_BETA_TOL )
    results_check++;			
	
  if ( abs((objects[OBJECT_ID_MARS].equ_ra - expected_output[4])) <= MARS_EQU_RA_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_MARS].equ_dec - expected_output[5])) <= MARS_EQU_DEC_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_MARS].hor_altitude - expected_output[6])) <= MARS_HOR_ALTITUDE_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_MARS].hor_azimuth - expected_output[7])) <= MARS_HOR_AZIMUTH_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_MARS].earth_object_distance - expected_output[8])) <= MARS_EARTH_DIST_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_MARS].angular_size - expected_output[9])) <= MARS_ANGULAR_SIZE_TOL )
    results_check++;	
    		  
  if ( abs((objects[OBJECT_ID_MARS].light_travel_time - expected_output[10])) <= MARS_LIGHT_TRAVEL_TOL )
    results_check++;	
    
  if ( abs((objects[OBJECT_ID_MARS].sun_object_distance - expected_output[11])) <= MARS_SUN_DIST_TOL )
    results_check++;	
		        
  if ( abs((objects[OBJECT_ID_MARS].phase - expected_output[12])) <= MARS_PHASE_TOL )
    results_check++;   
    		    
  if ( abs((objects[OBJECT_ID_MARS].magnitude - expected_output[13])) <= MARS_MAG_TOL )
    results_check++;     
	    
  if ( abs((objects[OBJECT_ID_MARS].azimuth_rise - expected_output[14])) <= MARS_AZIMUTH_RISE_TOL )
    results_check++;     
		  
  if ( abs((objects[OBJECT_ID_MARS].azimuth_set - expected_output[15])) <= MARS_AZIMUTH_SET_TOL )
    results_check++;    
     		  
  if ( abs((objects[OBJECT_ID_MARS].rise_time - expected_output[16])) <= MARS_RISE_TIME_TOL )
    results_check++;     
    		  
  if ( abs((objects[OBJECT_ID_MARS].transit_time - expected_output[17])) <= MARS_TRANSIT_TIME_TOL )
    results_check++;     
  		  
  if ( abs((objects[OBJECT_ID_MARS].set_time - expected_output[18])) <= MARS_SET_TIME_TOL )
    results_check++;     			    			  	
    			
  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_005_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Mars actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Mars actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Mars actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Mars actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Mars RA                             = " << expected_output[4] << endl;
  cout << "Mars DEC                            = " << expected_output[5] << endl;	
  cout << "Mars hor_altitude                   = " << expected_output[6] << endl;
  cout << "Mars hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Mars Earth distance                 = " << expected_output[8] << endl;
  cout << "Mars angular size                   = " << expected_output[9] << endl;
  cout << "Mars light travel time              = " << expected_output[10] << endl;
  cout << "Mars Sun-object distance            = " << expected_output[11] << endl;
  cout << "Mars phase                          = " << expected_output[12] << endl;
  cout << "Mars magnitude                      = " << expected_output[13] << endl;
  cout << "Mars azimuth rise                   = " << expected_output[14] << endl;
  cout << "Mars azimuth set                    = " << expected_output[15] << endl;
  cout << "Mars rise time                      = " << expected_output[16] << endl;
  cout << "Mars transit time                   = " << expected_output[17] << endl;
  cout << "Mars set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Mars actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_MARS].actual_geo_ecliptic_lambda << endl;
  cout << "Mars actual geo ecliptic beta       = " << objects[OBJECT_ID_MARS].actual_geo_ecliptic_beta << endl; 
  cout << "Mars actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_MARS].actual_helio_ecliptic_lambda << endl;
  cout << "Mars actual helio ecliptic beta     = " << objects[OBJECT_ID_MARS].actual_helio_ecliptic_beta << endl;
  cout << "Mars RA                             = " << objects[OBJECT_ID_MARS].equ_ra << endl;
  cout << "Mars DEC                            = " << objects[OBJECT_ID_MARS].equ_dec << endl;	
  cout << "Mars hor_altitude                   = " << objects[OBJECT_ID_MARS].hor_altitude << endl;
  cout << "Mars hor_azimuth                    = " << objects[OBJECT_ID_MARS].hor_azimuth << endl;		
  cout << "Mars Earth distance                 = " << objects[OBJECT_ID_MARS].earth_object_distance  << endl;
  cout << "Mars angular size                   = " << objects[OBJECT_ID_MARS].angular_size << endl;
  cout << "Mars light travel time              = " << objects[OBJECT_ID_MARS].light_travel_time << endl;
  cout << "Mars Sun-object distance            = " << objects[OBJECT_ID_MARS].sun_object_distance << endl;
  cout << "Mars phase                          = " << objects[OBJECT_ID_MARS].phase << endl;
  cout << "Mars magnitude                      = " << objects[OBJECT_ID_MARS].magnitude << endl;
  cout << "Mars azimuth rise                   = " << objects[OBJECT_ID_MARS].azimuth_rise << endl;
  cout << "Mars azimuth set                    = " << objects[OBJECT_ID_MARS].azimuth_set << endl;
  cout << "Mars rise time                      = " << objects[OBJECT_ID_MARS].rise_time << endl;
  cout << "Mars transit time                   = " << objects[OBJECT_ID_MARS].transit_time << endl;
  cout << "Mars set time                       = " << objects[OBJECT_ID_MARS].set_time << endl;
  cout << "Results                             = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);
}

//002	006		000			0000	Jupiter
// Check Jupiter details 17
BOOST_AUTO_TEST_CASE( TestJunit002_006_000_0000 )    
{
  // Jupiter on 22nd Nov 1988 00:00:00 at 51.5N and 0.0W
  // Expected results from:
  // https://ssd.jpl.nasa.gov/horizons/app.html#/
  // www.heavens-above.com
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;

  expected_output[0] =   61.2007233;				// geo_ecliptic_lambda
  expected_output[1] =   -1.0322433;				// geo_ecliptic_beta
  expected_output[2] =   61.0969;				// helio_ecliptic_lambda
  expected_output[3] =  -0.8277;				// helio_ecliptic_beta
  expected_output[4] =   3 + (57.0/60.0) + (47.52/3600.0);	// RA Astrometric
  expected_output[5] =  19 + (25.0/60.0) + (15.90/3600.0);	// DEC Astrometric
  expected_output[6] =   57.858047;                             // hor_altitude
  expected_output[7] =  183.376317;                             // hor_azimuth
  expected_output[8] =    4.03394645096661;			// Earth-object distance
  expected_output[9] =      48.87165;				// angular size
  expected_output[10] =   2012.9585766;				// light travel time
  expected_output[11] =    5.021236908950;			// Sun-object distance
  expected_output[12] =    1.0;                                 // phase
  expected_output[13] =    -2.862;				// magnitude
  expected_output[14] =    57.8;				// azimuth rise 
  expected_output[15] =    302.3;				// azimuth set
  expected_output[16] =    2447488.17014;			// rise time 
  expected_output[17] =    2447488.49236;			// transit time 
  expected_output[18] =    2447487.81736;			// set time 
   
  objects = api.object_details(2447487.50000,0.0,51.5);
  						
  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_JUPITER].actual_geo_ecliptic_lambda - expected_output[0])) <= JUPITER_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_JUPITER].actual_geo_ecliptic_beta - expected_output[1])) <= JUPITER_GEO_ECL_BETA_TOL )
    results_check++;
	
  if ( abs((objects[OBJECT_ID_JUPITER].actual_helio_ecliptic_lambda - expected_output[2])) <= JUPITER_HELIO_ECL_LAMBDA_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_JUPITER].actual_helio_ecliptic_beta - expected_output[3])) <= JUPITER_HELIO_ECL_BETA_TOL )
    results_check++;			
	
  if ( abs((objects[OBJECT_ID_JUPITER].equ_ra - expected_output[4])) <= JUPITER_EQU_RA_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_JUPITER].equ_dec - expected_output[5])) <= JUPITER_EQU_DEC_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_JUPITER].hor_altitude - expected_output[6])) <= JUPITER_HOR_ALTITUDE_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_JUPITER].hor_azimuth - expected_output[7])) <= JUPITER_HOR_AZIMUTH_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_JUPITER].earth_object_distance - expected_output[8])) <= JUPITER_EARTH_DIST_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_JUPITER].angular_size - expected_output[9])) <= JUPITER_ANGULAR_SIZE_TOL )
    results_check++;	
  		  
  if ( abs((objects[OBJECT_ID_JUPITER].light_travel_time - expected_output[10])) <= JUPITER_LIGHT_TRAVEL_TOL )
    results_check++;	
   
  if ( abs((objects[OBJECT_ID_JUPITER].sun_object_distance - expected_output[11])) <= JUPITER_SUN_DIST_TOL )
    results_check++;	
	        
  if ( abs((objects[OBJECT_ID_JUPITER].phase - expected_output[12])) <= JUPITER_PHASE_TOL )
    results_check++;   
   		    
  if ( abs((objects[OBJECT_ID_JUPITER].magnitude - expected_output[13])) <= JUPITER_MAG_TOL )
    results_check++;     
		    
  if ( abs((objects[OBJECT_ID_JUPITER].azimuth_rise - expected_output[14])) <= JUPITER_AZIMUTH_RISE_TOL )
    results_check++;     
		  
  if ( abs((objects[OBJECT_ID_JUPITER].azimuth_set - expected_output[15])) <= JUPITER_AZIMUTH_SET_TOL )
    results_check++;    
    		  
  if ( abs((objects[OBJECT_ID_JUPITER].rise_time - expected_output[16])) <= JUPITER_RISE_TIME_TOL )
    results_check++;     
    		  
  if ( abs((objects[OBJECT_ID_JUPITER].transit_time - expected_output[17])) <= JUPITER_TRANSIT_TIME_TOL )
    results_check++;     
  		  
  if ( abs((objects[OBJECT_ID_JUPITER].set_time - expected_output[18])) <= JUPITER_SET_TIME_TOL )
    results_check++;     
		    			    			
  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_006_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Jupiter actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Jupiter actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Jupiter actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Jupiter actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Jupiter RA                             = " << expected_output[4] << endl;
  cout << "Jupiter DEC                            = " << expected_output[5] << endl;	
  cout << "Jupiter hor_altitude                   = " << expected_output[6] << endl;
  cout << "Jupiter hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Jupiter Earth-Object distance          = " << expected_output[8] << endl;
  cout << "Jupiter angular size                   = " << expected_output[9] << endl;
  cout << "Jupiter light travel time              = " << expected_output[10] << endl;
  cout << "Jupiter Sun-object distance            = " << expected_output[11] << endl;
  cout << "Jupiter phase                          = " << expected_output[12] << endl;
  cout << "Jupiter magnitude                      = " << expected_output[13] << endl;
  cout << "Jupiter azimuth rise                   = " << expected_output[14] << endl;
  cout << "Jupiter azimuth set                    = " << expected_output[15] << endl;
  cout << "Jupiter rise time                      = " << expected_output[16] << endl;
  cout << "Jupiter transit time                   = " << expected_output[17] << endl;
  cout << "Jupiter set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Jupiter actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_JUPITER].actual_geo_ecliptic_lambda << endl;
  cout << "Jupiter actual geo ecliptic beta       = " << objects[OBJECT_ID_JUPITER].actual_geo_ecliptic_beta << endl; 
  cout << "Jupiter actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_JUPITER].actual_helio_ecliptic_lambda << endl;
  cout << "Jupiter actual helio ecliptic beta     = " << objects[OBJECT_ID_JUPITER].actual_helio_ecliptic_beta << endl;
  cout << "Jupiter RA                             = " << objects[OBJECT_ID_JUPITER].equ_ra << endl;
  cout << "Jupiter DEC                            = " << objects[OBJECT_ID_JUPITER].equ_dec << endl;	
  cout << "Jupiter hor_altitude                   = " << objects[OBJECT_ID_JUPITER].hor_altitude << endl;
  cout << "Jupiter hor_azimuth                    = " << objects[OBJECT_ID_JUPITER].hor_azimuth << endl;		
  cout << "Jupiter Earth-Object distance          = " << objects[OBJECT_ID_JUPITER].earth_object_distance  << endl;
  cout << "Jupiter angular size                   = " << objects[OBJECT_ID_JUPITER].angular_size << endl;
  cout << "Jupiter light travel time              = " << objects[OBJECT_ID_JUPITER].light_travel_time << endl;
  cout << "Jupiter Sun-object distance            = " << objects[OBJECT_ID_JUPITER].sun_object_distance << endl;
  cout << "Jupiter phase                          = " << objects[OBJECT_ID_JUPITER].phase << endl;
  cout << "Jupiter magnitude                      = " << objects[OBJECT_ID_JUPITER].magnitude << endl;
  cout << "Jupiter azimuth rise                   = " << objects[OBJECT_ID_JUPITER].azimuth_rise << endl;
  cout << "Jupiter azimuth set                    = " << objects[OBJECT_ID_JUPITER].azimuth_set << endl;
  cout << "Jupiter rise time                      = " << objects[OBJECT_ID_JUPITER].rise_time << endl;
  cout << "Jupiter transit time                   = " << objects[OBJECT_ID_JUPITER].transit_time << endl;
  cout << "Jupiter set time                       = " << objects[OBJECT_ID_JUPITER].set_time << endl;
  cout << "Results                                = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	007		000			0000	Saturn
// Check Saturn details 18
BOOST_AUTO_TEST_CASE( TestJunit002_007_000_0000 )    
{
  // Saturn on 22nd Nov 1988 00:00:00 at 51.5N and 0.0W
  // Expected results from:
  // https://ssd.jpl.nasa.gov/horizons/app.html#/
  // www.heavens-above.com
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;

  expected_output[0] = 270.9934310;				// geo_ecliptic_lambda
  expected_output[1] =   0.7726826;				// geo_ecliptic_beta
  expected_output[2] = 274.0628;				// helio_ecliptic_lambda
  expected_output[3] =   0.8354;				// helio_ecliptic_beta 
  expected_output[4] =  18 + ( 4.0/60.0) + (59.70/3600.0);	// RA Astrometric
  expected_output[5] = -22 - (39.0/60.0) - (47.10/3600.0);	// DEC Astrometric
  expected_output[6] =  -53.098729;                             // hor_altitude
  expected_output[7] =  310.039685;                             // hor_azimuth
  expected_output[8] =   10.8767708797101;			// Earth-object distance
  expected_output[9] =    15.28;				// angular size 
  expected_output[10] =    5427.5607018;			// light travel time
  expected_output[11] =    10.04400796067;			// Sun-object distance
  expected_output[12] =    1.0;                                 // phase
  expected_output[13] =    0.540;                                 // magnitude
  expected_output[14] =    128.2;				// azimuth rise 
  expected_output[15] =    231.8;				// azimuth set
  expected_output[16] =    2447487.92014;			// rise time 
  expected_output[17] =    2447488.08194;			// transit time
  expected_output[18] =    2447488.24375;			// set time 
   
  objects = api.object_details(2447487.50000,0.0,51.5);
						
  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_SATURN].actual_geo_ecliptic_lambda - expected_output[0])) <= SATURN_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_SATURN].actual_geo_ecliptic_beta - expected_output[1])) <= SATURN_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_SATURN].actual_helio_ecliptic_lambda - expected_output[2])) <= SATURN_HELIO_ECL_LAMBDA_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SATURN].actual_helio_ecliptic_beta - expected_output[3])) <= SATURN_HELIO_ECL_BETA_TOL )
    results_check++;			
		
  if ( abs((objects[OBJECT_ID_SATURN].equ_ra - expected_output[4])) <= SATURN_EQU_RA_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_SATURN].equ_dec - expected_output[5])) <= SATURN_EQU_DEC_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SATURN].hor_altitude - expected_output[6])) <= SATURN_HOR_ALTITUDE_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_SATURN].hor_azimuth - expected_output[7])) <= SATURN_HOR_AZIMUTH_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_SATURN].earth_object_distance - expected_output[8])) <= SATURN_EARTH_DIST_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_SATURN].angular_size - expected_output[9])) <= SATURN_ANGULAR_SIZE_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_SATURN].light_travel_time - expected_output[10])) <= SATURN_LIGHT_TRAVEL_TOL )
    results_check++;	
    
  if ( abs((objects[OBJECT_ID_SATURN].sun_object_distance - expected_output[11])) <= SATURN_SUN_DIST_TOL )
    results_check++;	
		        
  if ( abs((objects[OBJECT_ID_SATURN].phase - expected_output[12])) <= SATURN_PHASE_TOL )
    results_check++;   
    		    
  if ( abs((objects[OBJECT_ID_SATURN].magnitude - expected_output[13])) <= SATURN_MAG_TOL )
    results_check++;     
		    
  if ( abs((objects[OBJECT_ID_SATURN].azimuth_rise - expected_output[14])) <= SATURN_AZIMUTH_RISE_TOL )
    results_check++;     
		  
  if ( abs((objects[OBJECT_ID_SATURN].azimuth_set - expected_output[15])) <= SATURN_AZIMUTH_SET_TOL )
    results_check++;    
    		  
  if ( abs((objects[OBJECT_ID_SATURN].rise_time - expected_output[16])) <= SATURN_RISE_TIME_TOL )
    results_check++;     
    		  
  if ( abs((objects[OBJECT_ID_SATURN].transit_time - expected_output[17])) <= SATURN_TRANSIT_TIME_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_SATURN].set_time - expected_output[18])) <= SATURN_SET_TIME_TOL )
    results_check++;     
    			
  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_007_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Saturn actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Saturn actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Saturn actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Saturn actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Saturn RA                             = " << expected_output[4] << endl;
  cout << "Saturn DEC                            = " << expected_output[5] << endl;	
  cout << "Saturn hor_altitude                   = " << expected_output[6] << endl;
  cout << "Saturn hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Saturn Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Saturn angular size                   = " << expected_output[9] << endl;
  cout << "Saturn light travel time              = " << expected_output[10] << endl;
  cout << "Saturn Sun-object distance            = " << expected_output[11] << endl;
  cout << "Saturn phase                          = " << expected_output[12] << endl;
  cout << "Saturn magnitude                      = " << expected_output[13] << endl;
  cout << "Saturn azimuth rise                   = " << expected_output[14] << endl;
  cout << "Saturn azimuth set                    = " << expected_output[15] << endl;
  cout << "Saturn rise time                      = " << expected_output[16] << endl;
  cout << "Saturn transit time                   = " << expected_output[17] << endl;
  cout << "Saturn set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Saturn actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_SATURN].actual_geo_ecliptic_lambda << endl;
  cout << "Saturn actual geo ecliptic beta       = " << objects[OBJECT_ID_SATURN].actual_geo_ecliptic_beta << endl; 
  cout << "Saturn actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_SATURN].actual_helio_ecliptic_lambda << endl;
  cout << "Saturn actual helio ecliptic beta     = " << objects[OBJECT_ID_SATURN].actual_helio_ecliptic_beta << endl;
  cout << "Saturn RA                             = " << objects[OBJECT_ID_SATURN].equ_ra << endl;
  cout << "Saturn DEC                            = " << objects[OBJECT_ID_SATURN].equ_dec << endl;	
  cout << "Saturn hor_altitude                   = " << objects[OBJECT_ID_SATURN].hor_altitude << endl;
  cout << "Saturn hor_azimuth                    = " << objects[OBJECT_ID_SATURN].hor_azimuth << endl;		
  cout << "Saturn Sun-Earth distance             = " << objects[OBJECT_ID_SATURN].earth_object_distance  << endl;
  cout << "Saturn angular size                   = " << objects[OBJECT_ID_SATURN].angular_size << endl;
  cout << "Saturn light travel time              = " << objects[OBJECT_ID_SATURN].light_travel_time << endl;
  cout << "Saturn Sun-object distance            = " << objects[OBJECT_ID_SATURN].sun_object_distance << endl;
  cout << "Saturn phase                          = " << objects[OBJECT_ID_SATURN].phase << endl;
  cout << "Saturn magnitude                      = " << objects[OBJECT_ID_SATURN].magnitude << endl;
  cout << "Saturn azimuth rise                   = " << objects[OBJECT_ID_SATURN].azimuth_rise << endl;
  cout << "Saturn azimuth set                    = " << objects[OBJECT_ID_SATURN].azimuth_set << endl;
  cout << "Saturn rise time                      = " << objects[OBJECT_ID_SATURN].rise_time << endl;
  cout << "Saturn transit time                   = " << objects[OBJECT_ID_SATURN].transit_time << endl;
  cout << "Saturn set time                       = " << objects[OBJECT_ID_SATURN].set_time << endl;
  cout << "Results                               = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	008		000			0000	Uranus
// Check Uranus details 19
BOOST_AUTO_TEST_CASE( TestJunit002_008_000_0000 )    
{
  // Uranus on 22nd Nov 1988 00:00:00 at 51.5N and 0.0W
  // Expected results from:
  // https://ssd.jpl.nasa.gov/horizons/app.html#/
  // www.heavens-above.com
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;

  expected_output[0] =   269.4010474;				// geo_ecliptic_lambda
  expected_output[1] =    -0.2147710;				// geo_ecliptic_beta
  expected_output[2] =   271.0032;				// helio_ecliptic_lambda
  expected_output[3] =    -0.2256;				// helio_ecliptic_beta 
  expected_output[4] =  17 + (58.0/60.0) + ( 4.75/3600.0);	// RA Astrometric
  expected_output[5] = -23 - (39.0/60.0) - (17.10/3600.0);	// DEC Astrometric
  expected_output[6] =  -54.764330;                             // hor_altitude
  expected_output[7] =  311.497608;                             // hor_azimuth
  expected_output[8] =    20.1610316672123;			// Object-Earth distance
  expected_output[9] =    3.495915;                             // angular size
  expected_output[10] =    10060.4512488;			// light travel time
  expected_output[11] =    19.30752016669;			// Sun-object distance
  expected_output[12] =    1.0;                                 // phase
  expected_output[13] =    5.778;                               // magnitude
  expected_output[14] =    130.1;				// azimuth rise 
  expected_output[15] =    229.9;				// azimuth set
  expected_output[16] =    2447487.92014;			// rise time 
  expected_output[17] =    2447488.07708;			// transit time 
  expected_output[18] =    2447488.23403;			// set time 
   
  objects = api.object_details(2447487.50000,0.0,51.5);
						
  // Check that the answer is within the tolerance.
  if ( abs((objects[OBJECT_ID_URANUS].actual_geo_ecliptic_lambda - expected_output[0])) <= URANUS_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_URANUS].actual_geo_ecliptic_beta - expected_output[1])) <= URANUS_GEO_ECL_BETA_TOL )
    results_check++;
	
  if ( abs((objects[OBJECT_ID_URANUS].actual_helio_ecliptic_lambda - expected_output[2])) <= URANUS_HELIO_ECL_LAMBDA_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_URANUS].actual_helio_ecliptic_beta - expected_output[3])) <= URANUS_HELIO_ECL_BETA_TOL )
    results_check++;			
		
  if ( abs((objects[OBJECT_ID_URANUS].equ_ra - expected_output[4])) <= URANUS_EQU_RA_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_URANUS].equ_dec - expected_output[5])) <= URANUS_EQU_DEC_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_URANUS].hor_altitude - expected_output[6])) <= URANUS_HOR_ALTITUDE_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_URANUS].hor_azimuth - expected_output[7])) <= URANUS_HOR_AZIMUTH_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_URANUS].earth_object_distance - expected_output[8])) <= URANUS_EARTH_DIST_TOL )
    results_check++;	
    		
  if ( abs((objects[OBJECT_ID_URANUS].angular_size - expected_output[9])) <= URANUS_ANGULAR_SIZE_TOL )
    results_check++;	
    		  
  if ( abs((objects[OBJECT_ID_URANUS].light_travel_time - expected_output[10])) <= URANUS_LIGHT_TRAVEL_TOL )
    results_check++;	
   
  if ( abs((objects[OBJECT_ID_URANUS].sun_object_distance - expected_output[11])) <= URANUS_SUN_DIST_TOL )
    results_check++;	
		        
  if ( abs((objects[OBJECT_ID_URANUS].phase - expected_output[12])) <= URANUS_PHASE_TOL )
    results_check++;   
    		    
  if ( abs((objects[OBJECT_ID_URANUS].magnitude - expected_output[13])) <= URANUS_MAG_TOL )
    results_check++;     
		    
  if ( abs((objects[OBJECT_ID_URANUS].azimuth_rise - expected_output[14])) <= URANUS_AZIMUTH_RISE_TOL )
    results_check++;     
		  
  if ( abs((objects[OBJECT_ID_URANUS].azimuth_set - expected_output[15])) <= URANUS_AZIMUTH_SET_TOL )
    results_check++;    
     		  
  if ( abs((objects[OBJECT_ID_URANUS].rise_time - expected_output[16])) <= URANUS_RISE_TIME_TOL )
    results_check++;     
  		  
  if ( abs((objects[OBJECT_ID_URANUS].transit_time - expected_output[17])) <= URANUS_TRANSIT_TIME_TOL )
    results_check++;     
  		  
  if ( abs((objects[OBJECT_ID_URANUS].set_time - expected_output[18])) <= URANUS_SET_TIME_TOL )
    results_check++;     
   			
  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_008_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Uranus actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Uranus actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Uranus actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Uranus actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Uranus RA                             = " << expected_output[4] << endl;
  cout << "Uranus DEC                            = " << expected_output[5] << endl;	
  cout << "Uranus hor_altitude                   = " << expected_output[6] << endl;
  cout << "Uranus hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Uranus Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Uranus angular size                   = " << expected_output[9] << endl;
  cout << "Uranus light travel time              = " << expected_output[10] << endl;
  cout << "Uranus Sun-object distance            = " << expected_output[11] << endl;
  cout << "Uranus phase                          = " << expected_output[12] << endl;
  cout << "Uranus magnitude                      = " << expected_output[13] << endl;
  cout << "Uranus azimuth rise                   = " << expected_output[14] << endl;
  cout << "Uranus azimuth set                    = " << expected_output[15] << endl;
  cout << "Uranus rise time                      = " << expected_output[16] << endl;
  cout << "Uranus transit time                   = " << expected_output[17] << endl;
  cout << "Uranus set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Uranus actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_URANUS].actual_geo_ecliptic_lambda << endl;
  cout << "Uranus actual geo ecliptic beta       = " << objects[OBJECT_ID_URANUS].actual_geo_ecliptic_beta << endl; 
  cout << "Uranus actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_URANUS].actual_helio_ecliptic_lambda << endl;
  cout << "Uranus actual helio ecliptic beta     = " << objects[OBJECT_ID_URANUS].actual_helio_ecliptic_beta << endl;
  cout << "Uranus RA                             = " << objects[OBJECT_ID_URANUS].equ_ra << endl;
  cout << "Uranus DEC                            = " << objects[OBJECT_ID_URANUS].equ_dec << endl;	
  cout << "Uranus hor_altitude                   = " << objects[OBJECT_ID_URANUS].hor_altitude << endl;
  cout << "Uranus hor_azimuth                    = " << objects[OBJECT_ID_URANUS].hor_azimuth << endl;		
  cout << "Uranus Sun-Earth distance             = " << objects[OBJECT_ID_URANUS].earth_object_distance  << endl;
  cout << "Uranus angular size                   = " << objects[OBJECT_ID_URANUS].angular_size << endl;
  cout << "Uranus light travel time              = " << objects[OBJECT_ID_URANUS].light_travel_time << endl;
  cout << "Uranus Sun-object distance            = " << objects[OBJECT_ID_URANUS].sun_object_distance << endl;
  cout << "Uranus phase                          = " << objects[OBJECT_ID_URANUS].phase << endl;
  cout << "Uranus magnitude                      = " << objects[OBJECT_ID_URANUS].magnitude << endl;
  cout << "Uranus azimuth rise                   = " << objects[OBJECT_ID_URANUS].azimuth_rise << endl;
  cout << "Uranus azimuth set                    = " << objects[OBJECT_ID_URANUS].azimuth_set << endl;
  cout << "Uranus rise time                      = " << objects[OBJECT_ID_URANUS].rise_time << endl;
  cout << "Uranus transit time                   = " << objects[OBJECT_ID_URANUS].transit_time << endl;
  cout << "Uranus set time                       = " << objects[OBJECT_ID_URANUS].set_time << endl;
  cout << "Results                               = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	009		000			0000	Neptune
// Check Neptune details 20
BOOST_AUTO_TEST_CASE( TestJunit002_009_000_0000 )    
{
  // Neptune on 22nd Nov 1988 00:00:00 at 51.5N and 0.0W
  // Expected results from:
  // https://ssd.jpl.nasa.gov/horizons/app.html#/
  // www.heavens-above.com
  api_interface api;
  struct astronomical_object *objects;
  double expected_output[19];
  int results_check = 0;

  expected_output[0] =  278.4957178;				// geo_ecliptic_lambda
  expected_output[1] =    0.9154884;				// geo_ecliptic_beta
  expected_output[2] =  279.8224;				// helio_ecliptic_lambda
  expected_output[3] =    0.9373;				// helio_ecliptic_beta 
  expected_output[4] =  18 + (37.0/60.0) + (25.19/3600.0);	// RA Astrometric
  expected_output[5] = -22 - (14.0/60.0) - (40.80/3600.0);	// DEC Astrometric
  expected_output[6] =  -48.634030;                             // hor_altitude
  expected_output[7] =  300.465549;                             // hor_azimuth
  expected_output[8] =   30.9861910181169;			// Object-Earth distance
  expected_output[9] =    2.203851;                             // angular size
  expected_output[10] =   15462.2575512;			// light travel time
  expected_output[11] =    30.22058631469;			// Sun-object distance
  expected_output[12] =    1.0;                                 // phase
  expected_output[13] =    7.919;                               // magnitude
  expected_output[14] =    127.5;				// azimuth rise 
  expected_output[15] =    232.6;				// azimuth set
  expected_output[16] =    2447487.94097;			// rise time 
  expected_output[17] =    2447488.10417;			// transit time 
  expected_output[18] =    2447488.26806;			// set time 

  objects = api.object_details(2447487.50000,0.0,51.5);
						
  // Check that the answer is within the tolerance. 
  if ( abs((objects[OBJECT_ID_NEPTUNE].actual_geo_ecliptic_lambda - expected_output[0])) <= NEPTUNE_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((objects[OBJECT_ID_NEPTUNE].actual_geo_ecliptic_beta - expected_output[1])) <= NEPTUNE_GEO_ECL_BETA_TOL )
    results_check++;
	
  if ( abs((objects[OBJECT_ID_NEPTUNE].actual_helio_ecliptic_lambda - expected_output[2])) <= NEPTUNE_HELIO_ECL_LAMBDA_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_NEPTUNE].actual_helio_ecliptic_beta - expected_output[3])) <= NEPTUNE_HELIO_ECL_BETA_TOL )
    results_check++;			
		
  if ( abs((objects[OBJECT_ID_NEPTUNE].equ_ra - expected_output[4])) <= NEPTUNE_EQU_RA_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_NEPTUNE].equ_dec - expected_output[5])) <= NEPTUNE_EQU_DEC_TOL )
    results_check++;	
	
  if ( abs((objects[OBJECT_ID_NEPTUNE].hor_altitude - expected_output[6])) <= NEPTUNE_HOR_ALTITUDE_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_NEPTUNE].hor_azimuth - expected_output[7])) <= NEPTUNE_HOR_AZIMUTH_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_NEPTUNE].earth_object_distance - expected_output[8])) <= NEPTUNE_EARTH_DIST_TOL )
    results_check++;	
		
  if ( abs((objects[OBJECT_ID_NEPTUNE].angular_size - expected_output[9])) <= NEPTUNE_ANGULAR_SIZE_TOL )
    results_check++;	

  if ( abs((objects[OBJECT_ID_NEPTUNE].light_travel_time - expected_output[10])) <= NEPTUNE_LIGHT_TRAVEL_TOL )
    results_check++;	
   
  if ( abs((objects[OBJECT_ID_NEPTUNE].sun_object_distance - expected_output[11])) <= NEPTUNE_SUN_DIST_TOL )
    results_check++;	
		        
  if ( abs((objects[OBJECT_ID_NEPTUNE].phase - expected_output[12])) <= NEPTUNE_PHASE_TOL )
    results_check++;   

  if ( abs((objects[OBJECT_ID_NEPTUNE].magnitude - expected_output[13])) <= NEPTUNE_MAG_TOL )
    results_check++;     
		    
  if ( abs((objects[OBJECT_ID_NEPTUNE].azimuth_rise - expected_output[14])) <= NEPTUNE_AZIMUTH_RISE_TOL )
    results_check++;     
		  
  if ( abs((objects[OBJECT_ID_NEPTUNE].azimuth_set - expected_output[15])) <= NEPTUNE_AZIMUTH_SET_TOL )
    results_check++;    
     		  
  if ( abs((objects[OBJECT_ID_NEPTUNE].rise_time - expected_output[16])) <= NEPTUNE_RISE_TIME_TOL )
    results_check++;     

  if ( abs((objects[OBJECT_ID_NEPTUNE].transit_time - expected_output[17])) <= NEPTUNE_TRANSIT_TIME_TOL )
    results_check++;     
  		  
  if ( abs((objects[OBJECT_ID_NEPTUNE].set_time - expected_output[18])) <= NEPTUNE_SET_TIME_TOL )
    results_check++;     

  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_009_000_0000" << endl;  
  cout << "Expected:" << endl;
  cout << "Neptune actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Neptune actual geo ecliptic beta       = " << expected_output[1] << endl; 
  cout << "Neptune actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Neptune actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Neptune RA                             = " << expected_output[4] << endl;
  cout << "Neptune DEC                            = " << expected_output[5] << endl;	
  cout << "Neptune hor_altitude                   = " << expected_output[6] << endl;
  cout << "Neptune hor_azimuth                    = " << expected_output[7] << endl;		
  cout << "Neptune Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Neptune angular size                   = " << expected_output[9] << endl;
  cout << "Neptune light travel time              = " << expected_output[10] << endl;
  cout << "Neptune Sun-object distance            = " << expected_output[11] << endl;
  cout << "Neptune phase                          = " << expected_output[12] << endl;
  cout << "Neptune magnitude                      = " << expected_output[13] << endl;
  cout << "Neptune azimuth rise                   = " << expected_output[14] << endl;
  cout << "Neptune azimuth set                    = " << expected_output[15] << endl;
  cout << "Neptune rise time                      = " << expected_output[16] << endl;
  cout << "Neptune transit time                   = " << expected_output[17] << endl;
  cout << "Neptune set time                       = " << expected_output[18] << endl;  
  cout << "Calculated:" << endl;
  cout << "Neptune actual_geo_ecliptic_lambda     = " << objects[OBJECT_ID_NEPTUNE].actual_geo_ecliptic_lambda << endl;
  cout << "Neptune actual geo ecliptic beta       = " << objects[OBJECT_ID_NEPTUNE].actual_geo_ecliptic_beta << endl; 
  cout << "Neptune actual_helio_ecliptic_lambda   = " << objects[OBJECT_ID_NEPTUNE].actual_helio_ecliptic_lambda << endl;
  cout << "Neptune actual helio ecliptic beta     = " << objects[OBJECT_ID_NEPTUNE].actual_helio_ecliptic_beta << endl;
  cout << "Neptune RA                             = " << objects[OBJECT_ID_NEPTUNE].equ_ra << endl;
  cout << "Neptune DEC                            = " << objects[OBJECT_ID_NEPTUNE].equ_dec << endl;	
  cout << "Neptune hor_altitude                   = " << objects[OBJECT_ID_NEPTUNE].hor_altitude << endl;
  cout << "Neptune hor_azimuth                    = " << objects[OBJECT_ID_NEPTUNE].hor_azimuth << endl;		
  cout << "Neptune Sun-Earth distance             = " << objects[OBJECT_ID_NEPTUNE].earth_object_distance  << endl;
  cout << "Neptune angular size                   = " << objects[OBJECT_ID_NEPTUNE].angular_size << endl;
  cout << "Neptune light travel time              = " << objects[OBJECT_ID_NEPTUNE].light_travel_time << endl;
  cout << "Neptune Sun-object distance            = " << objects[OBJECT_ID_NEPTUNE].sun_object_distance << endl;
  cout << "Neptune phase                          = " << objects[OBJECT_ID_NEPTUNE].phase << endl;
  cout << "Neptune magnitude                      = " << objects[OBJECT_ID_NEPTUNE].magnitude << endl;
  cout << "Neptune azimuth rise                   = " << objects[OBJECT_ID_NEPTUNE].azimuth_rise << endl;
  cout << "Neptune azimuth set                    = " << objects[OBJECT_ID_NEPTUNE].azimuth_set << endl;
  cout << "Neptune rise time                      = " << objects[OBJECT_ID_NEPTUNE].rise_time << endl;
  cout << "Neptune transit time                   = " << objects[OBJECT_ID_NEPTUNE].transit_time << endl;
  cout << "Neptune set time                       = " << objects[OBJECT_ID_NEPTUNE].set_time << endl;
  cout << "Results                                = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 19);			
}

//002	011		000			0001	Comet - periodic
// Perodic comet (non-Julian)
BOOST_AUTO_TEST_CASE( TestJunit002_011_000_0001 )
{
  // Expected results from:
  // Example from
  api_interface api;
  struct astronomical_object object;
  double expected_output[19];
  double orbit_params[7];
  int results_check = 0;

  expected_output[0]  = 156.7486;				// geo_ecliptic_lambda
  expected_output[1]  =   1.1067;				// geo_ecliptic_beta
  expected_output[2]  = 182.6507;				// helio_ecliptic_lambda
  expected_output[3]  =   1.1346;                               // helio_ecliptic_beta
  expected_output[4]  =   10 + (34.0/60.0) + (26.41/3600.0);	// RA Astrometric
  expected_output[5]  =  10 + (10.0/60.0) + (32.70/3600.0);	// DEC Astrometric
  expected_output[6]  =  18.10; 				// hor_altitude
  expected_output[7]  =  263.0; 				// hor_azimuth
  expected_output[8]  =    2.264;       			// Object-Earth distance
  expected_output[9]  = nan("");            			// angular size
  expected_output[10] =  1127.472;				// light travel time
  expected_output[11] =     2.209;      			// Sun-object distance
  expected_output[12] =     1.00;				// phase
  expected_output[13] =    12.04;				// magnitude
  expected_output[14] =    73.0;				// azimuth rise
  expected_output[15] =   286.0;				// azimuth set
  expected_output[16] =    2459743.92639;			// rise time
  expected_output[17] =    2459744.21944;			// transit time
  expected_output[18] =    2459744.49826;			// set time


  // Test the new comet position code.
  // Comet 116P/Wild 4 2022/06/13 22:00 51.5N 0.0W
  //
  //    Field	     Content					         Units			Symbol
  //    =====      =======       				         =====			======
  //	    0        Period 					    (mean Solar years)             T
  // 	    1        Epoch of periastron							   t
  // 	    2	     Longitude of periastron				 	  	           w
  // 	    3        Eccentricity								   e
  // 	    4        Semi-major axis of orbit 		            (arcsec)		           a
  // 	    5        Inclination of orbit 			    (degrees)		           i
  //	    6        Position angle of ascending node 	            (degrees)		           o
  cout << "Comet - periodic - year,months, etc - Comet 116P/Wild 4 2022/06/13 22:00 51.5N 0.0W" << endl;
  orbit_params[0] = 6.5048;
  orbit_params[1] = 2016.029501913;
  orbit_params[2] = 194.414095976; // (peri + node)
  orbit_params[3] = 0.37266174;
  orbit_params[4] = 3.48457297;
  orbit_params[5] = 3.60741312;
  orbit_params[6] = 21.014489640779;

  object = api.comet_position_perodic(&orbit_params[0],
                                      2022,
                                      6,
                                      13,
                                      22,
                                      0,
                                      0.0,
                                      0.0,
                                      0.0,
                                      51.5,
                                      5.60,
                                      5.36);

  // Check that the answer is within the tolerance.
  if ( abs((object.actual_geo_ecliptic_lambda - expected_output[0])) <= COMET_PERIODIC_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((object.actual_geo_ecliptic_beta - expected_output[1])) <= COMET_PERIODIC_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((object.actual_helio_ecliptic_lambda - expected_output[2])) <= COMET_PERIODIC_HELIO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((object.actual_helio_ecliptic_beta - expected_output[3])) <= COMET_PERIODIC_HELIO_ECL_BETA_TOL )
    results_check++;

  if ( abs((object.equ_ra - expected_output[4])) <= COMET_PERIODIC_EQU_RA_TOL )
    results_check++;

  if ( abs((object.equ_dec - expected_output[5])) <= COMET_PERIODIC_EQU_DEC_TOL )
    results_check++;

  if ( abs((object.hor_altitude - expected_output[6])) <= COMET_PERIODIC_HOR_ALTITUDE_TOL )
    results_check++;

  if ( abs((object.hor_azimuth - expected_output[7])) <= COMET_PERIODIC_HOR_AZIMUTH_TOL )
    results_check++;

  if ( abs((object.earth_object_distance - expected_output[8])) <= COMET_PERIODIC_EARTH_DIST_TOL )
    results_check++;

  //if ( abs((object.angular_size - expected_output[9])) <= COMET_PERIODIC_ANGULAR_SIZE_TOL )
  if(isnan(object.angular_size))
    results_check++;

  if ( abs((object.light_travel_time - expected_output[10])) <= COMET_PERIODIC_LIGHT_TRAVEL_TOL )
    results_check++;

  if ( abs((object.sun_object_distance - expected_output[11])) <= COMET_PERIODIC_SUN_DIST_TOL )
    results_check++;

  if ( abs((object.phase - expected_output[12])) <= COMET_PERIODIC_PHASE_TOL )
    results_check++;

  if ( abs((object.magnitude - expected_output[13])) <= COMET_PERIODIC_MAG_TOL )
    results_check++;

  if ( abs((object.azimuth_rise - expected_output[14])) <= COMET_PERIODIC_AZIMUTH_RISE_TOL )
    results_check++;

  if ( abs((object.azimuth_set - expected_output[15])) <= COMET_PERIODIC_AZIMUTH_SET_TOL )
    results_check++;

  if ( abs((object.rise_time - expected_output[16])) <= COMET_PERIODIC_RISE_TIME_TOL )
    results_check++;

  if ( abs((object.transit_time - expected_output[17])) <= COMET_PERIODIC_TRANSIT_TIME_TOL )
    results_check++;

  if ( abs((object.set_time - expected_output[18])) <= COMET_PERIODIC_SET_TIME_TOL )
    results_check++;

  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_011_000_0001" << endl;
  cout << "Expected:" << endl;
  cout << "Comet periodic actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Comet periodic actual geo ecliptic beta       = " << expected_output[1] << endl;
  cout << "Comet periodic actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Comet periodic actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Comet periodic RA                             = " << expected_output[4] << endl;
  cout << "Comet periodic DEC                            = " << expected_output[5] << endl;
  cout << "Comet periodic hor_altitude                   = " << expected_output[6] << endl;
  cout << "Comet periodic hor_azimuth                    = " << expected_output[7] << endl;
  cout << "Comet periodic Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Comet periodic angular size                   = " << expected_output[9] << endl;
  cout << "Comet periodic light travel time              = " << expected_output[10] << endl;
  cout << "Comet periodic Sun-object distance            = " << expected_output[11] << endl;
  cout << "Comet periodic phase                          = " << expected_output[12] << endl;
  cout << "Comet periodic magnitude                      = " << expected_output[13] << endl;
  cout << "Comet periodic azimuth rise                   = " << expected_output[14] << endl;
  cout << "Comet periodic azimuth set                    = " << expected_output[15] << endl;
  cout << "Comet periodic rise time                      = " << expected_output[16] << endl;
  cout << "Comet periodic transit time                   = " << expected_output[17] << endl;
  cout << "Comet periodic set time                       = " << expected_output[18] << endl;
  cout << "Calculated:" << endl;
  cout << "Comet periodic actual_geo_ecliptic_lambda     = " << object.actual_geo_ecliptic_lambda << endl;
  cout << "Comet periodic actual geo ecliptic beta       = " << object.actual_geo_ecliptic_beta << endl;
  cout << "Comet periodic actual_helio_ecliptic_lambda   = " << object.actual_helio_ecliptic_lambda << endl;
  cout << "Comet periodic actual helio ecliptic beta     = " << object.actual_helio_ecliptic_beta << endl;
  cout << "Comet periodic RA                             = " << object.equ_ra << endl;
  cout << "Comet periodic DEC                            = " << object.equ_dec << endl;
  cout << "Comet periodic hor_altitude                   = " << object.hor_altitude << endl;
  cout << "Comet periodic hor_azimuth                    = " << object.hor_azimuth << endl;
  cout << "Comet periodic Sun-Earth distance             = " << object.earth_object_distance  << endl;
  cout << "Comet periodic angular size                   = " << object.angular_size << endl;
  cout << "Comet periodic light travel time              = " << object.light_travel_time << endl;
  cout << "Comet periodic Sun-object distance            = " << object.sun_object_distance << endl;
  cout << "Comet periodic phase                          = " << object.phase << endl;
  cout << "Comet periodic magnitude                      = " << object.magnitude << endl;
  cout << "Comet periodic azimuth rise                   = " << object.azimuth_rise << endl;
  cout << "Comet periodic azimuth set                    = " << object.azimuth_set << endl;
  cout << "Comet periodic rise time                      = " << object.rise_time << endl;
  cout << "Comet periodic transit time                   = " << object.transit_time << endl;
  cout << "Comet periodic set time                       = " << object.set_time << endl;
  cout << "Results                                       = " << results_check << endl;
  cout << endl;

  BOOST_CHECK(results_check == 19);
}

//002	011		000			0002	Comet - periodic
// Perodic comet (Julian)
BOOST_AUTO_TEST_CASE( TestJunit002_011_000_0002 )
{
  // Expected results from:
  // Example from
  api_interface api;
  struct astronomical_object object;
  double expected_output[19];
  double orbit_params[7];
  int results_check = 0;

  expected_output[0]  = 156.7486;				// geo_ecliptic_lambda
  expected_output[1]  =   1.1067;				// geo_ecliptic_beta
  expected_output[2]  = 182.6507;				// helio_ecliptic_lambda
  expected_output[3]  =   1.1346;                               // helio_ecliptic_beta
  expected_output[4]  =   10 + (34.0/60.0) + (26.41/3600.0);	// RA Astrometric
  expected_output[5]  =  10 + (10.0/60.0) + (32.70/3600.0);	// DEC Astrometric
  expected_output[6]  =  18.10; 				// hor_altitude
  expected_output[7]  =  263.0; 				// hor_azimuth
  expected_output[8]  =    2.264;       			// Object-Earth distance
  expected_output[9]  = nan("");            			// angular size
  expected_output[10] =  1127.472;				// light travel time
  expected_output[11] =     2.209;      			// Sun-object distance
  expected_output[12] =     1.00;				// phase
  expected_output[13] =    12.04;				// magnitude
  expected_output[14] =    73.0;				// azimuth rise
  expected_output[15] =   286.0;				// azimuth set
  expected_output[16] =    2459743.92639;			// rise time
  expected_output[17] =    2459744.21944;			// transit time
  expected_output[18] =    2459744.49826;			// set time


  // Test the new comet position code.
  // Comet 116P/Wild 4 2022/06/13 22:00 51.5N 0.0W
  //
  //    Field	     Content					         Units			Symbol
  //    =====      =======       				         =====			======
  //	    0        Period 					    (mean Solar years)             T
  // 	    1        Epoch of periastron							   t
  // 	    2	     Longitude of periastron				 	  	           w
  // 	    3        Eccentricity								   e
  // 	    4        Semi-major axis of orbit 		            (arcsec)		           a
  // 	    5        Inclination of orbit 			    (degrees)		           i
  //	    6        Position angle of ascending node 	            (degrees)		           o
  cout << "Comet - periodic - year,months, etc - Comet 116P/Wild 4 2022/06/13 22:00 51.5N 0.0W" << endl;
  orbit_params[0] = 6.5048;
  orbit_params[1] = 2016.029501913;
  orbit_params[2] = 194.414095976; // (peri + node)
  orbit_params[3] = 0.37266174;
  orbit_params[4] = 3.48457297;
  orbit_params[5] = 3.60741312;
  orbit_params[6] = 21.014489640779;

  object = api.comet_position_perodic(&orbit_params[0],
                                      2459744.41667,
                                      0.0,
                                      51.5,
                                      5.60,
                                      5.36);

  // Check that the answer is within the tolerance.
  if ( abs((object.actual_geo_ecliptic_lambda - expected_output[0])) <= COMET_PERIODIC_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((object.actual_geo_ecliptic_beta - expected_output[1])) <= COMET_PERIODIC_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((object.actual_helio_ecliptic_lambda - expected_output[2])) <= COMET_PERIODIC_HELIO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((object.actual_helio_ecliptic_beta - expected_output[3])) <= COMET_PERIODIC_HELIO_ECL_BETA_TOL )
    results_check++;

  if ( abs((object.equ_ra - expected_output[4])) <= COMET_PERIODIC_EQU_RA_TOL )
    results_check++;

  if ( abs((object.equ_dec - expected_output[5])) <= COMET_PERIODIC_EQU_DEC_TOL )
    results_check++;

  if ( abs((object.hor_altitude - expected_output[6])) <= COMET_PERIODIC_HOR_ALTITUDE_TOL )
    results_check++;

  if ( abs((object.hor_azimuth - expected_output[7])) <= COMET_PERIODIC_HOR_AZIMUTH_TOL )
    results_check++;

  if ( abs((object.earth_object_distance - expected_output[8])) <= COMET_PERIODIC_EARTH_DIST_TOL )
    results_check++;

  //if ( abs((object.angular_size - expected_output[9])) <= COMET_PERIODIC_ANGULAR_SIZE_TOL )
  if(isnan(object.angular_size))
    results_check++;

  if ( abs((object.light_travel_time - expected_output[10])) <= COMET_PERIODIC_LIGHT_TRAVEL_TOL )
    results_check++;

  if ( abs((object.sun_object_distance - expected_output[11])) <= COMET_PERIODIC_SUN_DIST_TOL )
    results_check++;

  if ( abs((object.phase - expected_output[12])) <= COMET_PERIODIC_PHASE_TOL )
    results_check++;

  if ( abs((object.magnitude - expected_output[13])) <= COMET_PERIODIC_MAG_TOL )
    results_check++;

  if ( abs((object.azimuth_rise - expected_output[14])) <= COMET_PERIODIC_AZIMUTH_RISE_TOL )
    results_check++;

  if ( abs((object.azimuth_set - expected_output[15])) <= COMET_PERIODIC_AZIMUTH_SET_TOL )
    results_check++;

  if ( abs((object.rise_time - expected_output[16])) <= COMET_PERIODIC_RISE_TIME_TOL )
    results_check++;

  if ( abs((object.transit_time - expected_output[17])) <= COMET_PERIODIC_TRANSIT_TIME_TOL )
    results_check++;

  if ( abs((object.set_time - expected_output[18])) <= COMET_PERIODIC_SET_TIME_TOL )
    results_check++;

  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_011_000_0002" << endl;
  cout << "Expected:" << endl;
  cout << "Comet periodic actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Comet periodic actual geo ecliptic beta       = " << expected_output[1] << endl;
  cout << "Comet periodic actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Comet periodic actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Comet periodic RA                             = " << expected_output[4] << endl;
  cout << "Comet periodic DEC                            = " << expected_output[5] << endl;
  cout << "Comet periodic hor_altitude                   = " << expected_output[6] << endl;
  cout << "Comet periodic hor_azimuth                    = " << expected_output[7] << endl;
  cout << "Comet periodic Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Comet periodic angular size                   = " << expected_output[9] << endl;
  cout << "Comet periodic light travel time              = " << expected_output[10] << endl;
  cout << "Comet periodic Sun-object distance            = " << expected_output[11] << endl;
  cout << "Comet periodic phase                          = " << expected_output[12] << endl;
  cout << "Comet periodic magnitude                      = " << expected_output[13] << endl;
  cout << "Comet periodic azimuth rise                   = " << expected_output[14] << endl;
  cout << "Comet periodic azimuth set                    = " << expected_output[15] << endl;
  cout << "Comet periodic rise time                      = " << expected_output[16] << endl;
  cout << "Comet periodic transit time                   = " << expected_output[17] << endl;
  cout << "Comet periodic set time                       = " << expected_output[18] << endl;
  cout << "Calculated:" << endl;
  cout << "Comet periodic actual_geo_ecliptic_lambda     = " << object.actual_geo_ecliptic_lambda << endl;
  cout << "Comet periodic actual geo ecliptic beta       = " << object.actual_geo_ecliptic_beta << endl;
  cout << "Comet periodic actual_helio_ecliptic_lambda   = " << object.actual_helio_ecliptic_lambda << endl;
  cout << "Comet periodic actual helio ecliptic beta     = " << object.actual_helio_ecliptic_beta << endl;
  cout << "Comet periodic RA                             = " << object.equ_ra << endl;
  cout << "Comet periodic DEC                            = " << object.equ_dec << endl;
  cout << "Comet periodic hor_altitude                   = " << object.hor_altitude << endl;
  cout << "Comet periodic hor_azimuth                    = " << object.hor_azimuth << endl;
  cout << "Comet periodic Sun-Earth distance             = " << object.earth_object_distance  << endl;
  cout << "Comet periodic angular size                   = " << object.angular_size << endl;
  cout << "Comet periodic light travel time              = " << object.light_travel_time << endl;
  cout << "Comet periodic Sun-object distance            = " << object.sun_object_distance << endl;
  cout << "Comet periodic phase                          = " << object.phase << endl;
  cout << "Comet periodic magnitude                      = " << object.magnitude << endl;
  cout << "Comet periodic azimuth rise                   = " << object.azimuth_rise << endl;
  cout << "Comet periodic azimuth set                    = " << object.azimuth_set << endl;
  cout << "Comet periodic rise time                      = " << object.rise_time << endl;
  cout << "Comet periodic transit time                   = " << object.transit_time << endl;
  cout << "Comet periodic set time                       = " << object.set_time << endl;
  cout << "Results                                       = " << results_check << endl;
  cout << endl;

  BOOST_CHECK(results_check == 19);
}


//002	012		000			0001	Comet - parabolic
// Parabolic comet (non-Julian)
BOOST_AUTO_TEST_CASE( TestJunit002_012_000_0001 )
{
  api_interface api;
  struct astronomical_object object;
  double expected_output[19];
  double parabolic_orbit_params[5];
  int results_check = 0;

  expected_output[0]  = 269.91226;				// geo_ecliptic_lambda
  expected_output[1]  =  30.2189;				// geo_ecliptic_beta
  expected_output[2]  = 267.3403;				// helio_ecliptic_lambda
  expected_output[3]  =  20.1351;                               // helio_ecliptic_beta
  expected_output[4]  =   17 + (58.0/60.0) + (35.64/3600.0);	// RA Astrometric
  expected_output[5]  =    6 + (47.0/60.0) + (00.10/3600.0);	// DEC Astrometric
  expected_output[6]  =   36.1; 				// hor_altitude
  expected_output[7]  =  133.0; 				// hor_azimuth
  expected_output[8]  =  1.98889;                               // Object-Earth distance
  expected_output[9]  = nan("");            			// angular size
  expected_output[10] =  990.46722;				// light travel time
  expected_output[11] =  2.908399;      			// Sun-object distance
  expected_output[12] =     1.00;				// phase
  expected_output[13] =  9.20;                                  // magnitude
  expected_output[14] =   79.0;                                 // azimuth rise
  expected_output[15] =  281.0;                                 // azimuth set
  expected_output[16] =   2459745.24444;			// rise time
  expected_output[17] =   2459745.51597;			// transit time
  expected_output[18] =   2459744.79479;			// set time

  // Comet C/2017 K2 (PANSTARRS) 2022/06/14 22:00
  parabolic_orbit_params[0] = 2459933.442190267776;	// 2022-Dec-19.94219027
  parabolic_orbit_params[1] = 1.799073955184896;
  parabolic_orbit_params[2] = 87.54383914154957;
  parabolic_orbit_params[3] = 236.1676054883491;
  parabolic_orbit_params[4] = 88.26338356498053;

  // Perihelion of Earth (closest distance between Earth and Sun) in that epoch:
  // 2022 Jan 4 06:52 (Julian date = 2459583.78611)

  object = api.comet_position_parabolic(&parabolic_orbit_params[0],
                                        2022,
                                        6,
                                        14,
                                        22,
                                        0,
                                        0.0,
                                        0.0,
                                        2459583.78611,
                                        0.0,
                                        51.5,
                                        4.80,
                                        2.48);

  // Check that the answer is within the tolerance.
  if ( abs((object.actual_geo_ecliptic_lambda - expected_output[0])) <= COMET_PARABOLIC_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((object.actual_geo_ecliptic_beta - expected_output[1])) <= COMET_PARABOLIC_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((object.actual_helio_ecliptic_lambda - expected_output[2])) <= COMET_PARABOLIC_HELIO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((object.actual_helio_ecliptic_beta - expected_output[3])) <= COMET_PARABOLIC_HELIO_ECL_BETA_TOL )
    results_check++;

  if ( abs((object.equ_ra - expected_output[4])) <= COMET_PARABOLIC_EQU_RA_TOL )
    results_check++;

  if ( abs((object.equ_dec - expected_output[5])) <= COMET_PARABOLIC_EQU_DEC_TOL )
    results_check++;

  if ( abs((object.hor_altitude - expected_output[6])) <= COMET_PARABOLIC_HOR_ALTITUDE_TOL )
    results_check++;

  if ( abs((object.hor_azimuth - expected_output[7])) <= COMET_PARABOLIC_HOR_AZIMUTH_TOL )
    results_check++;

  if ( abs((object.earth_object_distance - expected_output[8])) <= COMET_PARABOLIC_EARTH_DIST_TOL )
    results_check++;

  //if ( abs((object.angular_size - expected_output[9])) <= COMET_PARABOLIC_ANGULAR_SIZE_TOL )
  if(isnan(object.angular_size))
    results_check++;

  if ( abs((object.light_travel_time - expected_output[10])) <= COMET_PARABOLIC_LIGHT_TRAVEL_TOL )
    results_check++;

  if ( abs((object.sun_object_distance - expected_output[11])) <= COMET_PARABOLIC_SUN_DIST_TOL )
    results_check++;

  if ( abs((object.phase - expected_output[12])) <= COMET_PARABOLIC_PHASE_TOL )
    results_check++;

  if ( abs((object.magnitude - expected_output[13])) <= COMET_PARABOLIC_MAG_TOL )
    results_check++;

  if ( abs((object.azimuth_rise - expected_output[14])) <= COMET_PARABOLIC_AZIMUTH_RISE_TOL )
    results_check++;

  if ( abs((object.azimuth_set - expected_output[15])) <= COMET_PARABOLIC_AZIMUTH_SET_TOL )
    results_check++;

  if ( abs((object.rise_time - expected_output[16])) <= COMET_PARABOLIC_RISE_TIME_TOL )
    results_check++;

  if ( abs((object.transit_time - expected_output[17])) <= COMET_PARABOLIC_TRANSIT_TIME_TOL )
    results_check++;

  if ( abs((object.set_time - expected_output[18])) <= COMET_PARABOLIC_SET_TIME_TOL )
    results_check++;

  // These lines are used for diagnostic reasons.
  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_012_000_0001" << endl;
  cout << "Expected:" << endl;
  cout << "Comet parabolic actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Comet parabolic actual geo ecliptic beta       = " << expected_output[1] << endl;
  cout << "Comet parabolic actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Comet parabolic actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Comet parabolic RA                             = " << expected_output[4] << endl;
  cout << "Comet parabolic DEC                            = " << expected_output[5] << endl;
  cout << "Comet parabolic hor_altitude                   = " << expected_output[6] << endl;
  cout << "Comet parabolic hor_azimuth                    = " << expected_output[7] << endl;
  cout << "Comet parabolic Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Comet parabolic angular size                   = " << expected_output[9] << endl;
  cout << "Comet parabolic light travel time              = " << expected_output[10] << endl;
  cout << "Comet parabolic Sun-object distance            = " << expected_output[11] << endl;
  cout << "Comet parabolic phase                          = " << expected_output[12] << endl;
  cout << "Comet parabolic magnitude                      = " << expected_output[13] << endl;
  cout << "Comet parabolic azimuth rise                   = " << expected_output[14] << endl;
  cout << "Comet parabolic azimuth set                    = " << expected_output[15] << endl;
  cout << "Comet parabolic rise time                      = " << expected_output[16] << endl;
  cout << "Comet parabolic transit time                   = " << expected_output[17] << endl;
  cout << "Comet parabolic set time                       = " << expected_output[18] << endl;
  cout << "Calculated:" << endl;
  cout << "Comet parabolic actual_geo_ecliptic_lambda     = " << object.actual_geo_ecliptic_lambda << endl;
  cout << "Comet parabolic actual geo ecliptic beta       = " << object.actual_geo_ecliptic_beta << endl;
  cout << "Comet parabolic actual_helio_ecliptic_lambda   = " << object.actual_helio_ecliptic_lambda << endl;
  cout << "Comet parabolic actual helio ecliptic beta     = " << object.actual_helio_ecliptic_beta << endl;
  cout << "Comet parabolic RA                             = " << object.equ_ra << endl;
  cout << "Comet parabolic DEC                            = " << object.equ_dec << endl;
  cout << "Comet parabolic hor_altitude                   = " << object.hor_altitude << endl;
  cout << "Comet parabolic hor_azimuth                    = " << object.hor_azimuth << endl;
  cout << "Comet parabolic Sun-Earth distance             = " << object.earth_object_distance  << endl;
  cout << "Comet parabolic angular size                   = " << object.angular_size << endl;
  cout << "Comet parabolic light travel time              = " << object.light_travel_time << endl;
  cout << "Comet parabolic Sun-object distance            = " << object.sun_object_distance << endl;
  cout << "Comet parabolic phase                          = " << object.phase << endl;
  cout << "Comet parabolic magnitude                      = " << object.magnitude << endl;
  cout << "Comet parabolic azimuth rise                   = " << object.azimuth_rise << endl;
  cout << "Comet parabolic azimuth set                    = " << object.azimuth_set << endl;
  cout << "Comet parabolic rise time                      = " << object.rise_time << endl;
  cout << "Comet parabolic transit time                   = " << object.transit_time << endl;
  cout << "Comet parabolic set time                       = " << object.set_time << endl;
  cout << "Results                                        = " << results_check << endl;
  cout << endl;

  BOOST_CHECK(results_check == 19);
}

//002	012		000			0002	Comet - parabolic
// Parabolic comet (Julian)
BOOST_AUTO_TEST_CASE( TestJunit002_012_000_0002 )
{
  api_interface api;
  struct astronomical_object object;
  double expected_output[19];
  double parabolic_orbit_params[5];
  int results_check = 0;

  expected_output[0]  = 269.91226;				// geo_ecliptic_lambda
  expected_output[1]  =  30.2189;				// geo_ecliptic_beta
  expected_output[2]  = 267.3403;				// helio_ecliptic_lambda
  expected_output[3]  =  20.1351;                               // helio_ecliptic_beta
  expected_output[4]  =   17 + (58.0/60.0) + (35.64/3600.0);	// RA Astrometric
  expected_output[5]  =    6 + (47.0/60.0) + (00.10/3600.0);	// DEC Astrometric
  expected_output[6]  =   36.1; 				// hor_altitude
  expected_output[7]  =  133.0; 				// hor_azimuth
  expected_output[8]  =  1.98889;                               // Object-Earth distance
  expected_output[9]  = nan("");            			// angular size
  expected_output[10] =  990.46722;				// light travel time
  expected_output[11] =  2.908399;      			// Sun-object distance
  expected_output[12] =     1.00;				// phase
  expected_output[13] =  9.20;                                  // magnitude
  expected_output[14] =   79.0;                                 // azimuth rise
  expected_output[15] =  281.0;                                 // azimuth set
  expected_output[16] =   2459745.24444;			// rise time
  expected_output[17] =   2459745.51597;			// transit time
  expected_output[18] =   2459744.79479;			// set time

  // Comet C/2017 K2 (PANSTARRS) 2022/06/14 22:00
  parabolic_orbit_params[0] = 2459933.442190267776;	// 2022-Dec-19.94219027
  parabolic_orbit_params[1] = 1.799073955184896;
  parabolic_orbit_params[2] = 87.54383914154957;
  parabolic_orbit_params[3] = 236.1676054883491;
  parabolic_orbit_params[4] = 88.26338356498053;

  // Perihelion of Earth (closest distance between Earth and Sun) in that epoch:
  // 2022 Jan 4 06:52 (Julian date = 2459583.78611)

  object = api.comet_position_parabolic(&parabolic_orbit_params[0],
                                        2459745.41667,
                                        2459583.78611,
                                        0.0,
                                        51.5,
                                        4.80,
                                        2.48);

  // Check that the answer is within the tolerance.
  if ( abs((object.actual_geo_ecliptic_lambda - expected_output[0])) <= COMET_PARABOLIC_GEO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((object.actual_geo_ecliptic_beta - expected_output[1])) <= COMET_PARABOLIC_GEO_ECL_BETA_TOL )
    results_check++;

  if ( abs((object.actual_helio_ecliptic_lambda - expected_output[2])) <= COMET_PARABOLIC_HELIO_ECL_LAMBDA_TOL )
    results_check++;

  if ( abs((object.actual_helio_ecliptic_beta - expected_output[3])) <= COMET_PARABOLIC_HELIO_ECL_BETA_TOL )
    results_check++;

  if ( abs((object.equ_ra - expected_output[4])) <= COMET_PARABOLIC_EQU_RA_TOL )
    results_check++;

  if ( abs((object.equ_dec - expected_output[5])) <= COMET_PARABOLIC_EQU_DEC_TOL )
    results_check++;

  if ( abs((object.hor_altitude - expected_output[6])) <= COMET_PARABOLIC_HOR_ALTITUDE_TOL )
    results_check++;

  if ( abs((object.hor_azimuth - expected_output[7])) <= COMET_PARABOLIC_HOR_AZIMUTH_TOL )
    results_check++;

  if ( abs((object.earth_object_distance - expected_output[8])) <= COMET_PARABOLIC_EARTH_DIST_TOL )
    results_check++;

  //if ( abs((object.angular_size - expected_output[9])) <= COMET_PARABOLIC_ANGULAR_SIZE_TOL )
  if(isnan(object.angular_size))
    results_check++;

  if ( abs((object.light_travel_time - expected_output[10])) <= COMET_PARABOLIC_LIGHT_TRAVEL_TOL )
    results_check++;

  if ( abs((object.sun_object_distance - expected_output[11])) <= COMET_PARABOLIC_SUN_DIST_TOL )
    results_check++;

  if ( abs((object.phase - expected_output[12])) <= COMET_PARABOLIC_PHASE_TOL )
    results_check++;

  if ( abs((object.magnitude - expected_output[13])) <= COMET_PARABOLIC_MAG_TOL )
    results_check++;

  if ( abs((object.azimuth_rise - expected_output[14])) <= COMET_PARABOLIC_AZIMUTH_RISE_TOL )
    results_check++;

  if ( abs((object.azimuth_set - expected_output[15])) <= COMET_PARABOLIC_AZIMUTH_SET_TOL )
    results_check++;

  if ( abs((object.rise_time - expected_output[16])) <= COMET_PARABOLIC_RISE_TIME_TOL )
    results_check++;

  if ( abs((object.transit_time - expected_output[17])) <= COMET_PARABOLIC_TRANSIT_TIME_TOL )
    results_check++;

  if ( abs((object.set_time - expected_output[18])) <= COMET_PARABOLIC_SET_TIME_TOL )
    results_check++;

  cout << setprecision(DISPLAY_PRECISION);
  cout << "TestJunit002_012_000_0002" << endl;
  cout << "Expected:" << endl;
  cout << "Comet parabolic actual_geo_ecliptic_lambda     = " << expected_output[0] << endl;
  cout << "Comet parabolic actual geo ecliptic beta       = " << expected_output[1] << endl;
  cout << "Comet parabolic actual_helio_ecliptic_lambda   = " << expected_output[2] << endl;
  cout << "Comet parabolic actual helio ecliptic beta     = " << expected_output[3] << endl;
  cout << "Comet parabolic RA                             = " << expected_output[4] << endl;
  cout << "Comet parabolic DEC                            = " << expected_output[5] << endl;
  cout << "Comet parabolic hor_altitude                   = " << expected_output[6] << endl;
  cout << "Comet parabolic hor_azimuth                    = " << expected_output[7] << endl;
  cout << "Comet parabolic Sun-Earth distance             = " << expected_output[8] << endl;
  cout << "Comet parabolic angular size                   = " << expected_output[9] << endl;
  cout << "Comet parabolic light travel time              = " << expected_output[10] << endl;
  cout << "Comet parabolic Sun-object distance            = " << expected_output[11] << endl;
  cout << "Comet parabolic phase                          = " << expected_output[12] << endl;
  cout << "Comet parabolic magnitude                      = " << expected_output[13] << endl;
  cout << "Comet parabolic azimuth rise                   = " << expected_output[14] << endl;
  cout << "Comet parabolic azimuth set                    = " << expected_output[15] << endl;
  cout << "Comet parabolic rise time                      = " << expected_output[16] << endl;
  cout << "Comet parabolic transit time                   = " << expected_output[17] << endl;
  cout << "Comet parabolic set time                       = " << expected_output[18] << endl;
  cout << "Calculated:" << endl;
  cout << "Comet parabolic actual_geo_ecliptic_lambda     = " << object.actual_geo_ecliptic_lambda << endl;
  cout << "Comet parabolic actual geo ecliptic beta       = " << object.actual_geo_ecliptic_beta << endl;
  cout << "Comet parabolic actual_helio_ecliptic_lambda   = " << object.actual_helio_ecliptic_lambda << endl;
  cout << "Comet parabolic actual helio ecliptic beta     = " << object.actual_helio_ecliptic_beta << endl;
  cout << "Comet parabolic RA                             = " << object.equ_ra << endl;
  cout << "Comet parabolic DEC                            = " << object.equ_dec << endl;
  cout << "Comet parabolic hor_altitude                   = " << object.hor_altitude << endl;
  cout << "Comet parabolic hor_azimuth                    = " << object.hor_azimuth << endl;
  cout << "Comet parabolic Sun-Earth distance             = " << object.earth_object_distance  << endl;
  cout << "Comet parabolic angular size                   = " << object.angular_size << endl;
  cout << "Comet parabolic light travel time              = " << object.light_travel_time << endl;
  cout << "Comet parabolic Sun-object distance            = " << object.sun_object_distance << endl;
  cout << "Comet parabolic phase                          = " << object.phase << endl;
  cout << "Comet parabolic magnitude                      = " << object.magnitude << endl;
  cout << "Comet parabolic azimuth rise                   = " << object.azimuth_rise << endl;
  cout << "Comet parabolic azimuth set                    = " << object.azimuth_set << endl;
  cout << "Comet parabolic rise time                      = " << object.rise_time << endl;
  cout << "Comet parabolic transit time                   = " << object.transit_time << endl;
  cout << "Comet parabolic set time                       = " << object.set_time << endl;
  cout << "Results                                        = " << results_check << endl;
  cout << endl;

  BOOST_CHECK(results_check == 19);
}

// Binary star
BOOST_AUTO_TEST_CASE( TestJunit004_000_000_0000 )    
{
  // Expected results from:
  // Practical Astronomy with your Calculator, 3rd Edition p133
  api_interface api;
  double expected_output[2];
  double *output;
  int results_check = 0;
    
  // Set the expected answers.
  expected_output[0] = 318.424;	// Position angle
  expected_output[1] =   0.411;	// seperation
		 
  output = api.double_star(1980, 1, 1, 0, 0, 0.0, 0.0, 41.623, 1934.008, 0.907, 0.2763, 59.025, 219.907, 23.717);
						
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= BINARY_STAR_ANGLE_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= BINARY_STAR_SEP_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit004_000_000_0000" << endl;  
  cout << "Expected position angle   = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected separation       = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Calculated position angle = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated separation     = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 2);			
}

// Star rise and set
BOOST_AUTO_TEST_CASE( TestJunit004_001_000_0000 )    
{
  // Expected results from:
  // Practical Astronomy with your Calculator, 3rd edition p52-55
  api_interface api;
  double expected_output[5];
  double equ_co_ords[2];
  double *output;
  int results_check = 0;
    
  // Output[0] - Azimuth of the selected object to rise.
  // Output[1] - Azimuth of the selected object to set.		 
  // Output[2] - Time of the object rising (Julian date).
  // Output[3] - Time of the object setting (Julian date).
  // Output[4] - Time of when the object is in transit.  
    
  // Set the expected answers.
  expected_output[0] =  64.364237;	 
  expected_output[1] = 295.635763;
  expected_output[2] = 2444476.44851029;	 
  expected_output[3] = 2444476.02747827;
  expected_output[4] = 2444475.74067593;
  // Do not care about transit time. 		 
		 
  equ_co_ords[0] = 23.655556; // RA
  equ_co_ords[1] = 21.700000; // Dec		 
		 
  output = api.star_rise_set(2444475.50000,64.0,30.0,&equ_co_ords[0]);
						
  // Check that the answer is within the tolerance.
  if ( abs((output[0] - expected_output[0])) <= STAR_RISE_AZIMUTH_TOL )
    results_check++;
							
  if ( abs((output[1] - expected_output[1])) <= STAR_SET_AZIMUTH_TOL )
    results_check++;

  if ( abs((output[2] - expected_output[2])) <= STAR_RISE_TIME_TOL )
    results_check++;

  if ( abs((output[3] - expected_output[3])) <= STAR_SET_TIME_TOL )
    results_check++;
    
  if ( abs((output[4] - expected_output[4])) <= STAR_SET_TIME_TOL )
    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit004_001_000_0000" << endl;  
  cout << "Expected azimuth rise     = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected azimuth set      = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Expected time rise        = " << setprecision(DISPLAY_PRECISION) << expected_output[2] << endl;
  cout << "Expected time set         = " << setprecision(DISPLAY_PRECISION) << expected_output[3] << endl;
  cout << "Expected time transit     = " << setprecision(DISPLAY_PRECISION) << expected_output[4] << endl;
  cout << "Calculated azimuth rise   = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated azimuth set    = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated time rise      = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << "Calculated time set       = " << setprecision(DISPLAY_PRECISION) << output[3] << endl;
  cout << "Calculated time transit   = " << setprecision(DISPLAY_PRECISION) << output[4] << endl;
  cout << "reults_check              = " << results_check << endl;
  cout << endl;
	
  BOOST_CHECK(results_check == 5);			
}

// Star rise and set - when the star is circumpolar
BOOST_AUTO_TEST_CASE( TestJunit004_001_000_0001 )    
{
  api_interface api;
  double expected_output[5];
  double equ_co_ords[2];
  double *output;
  int results_check = 0;
    
  // Output[0] - Azimuth of the selected object to rise.
  // Output[1] - Azimuth of the selected object to set.		 
  // Output[2] - Time of the object rising (Julian date).
  // Output[3] - Time of the object setting (Julian date).
  // Output[4] - Time of when the object is in transit.  
    
  // Set the expected answers.
  expected_output[0] =  64.364237;	 
  expected_output[1] = 295.635763;
  expected_output[2] = 2444476.44851029;	 
  expected_output[3] = 2444476.02747827;
  expected_output[4] = 2444475.74067593;
   		 
  // The star is Polaris RA 2h 31m 49.09sec Dec +89 15' 50.8"		 
  equ_co_ords[0] =  2.530302778; // RA
  equ_co_ords[1] = 89.264111111; // Dec		 

  // Work out the rise ans set details for Polaris at 30N 0.0W on the 24th Aug 1980.		 
  output = api.star_rise_set(2444475.50000,0.0,30.0,&equ_co_ords[0]);
						
  // Check that the answer is within the tolerance.
//  if ( abs((output[0] - expected_output[0])) <= STAR_RISE_AZIMUTH_TOL )
//    results_check++;
//							
//  if ( abs((output[1] - expected_output[1])) <= STAR_SET_AZIMUTH_TOL )
//    results_check++;

  // A star that is circumpolar, then is never rises or sets.
  // The rest of the output from the star_rise_set function, in this case, is invalid.
  if (isnan(output[2]))
    results_check++;

  if (isnan(output[3]))
    results_check++;
    
//  if ( abs((output[4] - expected_output[4])) <= STAR_SET_TIME_TOL )
//    results_check++;
				
  // These lines are used for diagnostic reasons.
  cout << "TestJunit004_001_000_0001" << endl;  
  cout << "Expected azimuth rise     = " << setprecision(DISPLAY_PRECISION) << expected_output[0] << endl;
  cout << "Expected azimuth set      = " << setprecision(DISPLAY_PRECISION) << expected_output[1] << endl;
  cout << "Expected time rise        = " << setprecision(DISPLAY_PRECISION) << expected_output[2] << endl;
  cout << "Expected time set         = " << setprecision(DISPLAY_PRECISION) << expected_output[3] << endl;
  cout << "Expected time transit     = " << setprecision(DISPLAY_PRECISION) << expected_output[4] << endl;
  cout << "Calculated azimuth rise   = " << setprecision(DISPLAY_PRECISION) << output[0] << endl;
  cout << "Calculated azimuth set    = " << setprecision(DISPLAY_PRECISION) << output[1] << endl;
  cout << "Calculated time rise      = " << setprecision(DISPLAY_PRECISION) << output[2] << endl;
  cout << "Calculated time set       = " << setprecision(DISPLAY_PRECISION) << output[3] << endl;
  cout << "Calculated time transit   = " << setprecision(DISPLAY_PRECISION) << output[4] << endl;
  cout << "reults_check              = " << results_check << endl;
  cout << endl;

  // In this case, only the rise and set values actually matter.	
  BOOST_CHECK(results_check == 2);			
}
