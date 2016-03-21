#ifndef FUNCTIONS_H
#define FUNCTIONS_H

double max(double* values,int count);
double power(double* values,int count);
double signinversion(double* values,int count);
double squareroot(double* values,int count);

struct func {
	char name[10];
	double (*f)(double*,int);
	int operandsCount;
};

static func functions[4] = {
	{"max",&max,2},
	{"power",&power,2},
	{"signinv",&signinversion,1},
	{"sqrt",&squareroot,1}
};

static int functionsCount = 4;


#endif