#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// function for golden section minimization
#define f(x) ((x) * (x) * (x) * (x) * (erf(x) - 1.))

// golden ratio
#define GOLDEN_R 1.61803398875
// tolerance for golden section
#define GOLDEN_TOL 1e-6

/*
 * Golden section search algorithm for finding the minimum of function f 
 * in range [xa, xc].
 */
double golden(double xa, double xc)
{
	double ba, bc;
	double a = xa, c = xc;

	while (fabs(c - a) > GOLDEN_TOL) { // iterate until tolerance reached
		ba = c - (c - a) / GOLDEN_R;
		bc = a + (c - a) / GOLDEN_R;
	
		if (f(ba) < f(bc)) // pick which side to advance
			c = bc;
		else
			a = ba;
	}

	return (a + c) / 2.; // return value in the middle
}
