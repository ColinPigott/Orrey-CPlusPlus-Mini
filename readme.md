# Orrey C++ mini

## Introduction

This is a basic astronomy library that can be used to:

- Predict the position and details of the Sun, Moon and planets.
- Predict the position of a comet with a periodic ordit.
- Predict the position of a comet with a parabolic orbit.
- Co-ordinate conversion
- Time conversion
- Work out the rise and set times of the Sun,Moon, the planets and a star.
- Work out the position of a binary star around it's origin star.

To be able to use this library, one needs:

- A build system that can handle the programming language used.
- The longitude,latitude and time of the observer.

The longitude is in the form:

- West is negative, i.e. 64 W is -64.
- East is positive, i.e. 64 E is 64

The longitude is in the form:

- North is positive, i.e. 51 N is 51.
- South is negative, i.e. 51 S is -51.

The time is sometimes in the form of Julian date (there is a function to convert this from a calender date and time).

## How to build

This library was developed on Ubuntu Linux and g++.  
On Linux, this is done by:

g++ -Wall Application.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp

Where:  
&nbsp;&nbsp;&nbsp;&nbsp;Application.cpp is the code that is using the library.  
&nbsp;&nbsp;&nbsp;&nbsp;api_interface.cpp is the interface to the library.   
&nbsp;&nbsp;&nbsp;&nbsp;The rest of the files are part of the Orrey library.  

The above produces the following (in the same dir as the code):

	a.out

The execute:

	./a.out


## Sections

The functions provided by this library come into the following groups:

- star functions
- cordinate conversion
- time conversion
- comet position
- objects in the solar system

The methods are described in more detail here [sections](Sections.md).

## Building and Performance

This library was developed on Ubuntu Linux and g++.
The basic library does not require any extra frameworks in order to work.

However the for the testing framework, the boost test framework does need to be installed before it can be used.
  
The size of the binary on a x86 Linux system is c.100K.

## Testing

There is a test harness for this library and it is based on the boost test harness (which has to be installed before this testharness is to be used).

The testharness is build by:

g++ -Wall -o testharness.out orrey_mini_testharness.cpp star.cpp math_misc.cpp time_details.cpp api_interface.cpp coord_conversion.cpp comet_details.cpp sun.cpp moon.cpp planets.cpp -lboost_system -lboost_thread -lboost_unit_test_framework 

The test harness tests each method in the Orrey mini api.

The above produces the following (in the same dir as the code):

	testharness.out

The execute:

	./testharness.out

The tolerances of this library is given in:

	orrey_mini_testharness_tolerances.h

## Limitations

Powerful though this library is, it does have some limitations, viz:

- The model used for the planets does not take account the effect of perturbations 
  (as a result, the position of a body could be off by up to a degree).
- The position of a comet does not take perturbations (though comet positions are always
  rough due to the core heating as it gets close to the Sun; the verting gas act as jet thrusters).
- The Earth's atmosphere can have a big effect of the rise and set times (this model uses
  the rule of thumb value of 34 minutes of arc).
- The position of Mercury does not take into account relativity.
- The julian_date method only works for dates after 1582 Oct 15.

Having said that, no model will be perfect.

The tolerances for the library is given in the file orrey_mini_testharness_tolerances.h 

## References/Sources of test data

The algorithums used for this library were provided by:

Practical Astronomy with your Calculator, 3rd edition,  
Peter Duffett-Smith,  
Cambridge University Press,  
1990, Cambridge,
ISBN 0 521 35629 6 hardback  
ISBN 0 521 35699 7 paperback  

Astronomical Algorithms,  
J. Meeus,  
Atlantic Books, 1998  
ISBN 0 943 39661 1 hardback  

The test data used to test the effectiveness of this libary comes from a number of websites (no one website contains all the information). The sites used were:  

Jet Propulsion Laboratory Horizons System  
https://ssd.jpl.nasa.gov  
Very useful for finding the details of the objects in the Solar system except for the rise and set times.  
It also contains the orbital details of comets.  

Heavens Above  
https://www.heavens-above.com  
Used to find the rise and set times of the Sun,Moon and planets.  
The azimuth of the rise and set times can be found by setting the time to the rise or set and reading the value for the azimuth.  

aavso  
https://www.aavso.org/jd-calculator  
Very useful for converting to and from Julian dates.  

The Sky Live  
https://theskylive.com  
This site also has the rise and set times of the Sun,Moon and planets.  
It also contains the orbital details of comets.  

http://www.dibonsmith.com/elements.htm  
This is a good source of binary star orbits.  