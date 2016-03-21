#include <tgmath.h>
#include "functions.h"

double max(double* values,int count){
	double max = values[0];
	for(int i=1; i < count;i++)
		if(values[i] > max)
			max = values[i];

	return max;
}

double power(double *values, int count) {
	return pow(values[1],values[0]);
}

double signinversion(double *values, int count) {
	return values[0]*(-1);
}

double squareroot(double *values, int count) {
	return sqrt(values[0]);
}
