// Namespace to store the constants.
namespace constants
{
  // Angles related
  const double PI = 3.14159265359;
  const double TO_RADIANS = PI / 180.0;	      // DEG * PI/180
  const double TO_DEGREES = 180.0 / PI;             // RAD * 180/PI
  const double HR_MOV = 15.0;                       // How many degrees one hour
                                                    // of RA represents.
  const double ARCSECONDS_IN_A_DEGREE = 3600;	      // The number of arcseconds
                                                    // in a degree.

  // Time related
  const double JULIAN1990JAN0 = 2447892.5;          // Julian date on 1990 1 Jan 0.0.
  const double JULIAN2000JAN1_5 = 2451545.0;        // Julian day for 2000 Jan 1.5
  const double JULIAN_CENTURY = 36525.0;            // The number of days in a Julian century.

  // Distance related
  const double KM_IN_AU       = 1.495979e8;	      // An AU in Km.

  // Speed related
  const double SPEEDOFLIGHT = 299792.458;	      // Speed of light (Km/sec).
  const double TIME_FOR_LIGHT_TO_TRAVEL_1_AU = 498; // The number of seconds
                                                    // needed to travel 1 AU.

  // Earth atmosphere related
  const double ATMOSPHERIC_REFRACTION = 0.5667;     // Refraction due to the Earth's atmosphere
  	  	  	  	  	  	      // 34 minutes of arc.

}
