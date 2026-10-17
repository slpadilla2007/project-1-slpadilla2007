#include <iostream>
#include <cstdlib>
#include "capacitor.h"
//Needed structure is in capacitor.h
//The variables in my structure were shortened for ease of use while coding
//voltage = volt, current = curr

using namespace std;

int main() {
	
	/*Makes a dynamically allocated array of two capacitors, one for the const current supply
	  and one for the const voltage supply*/
	Capacitor *theCap;
	theCap = (Capacitor*) malloc(sizeof(Capacitor)*2);
	
	//All needed constant values
	/*Change in t (aka delta t or dt), time step*/
	const double dt = 1e-10;
	/*The final time*/
	const double finalTime = 5e-6;
	/*Total number of timesteps, this will be 50000*/
	const int totalStep = static_cast<int>(finalTime/dt);
	/*Resistance, equal to 1 kOhm*/
	const double R = 1e3;
	/*Capacitance*/
	const double C = 100e-12;
	/*For constant current supply calculations*/
	const double constI = 1e-2;
	/*For constant voltage supply calculations*/
	const double VO = 10;
	
	//Memory allocation for const current supply
	//There is one added to each of the sizes so that the 50000th step can be calculated
	theCap[0].time = (double*) malloc(sizeof(double) * (totalStep + 1));
	theCap[0].volt = (double*) malloc(sizeof(double) * (totalStep + 1));
	theCap[0].curr = (double*) malloc(sizeof(double) * (totalStep + 1));

	//Memory allocation for const voltage supply
	//There is one added to each of the sizes so that the 50000th step can be calculated
	theCap[1].time = (double*) malloc(sizeof(double) * (totalStep + 1));
	theCap[1].volt = (double*) malloc(sizeof(double) * (totalStep + 1));
	theCap[1].curr = (double*) malloc(sizeof(double) * (totalStep + 1));
	
	//Initial values for const current supply
	theCap[0].time[0] = 0;
	theCap[0].volt[0] = 0;
	theCap[0].curr[0] = constI;
	theCap[0].C = C;

	//Initial values for const voltage supply
	theCap[1].time[0] = 0;
	theCap[1].volt[0] = 0;
	theCap[1].curr[0] = VO/R;
	theCap[1].C = C;

	//Const current calculations
	for (int s = 1; s <= totalStep; s++) {
		theCap[0].time[s] = theCap[0].time[s-1] + dt;
		theCap[0].volt[s] = theCap[0].volt[s-1] + (theCap[0].curr[s-1] * dt)/theCap[0].C;
		theCap[0].curr[s] = constI;
	}
	
	//Const voltage calculations
	for (int s = 1; s <= totalStep; s++) {
		theCap[1].time[s] = theCap[1].time[s-1] + dt;
		theCap[1].volt[s] = theCap[1].volt[s-1] + (theCap[1].curr[s-1] * dt)/theCap[1].C;
		theCap[1].curr[s] = theCap[1].curr[s-1] - (theCap[1].volt[s-1] * dt)/(R * theCap[1].C);
	}

	//Const current prints
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Constant Current Source Power Supply" << endl;
	for (int i = 0; i <= totalStep; i += 200) {
		if (i != 0) {
			cout << i << "th time step:" << endl;
		} else {
			cout << "~~~~~~~~~~" << endl;
			cout << "initial time step:" << endl;
		}
		cout << "t = " << theCap[0].time[i] << " s" << endl;
		cout << "V(t) = " << theCap[0].volt[i] << " V" << endl;
		cout << "I(t) = " << theCap[0].curr[i] << " A" << endl;
		cout << "~~~~~~~~~~" << endl;
	}

	//Const voltage prints
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Constant Voltage Source Power Supply" << endl;
	for (int i = 0; i <= totalStep; i += 200) {
		if (i != 0) {
			cout << i << "th time step:" << endl;
		} else {
			cout << "~~~~~~~~~~" << endl;
			cout << "initial time step:" << endl;
		}
		cout << "t = " << theCap[1].time[i] << " s" << endl;
		cout << "V(t) = " << theCap[1].volt[i] << " V" << endl;
		cout << "I(t) = " << theCap[1].curr[i] << " A" << endl;
		cout << "~~~~~~~~~~" << endl;
	}
	
	//Frees all allocated memory
	for (int f = 0; f <= 1; f++) {
		free(theCap[f].time);
		free(theCap[f].volt);
		free(theCap[f].curr);
	}
	free(theCap);
	
	//End of code yippee yay wahoo :)
	return 0;

}
