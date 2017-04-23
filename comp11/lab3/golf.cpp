//
// golf.cpp
//	    version: 2012-09-18 Remove fcn call; keep booleans, consts
//	    purpose: practice using booleans and constants
//	modified by:
//	         on:
//
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// days of the week
const int SUN = 0, MON = 1, TUE = 2, WED = 3, THR = 4, FRI = 5, SAT = 6;

// constants for rules
const double	BASE_PRICE            = 9.0;
const int	HIGH_TEMP_CUTOFF      = 80;
const int	LOW_TEMP_CUTOFF       = 65;
const double	PER_DEGREE_PENALTY    = 0.10;
const int	EVENING_START         = 17;
const double	WEEKEND_EVE_SURCHARGE = 1.00;
const double	RAIN_PENALTY          = 2.00;
const int	WIND_GRANULARITY      = 15;
const double	WIND_PENALTY          = 1.50;
const int	IS_RAINING	      = 1;
const int       FREE		      = 0;

// main function here
int main() 
{
	// -- define vars for input and a value used in the tests below
	int	tempF, dayOweek, hour, rainP, windMPH;
	double	price;

	// -- set the precision 
	cout << setiosflags(ios::fixed) << setprecision(2);
	
	// -- Get data from user
	cout << "Temperature (fahrenheit)? ";
	cin  >> tempF;

	cout << "Day of week (0 = Sun, 1 = Mon, ..., 6 = Sat)? " ;
	cin  >> dayOweek;
	
	cout << "Hour of day (0..23)? ";
	cin  >> hour;

	cout << "Is it raining (0 = no, 1 = yes)? ";
	cin  >> rainP;

	cout << "Wind speed (MPH)? ";
	cin  >> windMPH;

	// -- compute price based on these values

	price = BASE_PRICE;

	if (tempF > HIGH_TEMP_CUTOFF) { // -- tests current temp. to see price should be lowered
	    price = price - (tempF - HIGH_TEMP_CUTOFF)*(PER_DEGREE_PENALTY);
	} else if (tempF < LOW_TEMP_CUTOFF) {
	    price = price - (LOW_TEMP_CUTOFF - tempF)*(PER_DEGREE_PENALTY);
	}
	if ((dayOweek == SUN || dayOweek == SAT) || (hour >= EVENING_START)) { // -- tests current hour and dayOweek to see surcharge should be added
		price = price + WEEKEND_EVE_SURCHARGE;
	}
	if (rainP == IS_RAINING) { // -- tests to see if a rain penalty should be deducted from price
	    price = price - RAIN_PENALTY; 
	}
	if (windMPH >= WIND_GRANULARITY) {
	    price = price - floor(windMPH / WIND_GRANULARITY)*(WIND_PENALTY);
	}
	if (price < FREE){ // -- if the price is below zero, make golfing free
	    price = FREE;
	}

	// -- report price to user

	cout << "Price: " << price << endl;
	return 0;
}
