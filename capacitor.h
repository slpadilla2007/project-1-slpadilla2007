#ifndef CAPACITOR_H 
#define CAPACITOR_H

struct _capacitor {

	double *time;
	double *volt;
	double *curr;
	double C;

};

typedef struct _capacitor Capacitor;

#endif
