#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// function f
#define f(x) (sin(exp(-(x) * (x))))
// and its derivative f'
#define fp(x) (-2.0 * (x) * exp(-(x) * (x)) * cos(exp(-(x) * (x))))

/*
 * Central difference derivative f'(x) with step size h.
 */
double central_difference(double x, double h)
{
	return (f(x + h) - f(x - h)) / (2.0 * h);
}

/*
 * Derivative f'(x) using Richardson extrapolation
 * with parameters n and h.
 */
double richardson(double x, int n, double h)
{
	double *dj = calloc(sizeof(double), n+1); // row j
	double *djj = calloc(sizeof(double), n+1); // new row j
	
	double dij = 0.0;
	double hh = h; // step size
	
	for (int i = 0; i <= n; ++i) {
		dij = central_difference(x, hh);
		djj[0] = dij; // first in row always CD

		for(int j = 0; j < i; ++j) {
			dij += (dij - dj[j]) / (pow(4.0, j + 1) - 1.0); // d(i, j + 1)
			djj[j+1] = dij; // calculate new row
		}
		for (int jj = 0; jj < n; ++jj)
			dj[jj] = djj[jj]; // copy new row

		hh /= 2.0; // h / 2^i
	}

	free(dj);
	free(djj);

	return dij;
}
