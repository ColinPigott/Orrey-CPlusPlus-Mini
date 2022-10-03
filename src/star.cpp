// This class is related to stars.
#include <math.h>
#include <iostream>
#include "math_misc.hpp"
#include "star.hpp"
#include "constants.hpp"

using namespace std;

// From Astronomy for Your Calculator p137.
double* star::double_star(double year,
                          double period,
                          double periastron,
                          double semi_major,
                          double e,
                          double i,
                          double w,
                          double pa)
{
  static double output[2];
  math_misc math_misc;
	
  double years_since,m,Ee,delta,delta_Ee,v,r,y,x,angle;
			
  years_since = year - periastron;
		
  m = (360 * years_since) / period;
		
  // Place into the range 0-360.
  while ( (m > 360) || (m < 0) )
  {
    if (m > 360)
      m -= 360;
    if (m < 0)
      m += 360;
  }
		
  m = math_misc.to_radians(m);
		
  // Solve Kepler's equation.
  Ee    = m;
  delta = m;
		
  while (abs(delta) > 0.000001)
  {
    delta = Ee - e * sin(Ee) - m;
    delta_Ee = delta / (1-e*cos(Ee));
			
    Ee = Ee - delta_Ee;
  }
		
  v = Ee / 2;
  v = tan(v);
  v = sqrt( (1+e) / (1-e) ) * v;
  v = 2 * atan(v);
  v = math_misc.to_degrees(v);
	
  r = semi_major * ( 1 - (e*cos(Ee)) );
		
  y = sin( math_misc.to_radians((v+w)) ) * cos(math_misc.to_radians(i));
  x = cos( math_misc.to_radians((v+w)) );
		
  angle = math_misc.tan_correct_quadrant(x,y);
			
  output[0] = angle + pa;
		
  if (output[0] > 360)
    output[0] -= 360;
		
  if (output[0] < 0)
    output[0] += 360;
		
  output[1] = (r * cos(math_misc.to_radians( (v + w) ))) / (cos(math_misc.to_radians( (output[0]-pa))));
		
  return output;
}
